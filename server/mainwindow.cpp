#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s1_in.bind(QHostAddress::LocalHost,6666); // соединение чтения с первым клиентом
    connect(&s1_in,SIGNAL(readyRead()),this,SLOT(readData1()));

    s2_in.bind(QHostAddress::LocalHost,3333); // соединение чтения со вторым клиентом
    connect(&s2_in,SIGNAL(readyRead()),this,SLOT(readData2()));
}

void MainWindow::readData1()
{
    readData('1');
}

void MainWindow::readData2()
{
    readData('2');
}


void MainWindow::readData(char i) //читаем пакет от первого клиента
{
    QByteArray arr;//, mass;

    switch (i) // если 1 - сообщение от 1 клиента, если 2 - сообщение от 2 клиента
    {
    case '1':
    {
        arr.resize(s1_in.pendingDatagramSize());
        s1_in.readDatagram(arr.data(),arr.size());
        // передаем пакет 2 клиенту
        s2_out.writeDatagram(arr,QHostAddress::LocalHost,4444);
        break;
    }
    case '2':
    {
        arr.resize(s2_in.pendingDatagramSize());
        s2_in.readDatagram(arr.data(),arr.size());
        // передаем пакет 1 клиенту
        s1_out.writeDatagram(arr,QHostAddress::LocalHost,5555);
        break;
    }

    }
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
