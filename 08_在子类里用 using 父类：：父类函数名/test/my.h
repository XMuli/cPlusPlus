#ifndef MY_H
#define MY_H
#include <QString>


class My
{
public:
    My();

    void fun();
    void fun(int n);
    void fun(QString str);
    void fun(int n, QString str);

    virtual void fun02();
    virtual void fun02(int n);
    virtual void fun02(QString str);
    virtual void fun02(int n, QString str);
};

#endif // MY_H
