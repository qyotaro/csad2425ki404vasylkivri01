#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>

class MockSerialCommunication;
class TestSerialCommunication;

class SerialCommunication : public QObject {
    Q_OBJECT

public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();

    bool openSerialPort(const QString &portName, int baudRate);
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);

private slots:
    void readFromSerial();

private:
    QSerialPort *serial;
    QByteArray buffer;

    friend class MockSerialCommunication;
    friend class TestSerialCommunication;
};

#endif // SERIALCOMMUNICATION_H
