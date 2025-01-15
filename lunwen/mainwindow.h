#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "WebEngineApp.h"  // 包含 WebEngineApp 头文件

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dakaislot();

private:
    Ui::MainWindow *ui;
    WebEngineApp *webEngineApp;  // WebEngineApp 实例
};

#endif // MAINWINDOW_H
