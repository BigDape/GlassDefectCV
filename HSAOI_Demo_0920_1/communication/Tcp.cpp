#include "Tcp.h"
#include <QDate>
#include <QTimer>
#pragma execution_character_set("utf-8")

Tcp::Tcp(qint64 bufLength, QObject *parent)
    : QObject(parent)
    , MaxBuffLength(bufLength)
    , m_bConnFlag(false)
    , m_bAutoReConnect(true)
{
    ReadBuff = new char[MaxBuffLength];
    m_pSock = new QTcpSocket();
    m_pThread = new QThread();
    m_pSock->moveToThread(m_pThread);
    this->moveToThread(m_pThread);
    connect(m_pSock, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
    connect(m_pSock, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this , SLOT(OnSockStateChanged(QAbstractSocket::SocketState)));
    connect(m_pThread, SIGNAL(started()), this, SLOT(slot_threadStarted()));
    m_pThread->start();
}

Tcp::~Tcp()
{
    if(m_pSock)
    {
        if(m_pSock->isOpen() && m_bConnFlag)
        {
            m_pSock->disconnectFromHost();
            m_bConnFlag = false;
        }
    }
    m_pThread->exit(0);
    m_pThread->wait(2000);
    m_pThread->deleteLater();
    m_pSock->deleteLater();
    delete [] ReadBuff;
    ReadBuff = NULL;
}

void Tcp::slot_threadStarted()
{
    vThreadStarted();
}

void Tcp::ConnectToServer(QString ip, int port)
{
    m_addr.setAddress(ip);
    m_nPort = port;
    if (m_pSock) {
        m_pSock->connectToHost( m_addr, m_nPort );
    }
}

void Tcp::Close()
{
    if (m_pSock) {
        if (m_pSock->isOpen() && m_bConnFlag) {
            m_pSock->disconnectFromHost();
            m_bConnFlag = false;
        }
    }
}

bool Tcp::WriteData( const char *data, int len )
{
    if( NULL == data || len <= 0 || !m_pSock || !m_bConnFlag)
        return false;

    QByteArray s_data(data, len);

    qint64 ret = m_pSock->write(data);

    if( ret > 0 ) {
        if (m_nPort == 7002) {
            //GlobalLogger.addLog("write heart beat request to net");
        }
    }

    return true;
}

bool Tcp::WriteData( const QByteArray & data )
{
    if( data.length() <= 0 || !m_pSock || !m_bConnFlag) {
        return false;
    }

    qint64 ret = m_pSock->write(data);

    if( ret > 0 ) {
        if (m_nPort == 7002) {
            //GlobalLogger.addLog("write heart beat request to net");
        }
    }

    return true;
}

void Tcp::slot_writeData( QByteArray data )
{
    // 参数判断
    if( data.length() <= 0 || !m_pSock || !m_bConnFlag)
        return ;

    qint64 ret = m_pSock->write(data);

    if( ret > 0 ) {
        if (m_nPort == 7002) {
            //GlobalLogger.addLog("write heart beat request to net");
        }
    }
}

void Tcp::OnReadyRead()
{
    qint64 len = m_pSock->read( ReadBuff, MaxBuffLength );
    if( len > 0 ) {
        ParseData( ReadBuff, len );
    } else {
        qDebug()<<"len ="<<len;
    }
}

void Tcp::OnSockStateChanged(QAbstractSocket::SocketState state)
{
    if (QAbstractSocket::UnconnectedState == state) {
        m_bConnFlag = false;
        if (m_bAutoReConnect ) {
LOOP:
                if (m_pSock) {
                    m_pSock->connectToHost( m_addr, m_nPort );
                } else {
                    ReConnectCount ++;
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    if(ReConnectCount < 30) {
                        goto LOOP;
                    } else {
                        ReConnectCount = 0;
                    }
                }
        }
    } else if (QAbstractSocket::ConnectedState == state) {
        m_bConnFlag = true;
        qDebug() << "port" << m_nPort << ", connected";
    } else {
        qDebug()<<"QAbstractSocket::SocketState = "<<state;
    }
}
