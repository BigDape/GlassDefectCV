#ifndef HSSOCKETINTERFACE_H
#define HSSOCKETINTERFACE_H

#include <memory>
#include "hstool.h"

namespace SocketNameSpace
{
    // 错误类型
    enum class HSSocketError {
        SUCCESS = 0,
        INVALID_PARAMETER,
        OUT_OF_MEMORY,
        INNER_ERROR
    };

    class HSSocketInterface
    {
    public:
        virtual ~HSSocketInterface(){}
        /**
         * @brief InitRegs 初始化寄存器
         */
        virtual void InitRegs(QString ip, int port) = 0;
        /**
         * @brief Trigger 调试模式下触发光源
         */
        virtual void Trigger() = 0;
        /**
         * @brief SetAllRegs 将设置的所有参数下发给信号板寄存器
         */
        virtual void SetAllRegs(SignalControl data) = 0;
        /**
         * @brief SetReg 设置单个参数下发给信号板寄存器
         */
        virtual void SetReg(unsigned short addr_s,
                            unsigned short addr_e,
                            unsigned int data) = 0;
        /**
         * @brief GetRealTimeData 单次获取信号板寄存器地址，外部需实时获取
         */
        virtual void GetRealTimeData(unsigned int& FrameSignal, unsigned int& AlmLightSignal) = 0;
        /**
         * @brief GetAllData 获取信号板所有寄存器地址
         */
        virtual void GetAllData(SignalControl& data) = 0;
        /**
         * @brief TestIPConnect 测试端口连接是否正确
         */
        virtual bool TestIPConnect() = 0;
    };

    // 用于创建对象的函数（DLL 导出函数）
    __declspec(dllexport) std::unique_ptr<HSSocketInterface> createSocketObject();
}



#endif // HSSOCKETINTERFACE_H
