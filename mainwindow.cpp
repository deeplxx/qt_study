#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText(tr("新窗口"));

    isUntitled = true;
    currFilePath = tr("未命名.txt");
    setWindowTitle(currFilePath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButton_2_clicked()
//{
//    QDialog *dlg = new QDialog(this);
//    dlg->show();
//}

void MainWindow::newFile()
{
    if (maybeSave()) {
        isUntitled = true;
        currFilePath = tr("未命名.txt");
        setWindowTitle(currFilePath);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave()
{
    if (ui->textEdit->document()->isModified()) {
        QMessageBox warningBox;
        warningBox.setWindowTitle(tr("警告"));
        warningBox.setIcon(QMessageBox::Warning);
        warningBox.setText(tr("尚未保存，是否保存？"));
        QPushButton *yesBtn = warningBox.addButton(tr("是(&Y)"), QMessageBox::YesRole);
        warningBox.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = warningBox.addButton(tr("取消(&C)"), QMessageBox::RejectRole);
        warningBox.exec();  //显示窗口

        if (warningBox.clickedButton() == yesBtn)
            return save();
        else if (warningBox.clickedButton() == cancelBtn)  // 只有点击取消才设置为false
            return false;
    }

    // 没被更改则直接返回 true
    return true;
}

bool MainWindow::save()
{
    if (isUntitled)
        return saveAs();
    else
        return saveFile(currFilePath);
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为:"), currFilePath);  // 实现了一个另存为对话框

    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法写入文件%1:/n %2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);  // 鼠标指针设置为等待状态
    out << ui->textEdit->toPlainText();  // 将编辑器中内容输出到out流中
    QApplication::restoreOverrideCursor();  // 鼠标指针恢复原状态

    isUntitled = false;
    currFilePath = QFileInfo(fileName).canonicalFilePath();  //获取当前文件的标准路径
    setWindowTitle(currFilePath);
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n %2").arg(fileName).arg(file.errorString()));
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit_2->setPlainText(in.readAll());  // 读取in流的所有内容并添加到编辑器
    QApplication::restoreOverrideCursor();

    currFilePath = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(currFilePath);

    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

/**
 槽调用
*/


void MainWindow::on_action_fn_triggered()
{
    newFile();
}

void MainWindow::on_action_fs_triggered()
{
    save();
}

void MainWindow::on_action_fa_triggered()
{
    saveAs();
}

void MainWindow::on_action_fo_triggered()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);  // 创建一个打开对话框
        if (!fileName.isEmpty()) {
            loadFile(fileName);
            ui->textEdit_2->setVisible(true);
        }
    }
}

void MainWindow::on_action_fc_triggered()
{
    if(maybeSave()) {
        ui->textEdit_2->setVisible(false);
    }
}

void MainWindow::on_action_fx_triggered()
{
    on_action_fc_triggered();
    qApp->quit();  // 指向应用程序的全局指针
}

void MainWindow::on_action_ez_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_ex_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_ec_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_ev_triggered()
{
    ui->textEdit->paste();
}
