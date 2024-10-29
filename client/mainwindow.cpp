#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serialComm(new SerialCommunication(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Task2 SW(Client)");

    if (!serialComm->openSerialPort("COM3", 9600)) {
        QMessageBox::critical(this, "Error", "Unable to open the serial port!");
    }

    connect(serialComm, &SerialCommunication::messageReceived, this, &MainWindow::handleReceivedMessage);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sendButton_clicked() {
    QString message = ui->inputText->text();
    serialComm->sendMessage(message);
    ui->logText->append("Send:\n" + message);
}

void MainWindow::handleReceivedMessage(const QString &message) {
    ui->logText->append("\nReceived:\n" + message);
}
