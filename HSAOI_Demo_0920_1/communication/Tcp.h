#ifndef TCP_H
#define TCP_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

class Tcp : public QObject
{
    Q_OBJECT
public:
    explicit Tcp(qint64 bufLength = DEFAULT_BUFF_LENGTH, QObject* parent = nullptr);
    virtual ~Tcp();

    void ConnectToServer(QString ip, int port);
    void Close();
    bool WriteData(const char* data, int len);
    bool WriteData(const QByteArray& data);
    void InitSock(const char* IP, int port);
    void SetAutoConnect(bool bAuto) { m_bAutoReConnect = bAuto; }
    bool IsOpen() {
        if (!m_pSock)
            return false;
        return m_bConnFlag;
    }


public:
    enum { DEFAULT_BUFF_LENGTH = 1600 };

protected:
    virtual void ParseData(const char*, qint64) { }

protected:
    QHostAddress m_addr; // 连接服务端地址
    int m_nPort;         // 连接的服务端端口

    QTcpSocket* m_pSock;
    QThread* m_pThread;

    qint64 MaxBuffLength;
    char* ReadBuff;
    int ReConnectCount = 0; //重连次数

private:
    bool m_bConnFlag;       //连接状态
    bool m_bAutoReConnect;  //是否自动重连

protected:
    virtual void vThreadStarted() { }

public slots:
    void slot_threadStarted();

private slots:
    void slot_writeData(QByteArray data);
    void OnReadyRead();
    void OnSockStateChanged(QAbstractSocket::SocketState);
};

#endif // TCP_H
