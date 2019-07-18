#ifndef IM_QQ_H
#define IM_QQ_H

#include <QWidget>

namespace Ui {
class IM_QQ;
}

class IM_QQ : public QWidget
{
    Q_OBJECT

public:
    explicit IM_QQ(QWidget *parent = nullptr);
    ~IM_QQ();

private:
    Ui::IM_QQ *ui;
};

#endif // IM_QQ_H
