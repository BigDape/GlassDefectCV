#include "HSSocketInterface.h"
#include "SignalControlData.h"


// 创建对象的函数实现
std::unique_ptr<SocketNameSpace::HSSocketInterface> SocketNameSpace::createSocketObject()
{
    std::unique_ptr<SocketNameSpace::HSSocketInterface> ptr = std::make_unique<SignalControlData>(); ;
    return ptr;
}
