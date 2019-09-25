#include <QCoreApplication>
#include "myson.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MySon mySon;
    mySon.fun(1);        //只一个"智能提示":是int类型

    mySon.fun();         //此(含自己)后面三个都是得益于 using My::fun; 而可以使用
    mySon.fun("str");    //仍然手写调用My::fun(QString)其他类型, 可以被调用
    mySon.fun(2, "ac");

    qDebug("");

    mySon.fun02(4);      //重写的那个函数,也是唯一的一个的"智能提示"的 int类型
    mySon.fun02();       //此(含自己)后面三个都是得益于 using My::fun02; 而可以使用
    mySon.fun02("ab");
    mySon.fun02(3, "test");

    return a.exec();
}
