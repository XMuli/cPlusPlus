#ifndef DLGGROUPCHAT_H
#define DLGGROUPCHAT_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class DlgGroupChat;
}

class DlgGroupChat : public QWidget
{
    Q_OBJECT

    enum MsgType {UserMsg, UserEnter, UserLeft};  //消息类型


public:
    explicit DlgGroupChat(QWidget *parent, QString name);
    ~DlgGroupChat();

signals:
    void closeDlgGroupChat(); //关闭窗口发送的信息

public:
    void closeEvent(QCloseEvent*);  //关闭事件

    void sendMsg(MsgType typeMsg);  //发送udp广播
    void userEnter(QString userName);  //用户加入
    void userLeft(QString userName);  //用户离开

private slots:
    void on_pbExit_clicked();

private:
    void recvMsg();  //接收udp广播消息

private:
    Ui::DlgGroupChat *ui;

    QUdpSocket* m_pUdpSocket;
    qint16 m_nPort;
    QString m_strUserName;
};

#endif // DLGGROUPCHAT_H
