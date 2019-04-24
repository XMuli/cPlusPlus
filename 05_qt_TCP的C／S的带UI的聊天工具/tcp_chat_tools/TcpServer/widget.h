#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>  //监听套接字
#include <QTcpSocket>  //通信套接字



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::Widget *ui;

    QTcpServer *pTcpServer;
    QTcpSocket *pTcpSocket;
};

#endif // WIDGET_H
