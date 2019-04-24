#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //避免一开始用户点击Send按钮，结果程序会无法正常运行
    pTcpServer = NULL;
    pTcpSocket = NULL;


    //指定父对象，让其自动回收该区域的空间
    pTcpServer = new QTcpServer(this);

    //绑定当前网卡的所有IP，和监听的端口
    pTcpServer->listen(QHostAddress::Any, 8888);

    //只要一建立连接成功，就会自动触发newConnection函数
    connect(pTcpServer, &QTcpServer::newConnection,
            [=]()
            {
                //取出建立好的连接套接字
                pTcpSocket = pTcpServer->nextPendingConnection();

                //获得客户端的IP和端口
                QString ip = pTcpSocket->peerAddress().toString();
                qint16 port = pTcpSocket->peerPort();
                QString temp = QString("[%1:%2]:The client connection is successful.").arg(ip).arg(port);

                ui->textEditRead->setText(temp);


                //-----------------------------------------------------------------------------------------------
                //接收到了内容之后，直接在显示区域显示消息
                /**/ connect(pTcpSocket, &QTcpSocket::readyRead,
                /**/        [=]()
                /**/        {
                /**/           //从通信套接字中间取出内容
                /**/           QByteArray array = pTcpSocket->readAll();
                /**/           //QString temp2 = QString("");
                /**/           ui->textEditRead->append("[Client:]" + array); //在后面追加新的消息
                /**/        }
                /**/        );
                //-----------------------------------------------------------------------------------------------
            }
            );

    connect(ui->pushButtonSend, &QPushButton::pressed,
           [=]()
           {
              QString str = "[Server:]" + ui->textEditWrite->toPlainText();
              ui->textEditRead->append(str); //在后面追加新的消息
           }
           );

    this->setWindowTitle("TcpServer");


}

Widget::~Widget()
{
    delete ui;
}

//给客户端发送消息的功能
void Widget::on_pushButtonSend_clicked()
{
    //获取编辑区域的内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送消息,当有中文的时候就是用使用utf8
    pTcpSocket->write(str.toUtf8().data());
}

//断开连接,拒绝接受来自客户端的消息
void Widget::on_pushButtonClose_clicked()
{
    pTcpSocket->disconnectFromHost();
    pTcpSocket->close();
}
