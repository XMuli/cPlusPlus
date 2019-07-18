#include "IM_QQ.h"
#include "ui_IM_QQ.h"

IM_QQ::IM_QQ(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IM_QQ)
{
    ui->setupUi(this);
}

IM_QQ::~IM_QQ()
{
    delete ui;
}
