#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "algorithm_global.h"

class ALGORITHM_EXPORT Algorithm
{
public:
    Algorithm();
    // 初始化算法
    void init();
    // 执行图像算法
    void Execu();
    // 暂停图像算法
    void Stop();
    // 完成图像算法
    void Exit();
};

#endif // ALGORITHM_H
