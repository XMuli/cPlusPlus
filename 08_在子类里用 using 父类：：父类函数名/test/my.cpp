#include "my.h"
#include <QDebug>

My::My()
{

}

void My::fun()
{
    qDebug()<<"基类的 普通函数 My::fun()";
}

void My::fun(int n)
{
    qDebug()<<"基类的 普通函数 My::fun(int n)";
}

void My::fun(QString str)
{
    qDebug()<<"基类的 普通函数 My::fun(QSting str)";
}

void My::fun(int n, QString str)
{
    qDebug()<<"基类的 普通函数 My::fun(int n, QString str)";
}

void My::fun02()
{
    qDebug()<<"基类的 虚函数 My::fun02()";
}

void My::fun02(int n)
{
    qDebug()<<"基类的 虚函数 My::fun02(int n)";
}

void My::fun02(QString str)
{
    qDebug()<<"基类的 虚函数 My::fun02(QString str)";
}

void My::fun02(int n, QString str)
{
    qDebug()<<"基类的 虚函数 My::fun02(int n, QString str)";
}


