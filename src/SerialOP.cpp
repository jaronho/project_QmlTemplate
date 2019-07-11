/**********************************************************************
* Author:	jaron.ho
* Date:		2019-02-15
* Brief:	串口操作
**********************************************************************/
#include "SerialOP.h"

QList<QSerialPortInfo> SerialOP::availablePorts(void) {
    return QSerialPortInfo::availablePorts();
}

SerialOP::SerialOP(void) {
    mSerial = new QSerialPort();
    mSerial->setFlowControl(QSerialPort::NoFlowControl);
    QObject::connect(mSerial, SIGNAL(readyRead()), this, SLOT(recvSerialData()));
}

SerialOP::~SerialOP(void) {
    if (mSerial->isOpen()) {
        mSerial->close();
    }
    delete mSerial;
    mSerial = nullptr;
}

QString SerialOP::getPort(void) {
    return mSerial->portName();
}

QString SerialOP::getBaudRate(void) {
    return QString::number(mSerial->baudRate());
}

bool SerialOP::setBaudRate(QString baudRate) {
    if (0 == baudRate.compare("1200")) {
        return mSerial->setBaudRate(QSerialPort::Baud1200);
    } else if (0 == baudRate.compare("2400")) {
        return mSerial->setBaudRate(QSerialPort::Baud2400);
    } else if (0 == baudRate.compare("4800")) {
        return mSerial->setBaudRate(QSerialPort::Baud4800);
    } else if (0 == baudRate.compare("9600")) {
        return mSerial->setBaudRate(QSerialPort::Baud9600);
    } else if (0 == baudRate.compare("19200")) {
        return mSerial->setBaudRate(QSerialPort::Baud19200);
    } else if (0 == baudRate.compare("38400")) {
        return mSerial->setBaudRate(QSerialPort::Baud38400);
    } else if (0 == baudRate.compare("57600")) {
        return mSerial->setBaudRate(QSerialPort::Baud57600);
    } else if (0 == baudRate.compare("115200")) {
        return mSerial->setBaudRate(QSerialPort::Baud115200);
    }
    return false;
}

QString SerialOP::getDataBits(void) {
    switch (mSerial->dataBits()) {
    case QSerialPort::Data5:
        return "5";
    case QSerialPort::Data6:
        return "6";
    case QSerialPort::Data7:
        return "7";
    case QSerialPort::Data8:
        return "8";
    case QSerialPort::UnknownDataBits:
        return "";
    }
    return "";
}

bool SerialOP::setDataBits(QString bits) {
    if (0 == bits.compare("5")) {
        return mSerial->setDataBits(QSerialPort::Data5);
    } else if (0 == bits.compare("6")) {
        return mSerial->setDataBits(QSerialPort::Data6);
    } else if (0 == bits.compare("7")) {
        return mSerial->setDataBits(QSerialPort::Data7);
    } else if (0 == bits.compare("8")) {
        return mSerial->setDataBits(QSerialPort::Data8);
    }
    return false;
}

QString SerialOP::getStopBits(void) {
    switch (mSerial->stopBits()) {
    case QSerialPort::StopBits::OneStop:
        return "1";
    case QSerialPort::StopBits::OneAndHalfStop:
        return "1.5";
    case QSerialPort::StopBits::TwoStop:
        return "2";
    case QSerialPort::StopBits::UnknownStopBits:
        return "";
    }
    return "";
}

bool SerialOP::setStopBits(QString bits) {
    if (0 == bits.compare("1")) {
        return mSerial->setStopBits(QSerialPort::StopBits::OneStop);
    } else if (0 == bits.compare("1.5")) {
        return mSerial->setStopBits(QSerialPort::StopBits::OneAndHalfStop);
    } else if (0 == bits.compare("2")) {
        return mSerial->setStopBits(QSerialPort::StopBits::TwoStop);
    }
    return false;
}

QString SerialOP::getParity(void) {
    switch (mSerial->parity()) {
    case QSerialPort::Parity::NoParity:
        return "None";
    case QSerialPort::Parity::EvenParity:
        return "Even";
    case QSerialPort::Parity::OddParity:
        return "Odd";
    case QSerialPort::Parity::SpaceParity:
        return "Space";
    case QSerialPort::Parity::MarkParity:
        return "Mark";
    case QSerialPort::Parity::UnknownParity:
        return "";
    }
    return "";
}

bool SerialOP::setParity(QString bits) {
    if (0 == bits.compare("None", Qt::CaseInsensitive)) {
        return mSerial->setParity(QSerialPort::Parity::NoParity);
    } else if (0 == bits.compare("Even", Qt::CaseInsensitive)) {
        return mSerial->setParity(QSerialPort::Parity::EvenParity);
    } else if (0 == bits.compare("Odd", Qt::CaseInsensitive)) {
        return mSerial->setParity(QSerialPort::Parity::OddParity);
    } else if (0 == bits.compare("Space", Qt::CaseInsensitive)) {
        return mSerial->setParity(QSerialPort::Parity::SpaceParity);
    } else if (0 == bits.compare("Mark", Qt::CaseInsensitive)) {
        return mSerial->setParity(QSerialPort::Parity::MarkParity);
    }
    return false;
}

void SerialOP::setRecvCallabck(SERIAL_RECV_CALLBACK callback) {
    mRecvCallback = callback;
}

bool SerialOP::isOpen(void) {
    return mSerial->isOpen();
}

bool SerialOP::open(QString portName, QIODevice::OpenMode mode) {
    mSerial->setPortName(portName);
    if (mSerial->isOpen()) {
        mSerial->close();
    }
    if (mSerial->open(mode)) {
        return true;
    }
    return false;
}

void SerialOP::close(void) {
    if (mSerial->isOpen()) {
        mSerial->close();
    }
}

bool SerialOP::send(QByteArray data, int recvTimeout) {
    if (mSerial->isOpen() && (QIODevice::WriteOnly == mSerial->openMode() || QIODevice::ReadWrite == mSerial->openMode())) {
        if (mSerial->write(data) >= 0) {
            if (recvTimeout > 0) {
                static const int MIN_TIMEOUT = 10;
                 mSerial->waitForReadyRead(recvTimeout >= MIN_TIMEOUT ? recvTimeout : MIN_TIMEOUT);
            }
            return true;
        }
    }
    return false;
}

void SerialOP::recvSerialData(void) {
    QByteArray data = mSerial->readAll();
    if (mRecvCallback) {
        mRecvCallback(data);
    }
}
