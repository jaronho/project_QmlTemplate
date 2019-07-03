/**********************************************************************
* Author:	jaron.ho
* Date:		2019-02-15
* Brief:	串口操作
**********************************************************************/
#ifndef _SERIAL_OP_H_
#define _SERIAL_OP_H_

#include <functional>
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

#define SERIAL_RECV_CALLBACK std::function<void(QByteArray command)>

class SerialOP : public QObject {
    Q_OBJECT

public:
    /* 获取有效的端口信息 */
    static QList<QSerialPortInfo> availablePorts(void);

public:
    SerialOP(void);

    ~SerialOP(void);

    /* 获取端口名称 */
    QString getPort(void);

    /* 获取波特率 */
    QString getBaudRate(void);

    /* 设置波特率:"1200","2400","4800","9600","19200","38400","57600","115200" */
    bool setBaudRate(QString baudRate);

    /* 获取数据位 */
    QString getDataBits(void);

    /* 设置数据位:"5","6","7","8" */
    bool setDataBits(QString bits);

    /* 获取停止位 */
    QString getStopBits(void);

    /* 设置停止位:"1","1.5","2" */
    bool setStopBits(QString bits);

    /* 获取校验位 */
    QString getParity(void);

    /* 设置校验位:"None","Even","Odd","Space","Mark" */
    bool setParity(QString bits);

    /* 设置串口数据接收回调函数 */
    void setRecvCallabck(SERIAL_RECV_CALLBACK callback);

    /* 是否已打开 */
    bool isOpen(void);

    /* 打开串口 */
    bool open(QString portName, QIODevice::OpenMode mode);

    /* 关闭串口 */
    void close(void);

    /* 发送数据,sleepMillisecondWhenOk:阻塞时间(当发送成功时才有效,毫秒) */
    bool send(QByteArray data, unsigned int sleepMillisecondWhenOk = 0);

    /* 发送数据,会阻塞等待响应数据,timeout:超时时间(毫秒,最小有效值10毫秒) */
    bool sendWait(QByteArray data, QByteArray& responseData, unsigned int timeout = 100);

private slots:
    void recvSerialData(void);

private:
    QSerialPort* mSerial;
    QByteArray mRecvData;
    SERIAL_RECV_CALLBACK mRecvCallback;
};

#endif // _SERIAL_OP_H_
