#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QPushButton>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket s_in, s_out;

    void send_signal();

private slots:
    void on_clearButton_clicked(); //�������� ������� � ������� 1
    void readData(); // ������ ������� � �������
};

#endif // MAINWINDOW_H
