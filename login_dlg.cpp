#include "login_dlg.h"
#include "ui_login_dlg.h"

#include <QMessageBox>

Login_Dlg::Login_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dlg)
{
    ui->setupUi(this);
}

Login_Dlg::~Login_Dlg()
{
    delete ui;
}

void Login_Dlg::on_login_clicked()
{
    if (ui->usr_Edit->text() == tr("xuy") && ui->password_Edit->text() == tr("123")) {
        accept();
    } else {
        QMessageBox::warning(this, tr("警告！"), tr("用户名或密码错误！"), QMessageBox::Yes);
        ui->usr_Edit->clear();
        ui->password_Edit->clear();
        ui->usr_Edit->setFocus();  // 定位光标到usr_Edit
    }
}
