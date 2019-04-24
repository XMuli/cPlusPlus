#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *pTcpSocket;
};

#endif // WIDGET_H
