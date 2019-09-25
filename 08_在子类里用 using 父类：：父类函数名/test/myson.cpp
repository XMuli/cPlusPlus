#include "myson.h"
#include <QDebug>

MySon::MySon()
{

}

void MySon::fun(int n)
{
    qDebug()<<"派生类的 普通 同名不同参数函数 MySon::fun(int n)";
}

void MySon::fun02(int n)
{
    qDebug()<<"派生类的 重写 同名同参数的函数 MySon::fun02(int n)";
}
