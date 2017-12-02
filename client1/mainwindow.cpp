#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_in.bind(QHostAddress::LocalHost,5555); //������������� ���������� � �������� (����� � �������)
    connect(&s_in,SIGNAL(readyRead()),this,SLOT(readData())); // ������ ������ � �������
}

void MainWindow::readData()
{
    QByteArray arr, mass;
    arr.resize(s_in.pendingDatagramSize());
    s_in.readDatagram(arr.data(),arr.size()); // ������ ������ �� ������

    QDataStream in(arr);
    in>>mass;

    QString str = QString::fromAscii(mass.data()); // ����������� ������ � ������
    qDebug()<<str; // ������� ������ � �������

    ui->textEdit->setText(str); //������� �� �����

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
    out<<"here is my data from client 1"; //��������� ������ ��� �������� �� ������
    qDebug()<<"mass to server is send"; // ���������� � ������� �� �������� ������ �� ������
    s_out.writeDatagram(arr,QHostAddress::LocalHost,6666); //���������� ������ �� ������

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
