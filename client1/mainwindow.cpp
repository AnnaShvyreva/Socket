#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_in.bind(QHostAddress::LocalHost,5555); //устанавливаем соединение с сервером (прием с сервера)
    connect(&s_in,SIGNAL(readyRead()),this,SLOT(readData())); // читаем данные с сервера
}

void MainWindow::readData()
{
    QByteArray arr, mass;
    arr.resize(s_in.pendingDatagramSize());
    s_in.readDatagram(arr.data(),arr.size()); // читаем данные из пакета

    QDataStream in(arr);
    in>>mass;

    QString str = QString::fromAscii(mass.data()); // преобразуем данные к строке
    qDebug()<<str; // выводим данные в консоль

    ui->textEdit->setText(str); //выводим на форму

    update();
}

void MainWindow::on_clearButton_clicked()
{
    send_signal();
}

void MainWindow::send_signal()
{
    QByteArray arr;
    QDataStream out(&arr,QIODevice::WriteOnly);
    out<<"here is my data from client 1"; //формируем данные для отправки на сервер
    qDebug()<<"mass to server is send"; // информация в консоль об отправке данных на сервер
    s_out.writeDatagram(arr,QHostAddress::LocalHost,6666); //отправляем данные на сервер

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
