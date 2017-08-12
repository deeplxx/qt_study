#include "mainwindow.h"
#include "login_dlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login_Dlg dlg;
    if (dlg.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    } else {
        return 0;
    }

//    w.show();

//    return a.exec();
}
