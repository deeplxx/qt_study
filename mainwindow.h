#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newFile();  // 新建操作
    bool maybeSave();  // 判断是否需要保存
    bool save();  // 保存操作
    bool saveAs();  // 另存为操作
    bool saveFile(const QString &fileName);  // 保存文件

    bool loadFile(const QString &fileName);  // 打开操作


private slots:
//    void on_pushButton_2_clicked();

    void on_action_fn_triggered();

    void on_action_fs_triggered();

    void on_action_fa_triggered();

    void on_action_fo_triggered();

    void on_action_fc_triggered();

    void on_action_fx_triggered();

    void on_action_ez_triggered();

    void on_action_ex_triggered();

    void on_action_ec_triggered();

    void on_action_ev_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;  // 当前文件是否未保存
    QString currFilePath;  // 当前文件路径

protected:
    void closeEvent(QCloseEvent *event);  // 关闭事件(按下了程序的关闭按钮比)
};

#endif // MAINWINDOW_H
