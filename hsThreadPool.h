#ifndef HSTHREADPOOL_H
#define HSTHREADPOOL_H

#include <mutex>
#include <queue>
#include <mutex>
#include <thread>
#include <list>
#include <memory>
#include <vector>
#include <utility>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>

//线程安全队列
template <typename T>
class SafeQueue{
private:
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable condition;
    int _maxCount;
public:
    explicit SafeQueue(int count = INT_MAX):_maxCount(count){}
    explicit SafeQueue(SafeQueue& other){
        if(this != &other) {
            _maxCount = other._maxCount;
            _queue = other._queue;
            _mutex = other._mutex;
        }
    }
    SafeQueue& operator=(const SafeQueue& other){
        if (this != &other) {
            _maxCount = other._maxCount;
            _queue = other._queue;
            _mutex = other._mutex;
        }
    }
    ~SafeQueue(){}
    bool empty(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.empty();
    }
    int size(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.size();
    }
    void inqueue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        condition.wait(sbguard,[this]{if(_queue.size() > _maxCount)
                                        return false;
                                      return true;});
        _queue.push(t);
    }
    void push(const T& _Val){
        std::unique_lock<std::mutex> sbguard(_mutex);
        condition.wait(sbguard,[this]{if(_queue.size() > _maxCount)
                                        return false;
                                      return true;});
        _queue.push(_Val);
    }
    void push(T& _Val){
        std::unique_lock<std::mutex> sbguard(_mutex);
        condition.wait(sbguard,[this]{if(_queue.size() > _maxCount)
                                        return false;
                                      return true;});
        _queue.push(_Val);
    }
    bool dequeue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        if(_queue.empty()){
            return false;
        }
        t = std::move(_queue.front());
        _queue.pop();
        condition.notify_one();
        return true;
    }
    void pop(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _queue.pop();
        condition.notify_one();
    }
    T& front(){
       std::unique_lock<std::mutex> sbguard(_mutex);
       return (_queue.front());
    }

    T& back(){
       std::unique_lock<std::mutex> sbguard(_mutex);
       return (_queue.back());
    }

    void swap(T& _Right){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _queue.swap(_Right);
    }


};

class hsThreadPool
{
private:
    //内置线程工作类
    class ThreadWorker{
    private:
        int _id;
        hsThreadPool* _pool;
    public:
        ThreadWorker(hsThreadPool* pool,const int id)
        :_pool(pool),_id(id){

        }
        void operator()(){
            std::function<void()> func;
            bool dequeued;
            while(!_pool->_shutdown){
                {
                    std::unique_lock<std::mutex> lock(_pool->_conditional_mutex);
                    if(_pool->_queue.empty()){
                        _pool->_conditional_lock.wait(lock);
                    }
                    dequeued = _pool->_queue.dequeue(func);
                }
                if(dequeued){
                    func();
                }
            }
        }
    };//ThreadWorker

    bool _shutdown;//线程池是否关闭
    SafeQueue<std::function<void()>> _queue;//执行函数安全队列，即任务队列
    std::vector<std::thread> _threads;//工作线程队列
    std::mutex _conditional_mutex;//线程休眠锁互斥量
    std::condition_variable _conditional_lock;//线程环境锁，让线程可以处于休眠或者唤醒状态
public:
    hsThreadPool(const int n_threads, const int maxQueueCount)
    :_threads(std::vector<std::thread>(n_threads)),
     _shutdown(false),
     _queue(SafeQueue(maxQueueCount))
    {
    }

    hsThreadPool(const hsThreadPool&)=delete;
    hsThreadPool(hsThreadPool&&)=delete;
    hsThreadPool& operator=(const hsThreadPool&)=delete;
    hsThreadPool& operator=(hsThreadPool&&)=delete;

    void Init() {
        for(int i=0;i<_threads.size();++i) {
            _threads[i]=std::thread(ThreadWorker(this,i));
        }
    }

    void shutdown() {
        _shutdown = true;
        _conditional_lock.notify_all(); //通知 唤醒所有工作线程

        for (int i = 0; i < _threads.size(); ++i) {
            if(_threads[i].joinable()) { //判断线程是否正在等待
                _threads[i].join();  //将线程加入等待队列
            }
        }
    }

    template <typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        // Create a function with bounded parameters ready to execute
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);//连接函数和参数定义，特殊函数类型,避免左、右值错误

        //封装获取任务对象，方便另外一个线程查看结果
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        // Wrap packaged task into void function
        //利用正则表达式，返回一个函数对象
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };

        // 队列通用安全封包函数，并压入安全队列
        _queue.inqueue(wrapper_func);

        // 唤醒一个等待中的线程
        _conditional_lock.notify_one();

        // 返回先前注册的任务指针
        return task_ptr->get_future();
    }

};


#endif // HSTHREADPOOL_H
