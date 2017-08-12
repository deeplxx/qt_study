#ifndef LOGIN_DLG_H
#define LOGIN_DLG_H

#include <QDialog>

namespace Ui {
class Login_Dlg;
}

class Login_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Dlg(QWidget *parent = 0);
    ~Login_Dlg();

private:
    Ui::Login_Dlg *ui;

private slots:
    void on_login_clicked();
};

#endif // LOGIN_DLG_H
