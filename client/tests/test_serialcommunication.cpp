#include <QtTest>
#include "../serialcommunication.h"

class MockSerialCommunication : public SerialCommunication {
public:
    MockSerialCommunication() {
    }
    bool openSerialPort(const QString &portName, int baudRate)  {
        return true;
    }

    void sendMessage(const QString &message)  {
        emit messageReceived(message);
    }

    void readFromSerial()  {
        if (!buffer.isEmpty()) {
            emit messageReceived(QString::fromUtf8(buffer));
            buffer.clear();
        }
    }
};

class TestSerialCommunication : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSendMessage();
    void testReceiveMessage();

private:
    MockSerialCommunication *serialComm;
};

void TestSerialCommunication::initTestCase() {
    serialComm = new MockSerialCommunication();
}

void TestSerialCommunication::cleanupTestCase() {
    delete serialComm;
}

void TestSerialCommunication::testSendMessage() {
    QString message = "Hello Arduino\n";
    QSignalSpy spy(serialComm, &SerialCommunication::messageReceived);

    serialComm->sendMessage(message);

    QVERIFY(spy.count() == 1);
    QCOMPARE(spy.takeFirst().at(0).toString(), message);
}

void TestSerialCommunication::testReceiveMessage() {
    QString message = "Message from Arduino\n";
    QSignalSpy spy(serialComm, &SerialCommunication::messageReceived);

    serialComm->buffer.append(message.toUtf8());
    serialComm->readFromSerial();

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QString receivedMessage = arguments.at(0).toString();
    QCOMPARE(receivedMessage, message);
}

QTEST_MAIN(TestSerialCommunication)
#include "test_serialcommunication.moc"
