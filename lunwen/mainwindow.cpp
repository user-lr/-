#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "WebEngineApp.h"
#include "webbrowser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dakai, &QAction::triggered, this, &MainWindow::dakaislot);
    auto widget = new WebBrowser();
    widget->load(QUrl("https://www.baidu.com"));
    this->setCentralWidget(widget);

    // 创建 WebEngineApp 实例
    webEngineApp = new WebEngineApp(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dakaislot()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("选择一个文件"), QCoreApplication::applicationFilePath(), "*.html");

    if (filename.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择正确的文件");
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << file.errorString();
        return;
    }

    QString htmlContent = file.readAll();
    file.close();

    // 使用 WebEngineApp 加载 HTML 文件
    webEngineApp->initWebEngineView(filename);  // 加载本地 HTML 文件
}
