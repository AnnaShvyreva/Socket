#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s1_in.bind(QHostAddress::LocalHost,6666); // ���������� ������ � ������ ��������
    connect(&s1_in,SIGNAL(readyRead()),this,SLOT(readData1()));

    s2_in.bind(QHostAddress::LocalHost,3333); // ���������� ������ �� ������ ��������
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


void MainWindow::readData(char i) //������ ����� �� ������� �������
{
    QByteArray arr;//, mass;

    switch (i) // ���� 1 - ��������� �� 1 �������, ���� 2 - ��������� �� 2 �������
    {
    case '1':
    {
        arr.resize(s1_in.pendingDatagramSize());
        s1_in.readDatagram(arr.data(),arr.size());
        // �������� ����� 2 �������
        s2_out.writeDatagram(arr,QHostAddress::LocalHost,4444);
        break;
    }
    case '2':
    {
        arr.resize(s2_in.pendingDatagramSize());
        s2_in.readDatagram(arr.data(),arr.size());
        // �������� ����� 1 �������
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
