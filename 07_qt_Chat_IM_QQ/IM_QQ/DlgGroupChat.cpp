#include "DlgGroupChat.h"
#include "ui_DlgGroupChat.h"
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>

DlgGroupChat::DlgGroupChat(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::DlgGroupChat)
{
    ui->setupUi(this);

    //初始化
    m_pUdpSocket = new QUdpSocket;
    m_strUserName = name;
    m_nPort = 9999;
    m_pUdpSocket->bind(this->m_nPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);  //共享地址+断开重连

    connect(ui->pbSend, &QPushButton::clicked, [=](){
        sendMsg(UserMsg);
    });

    sendMsg(UserEnter);

    connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &DlgGroupChat::recvMsg);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //字体
    connect(ui->fcbFont, &QFontComboBox::currentFontChanged, [=](const QFont &font){
       ui->teChatInput->setCurrentFont(font);
       ui->teChatInput->setFocus();
    });

    //字号
    void (QComboBox:: *cbxsingal)(const QString &text) = &QComboBox::currentIndexChanged;
    connect(ui->comboBox, cbxsingal, [=](const QString &text){
       ui->teChatInput->setFontPointSize(text.toDouble());
       ui->teChatInput->setFocus();
    });

    //加粗
    connect(ui->tbFontBold, &QToolButton::clicked, [=](bool isCheck){
        if(isCheck)
            ui->teChatInput->setFontWeight(QFont::Bold);
        else
            ui->teChatInput->setFontWeight(QFont::Normal);

        ui->teChatInput->setFocus();
    });

    //倾斜
    connect(ui->tbFontTilt, &QToolButton::clicked, [=](bool Check){
        ui->teChatInput->setFontItalic(Check);
        ui->teChatInput->setFocus();
    });

    //下划线
    connect(ui->tbFontUnderline, &QToolButton::clicked, [=](bool Check){
        ui->teChatInput->setFontUnderline(Check);
        ui->teChatInput->setFocus();
    });

    //字体颜色
    connect(ui->tbMark, &QToolButton::clicked, [=](){
        QColor color = QColorDialog::getColor(Qt::red);
        ui->teChatInput->setTextColor(color);
        ui->teChatInput->setFocus();
    });

    //保存聊天记录
    connect(ui->tbChatSave, &QToolButton::clicked, [=](){
        QString path = QFileDialog::getSaveFileName(this, "保存记录", "聊天记录", "(*.txt)");
        if(path.isEmpty()  || ui->tbChat->document()->isEmpty())
        {
            QMessageBox::warning(this, "警告", "路径或者内容不能为空");
            return;
        }
        else
        {
            QFile file(path);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream stream(&file);
            stream << ui->tbChat->toPlainText();
            file.close();
        }

        ui->teChatInput->clear();
        ui->teChatInput->setFocus();
    });

    //清空聊天记录
    connect(ui->tbChatClean, &QToolButton::clicked, [=](){
        ui->tbChat->clear();
        ui->teChatInput->setFocus();
    });





}

DlgGroupChat::~DlgGroupChat()
{
    delete ui;
}



void DlgGroupChat::closeEvent(QCloseEvent* e)
{
    emit this->closeDlgGroupChat();

    sendMsg(UserLeft);
    close();
}

void DlgGroupChat::sendMsg(DlgGroupChat::MsgType typeMsg)
{
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);

    stream << typeMsg;  //将类型加入到 流中

    switch (typeMsg)
    {
    case UserMsg:{
        if(ui->teChatInput->toPlainText().isEmpty())
        {
            QMessageBox::warning(this, "警告", "发送的消息不能为空");
            return;
        }

        //报文协1：类型+姓名+时间+内容
        QString time = QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss");
        QString msg = ui->teChatInput->toHtml();
        stream <<m_strUserName<<time<< msg;

        ui->teChatInput->clear();
        ui->teChatInput->setFocus();

    }break;
    case UserEnter:{
        //报文协议2：类型+姓名
        stream <<m_strUserName;
    }break;
    case UserLeft:{
        //报文协议3：类型+姓名
        stream <<m_strUserName;
    }break;
    default:
        break;
    }

    //书写报文，广播发送
    m_pUdpSocket->writeDatagram(array, QHostAddress::Broadcast, m_nPort);

}

void DlgGroupChat::userEnter(QString userName)
{
    bool isEmpty = ui->twUser->findItems(userName, Qt::MatchExactly).isEmpty();

    if(isEmpty)   //不存在才能添加显示
    {
        QTableWidgetItem* item = new QTableWidgetItem(userName);
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QTableWidgetItem* timeItem = new QTableWidgetItem(time);

        //插入行
        ui->twUser->insertRow(0);
        ui->twUser->setItem(0, 0, item);
        ui->twUser->setItem(0, 1, timeItem);

        //追加聊天记录
        ui->tbChat->setTextColor(Qt::gray);
        ui->tbChat->append(QString("%1 于 %2 上线了").arg(userName).arg(time));

        //在线人数更新
        ui->labCount->setText(QString("在线用户：%1人").arg(ui->twUser->rowCount()));
        sendMsg(UserEnter);

    }


}

void DlgGroupChat::userLeft(QString userName)
{
    bool isEmpty = ui->twUser->findItems(userName, Qt::MatchExactly).isEmpty();

    if(!isEmpty) //存在才能离开显示
    {
        int nRow = ui->twUser->findItems(userName, Qt::MatchExactly).first()->row();
        ui->twUser->removeRow(nRow);
        QString time = QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss");

        //追加聊天记录
        ui->tbChat->setTextColor(Qt::gray);
        ui->tbChat->append(QString("%1 于 %2 下线了").arg(userName).arg(time));

        //在线人数更新
        ui->labCount->setText(QString("在线用户：%1人").arg(ui->twUser->rowCount()));
    }
}



void DlgGroupChat::recvMsg()
{
    qint64 size = m_pUdpSocket->pendingDatagramSize();  //获取接收报文的长度
    QByteArray array = QByteArray(size, 0);
    m_pUdpSocket->readDatagram(array.data(), size);

    //解析报文协议：类型+姓名+时间+内容

    QString name;
    QString time;
    int typeMsg;
    QString Msg;
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> typeMsg >> name  >> time >> Msg;

    qDebug()<<size<<" recv=>"<<QString::fromLocal8Bit(array);

    switch (typeMsg)
    {
    case UserMsg:{
        ui->tbChat->setTextColor(Qt::blue);
        ui->tbChat->append("[" + name +"]" + time);
        ui->tbChat->append(Msg);
    }break;
    case UserEnter:{
        userEnter(name);

    }break;
    case UserLeft:{
        userLeft(name);
    }break;
    default:
        break;
    }

}

void DlgGroupChat::on_pbExit_clicked()
{
    sendMsg(UserLeft);
    close();
}
