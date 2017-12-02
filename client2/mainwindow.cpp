#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_in.bind(QHostAddress::LocalHost,4444); //устанавливаем соединение с сервером (прием с сервера)
    connect(&s_in,SIGNAL(readyRead()),this,SLOT(readData())); // читаем данные с сервера
}

void MainWindow::readData()
{
    QByteArray arr, mass;
    arr.resize(s_in.pendingDatagramSize());
    s_in.readDatagram(arr.data(),arr.size());

    QDataStream in(arr);
    in>>mass; //читаем полученные данные

    QString str = QString::fromAscii(mass.data()); // преобразуем данные из байтового вида в строку
    qDebug()<<str;//"mass from client1 is came";

    ui->textEdit->setText(str); //выводим на форму

    update();
}

void MainWindow::on_pushButton_clicked() // симулируем трафик нажатием на кнопку
{

    send_signal(); // отправляем сигнал
}

void MainWindow::send_signal()
{
    QByteArray arr;
    QDataStream out(&arr,QIODevice::WriteOnly);
    out<<"here is my data from client 2"; // формируем данные для передачи
    qDebug()<<"mass to server is send"; // информационное сообщение в консоль о передаче
    s_out.writeDatagram(arr,QHostAddress::LocalHost,3333);// передача данных на сервер

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
