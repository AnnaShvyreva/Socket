#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_in.bind(QHostAddress::LocalHost,4444); //������������� ���������� � �������� (����� � �������)
    connect(&s_in,SIGNAL(readyRead()),this,SLOT(readData())); // ������ ������ � �������
}

void MainWindow::readData()
{
    QByteArray arr, mass;
    arr.resize(s_in.pendingDatagramSize());
    s_in.readDatagram(arr.data(),arr.size());

    QDataStream in(arr);
    in>>mass; //������ ���������� ������

    QString str = QString::fromAscii(mass.data()); // ����������� ������ �� ��������� ���� � ������
    qDebug()<<str;//"mass from client1 is came";

    ui->textEdit->setText(str); //������� �� �����

    update();
}

void MainWindow::on_pushButton_clicked() // ���������� ������ �������� �� ������
{

    send_signal(); // ���������� ������
}

void MainWindow::send_signal()
{
    QByteArray arr;
    QDataStream out(&arr,QIODevice::WriteOnly);
    out<<"here is my data from client 2"; // ��������� ������ ��� ��������
    qDebug()<<"mass to server is send"; // �������������� ��������� � ������� � ��������
    s_out.writeDatagram(arr,QHostAddress::LocalHost,3333);// �������� ������ �� ������

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
