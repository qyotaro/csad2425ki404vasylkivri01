#include "serialcommunication.h"
#include <QMessageBox>

SerialCommunication::SerialCommunication(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)) {
    connect(serial, &QSerialPort::readyRead, this, &SerialCommunication::readFromSerial);
}

SerialCommunication::~SerialCommunication() {
    if (serial->isOpen()) {
        serial->close();
    }
}

bool SerialCommunication::openSerialPort(const QString &portName, int baudRate) {
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        return false;
    }
    return true;
}

void SerialCommunication::sendMessage(const QString &message) {
    if (serial->isOpen()) {
        serial->write(message.toUtf8());
    }
}

void SerialCommunication::readFromSerial() {
    buffer.append(serial->readAll());

    int endIndex = buffer.indexOf('\n');
    while (endIndex != -1) {
        QString receivedMessage = QString::fromUtf8(buffer.left(endIndex).trimmed());
        emit messageReceived(receivedMessage);
        buffer.remove(0, endIndex + 1);
        endIndex = buffer.indexOf('\n');

        if (buffer.size() > 1024) {
            buffer.clear();
        }
    }
}
