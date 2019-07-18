#include "DlgContactList.h"
#include "ui_DlgContactList.h"
#include <QDebug>

DlgContactList::DlgContactList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DlgContactList)
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("QQ轻聊版 2019"));
    setWindowIcon(QPixmap(":/images/19.ico"));



    QList<QString> nameList;
    nameList<<"明月清风"<<"上善若水"<<"自由如风"<<"五行缺钱"<<"浅笑心柔"<<"我的意中人是个盖世英雄"
            <<"洪荒少女"<<"风继续吹"<<"信仰改不了信念"<<"凡人多烦事"<<"不瘦十斤不改名字"<<"~正在缓冲99%"
           <<"狂吃不胖没办法"<<"全能吃货不挑食"<<"你若安好便是晴天"<<"本人太帅名字无法显示"<<"微微一笑很倾城"<<"执子之手";


    QVector<QToolButton*> vToolBtn;


    for (int i = 0; i < 18; i++)
    {
        //添加头像
        QToolButton* pBtn = new QToolButton;
        pBtn->setText(nameList[i]);
        QString str = QString(":/images/%1.jpg").arg(i+1);
        pBtn->setIcon(QPixmap(str));
        pBtn->setIconSize(QPixmap(str).size());
        pBtn->setAutoRaise(true);
        pBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pBtn->setFixedWidth(248);  // (QPixmap(str).height(), ui->vLayout->widget());
        ui->vLayout->addWidget(pBtn);

        vToolBtn.push_back(pBtn);//好友按钮保存到容器，便于其他地方操作
        m_vIsShow.push_back(false);
    }



    //为每一个按钮都创建一个系统聊天对话框
    for (int i = 0; i < vToolBtn.size(); i++)
    {
        connect(vToolBtn[i], &QToolButton::clicked, [=]() {
            if(m_vIsShow[i])
                return;

            m_vIsShow[i] = true;
            DlgGroupChat* pDlgGroupChat = new DlgGroupChat(nullptr, vToolBtn[i]->text());
            pDlgGroupChat->setWindowTitle(vToolBtn[i]->text());
            pDlgGroupChat->setWindowIcon(vToolBtn[i]->icon());
            pDlgGroupChat->show();

            connect(pDlgGroupChat, &DlgGroupChat::closeDlgGroupChat, [=](){
                m_vIsShow[i] = false;
            });
        });
    }


}

DlgContactList::~DlgContactList()
{
    delete ui;
}





