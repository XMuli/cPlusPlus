#include "IM_QQ.h"
#include <QApplication>
#include "DlgContactList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    IM_QQ w;
//    w.show();

    DlgContactList dlgList;
    dlgList.show();






    return a.exec();
}
