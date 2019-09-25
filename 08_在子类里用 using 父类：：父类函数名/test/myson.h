#ifndef MYSON_H
#define MYSON_H
#include "my.h"


class MySon : public My
{
public:
    MySon();
    void fun(int n);

    virtual void fun02(int n) override;

    using My::fun;    //本篇所讲
    using My::fun02;  //本篇所讲
};

#endif // MYSON_H
