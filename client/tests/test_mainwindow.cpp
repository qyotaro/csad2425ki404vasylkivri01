#include <QtTest>
#include "../serialcommunication.h"

class TestSerialCommunication : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();    
    void cleanupTestCase(); 

    void testOpenSerialPort();      
    void testSendMessage();         
    void testReceiveMessage();      

private:
    SerialCommunication *serialComm;
};

void TestSerialCommunication::initTestCase() {
    serialComm = new SerialCommunication();
}

void TestSerialCommunication::cleanupTestCase() {
    delete serialComm;
}

void TestSerialCommunication::testOpenSerialPort() {
    QString portName = "COM3"; 
    bool result = serialComm->openSerialPort(portName, 9600);
    QVERIFY(result == true);
}

void TestSerialCommunication::testSendMessage() {
    QString message = "Hello Arduino\n";

    QSignalSpy spy(serialComm, &SerialCommunication::messageReceived);

    serialComm->sendMessage(message);

    QVERIFY(spy.count() == 0);
}

void TestSerialCommunication::testReceiveMessage() {
    QString message = "Message from Arduino\n";
    QSignalSpy spy(serialComm, &SerialCommunication::messageReceived);

    serialComm->buffer.append(message.toUtf8());
    serialComm->readFromSerial();

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QString receivedMessage = arguments.at(0).toString();
    QCOMPARE(receivedMessage, "Message from Arduino");
}


QTEST_MAIN(TestSerialCommunication)
#include "test_mainwindow.moc"
