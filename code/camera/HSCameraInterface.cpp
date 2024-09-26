#include "HSCameraInterface.h"
#include "DushenBasicFunc.h"


namespace CameraNameSpace{
// 创建对象的函数实现
    std::unique_ptr<HSCameraInterface> CameraNameSpace::createCameraObject()
    {
        std::unique_ptr<HSCameraInterface> ptr = std::make_unique<DushenBasicFunc>();
        return ptr;
    }
}

