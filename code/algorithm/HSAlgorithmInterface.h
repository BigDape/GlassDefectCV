#ifndef HSALGORITHMINTERFACE_H
#define HSALGORITHMINTERFACE_H

#include <memory>
#include <vector>
#include <QString>
#include <windows.h>
#include <QImage>
#include "hstool.h"

namespace AlgorithmNamespace
{
    // 错误码枚举
    enum class HSAlgorithmError {
        SUCCESS = 0,
        INVALID_PARAMETER,
        OUT_OF_MEMORY,
        INNER_ERROR
    };
    // 抽象接口类
    class HSAlgorithmInterface
    {
    public:
        virtual ~ HSAlgorithmInterface(){}

        virtual void init() = 0;

        virtual void Execu() = 0;

        virtual void Stop() = 0;

        virtual void Exit() = 0;
    };

    // 用于创建对象的函数（DLL 导出函数）
    __declspec(dllexport) std::unique_ptr<HSAlgorithmInterface> createAlgorithmObject();
}



#endif // HSALGORITHMINTERFACE_H
