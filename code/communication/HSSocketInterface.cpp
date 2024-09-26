#include "HSSocketInterface.h"

namespace SocketNameSpace{
// 创建对象的函数实现
    std::unique_ptr<HSSocketInterface> SocketNameSpace::createSocketObject()
    {
        std::unique_ptr<HSSocketInterface> ptr ;
        return ptr;
    }
}
