#ifndef DLGCONTACTLIST_H
#define DLGCONTACTLIST_H

#include <QWidget>
#include <QToolButton>
#include <QVector>
#include "DlgGroupChat.h"


namespace Ui {
class DlgContactList;
}

class DlgContactList : public QWidget
{
    Q_OBJECT

public:
    explicit DlgContactList(QWidget *parent = nullptr);
    ~DlgContactList();

private:
    Ui::DlgContactList *ui;

    QVector<bool> m_vIsShow;  //标识是否打开群聊?
};

#endif // DLGCONTACTLIST_H
