#include "webbrowser.h"
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>

WebBrowser::WebBrowser(QWidget* parent) : QWebEngineView(parent) {
    CustomWebEnginePage *page = new CustomWebEnginePage(this);
    setPage(page);

    connect(page, &CustomWebEnginePage::linkClicked, this, [](const QUrl &url) {
        qDebug() << "链接被点击:" << url;

        // 弹出对话框显示可点击链接
        QMessageBox msgBox;
        msgBox.setWindowTitle("链接被点击");

        // 设置文本和添加可点击链接
        QString message = QString("你点击的链接是: <a href=\"%1\">%1</a>").arg(url.toString());
        msgBox.setTextFormat(Qt::RichText);
        msgBox.setText(message);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

        // 显示对话框并等待操作
        int ret = msgBox.exec();

        // 选择来决定是否打开链接
        if (ret == QMessageBox::Ok) {
            QDesktopServices::openUrl(url); // 打开链接
        }
        // 如果点击了取消，什么也不做
    });
    connect(this, &QWebEngineView::urlChanged, this, &WebBrowser::OnUrlChanged);

}

WebBrowser::~WebBrowser() {
}

QWebEngineView *WebBrowser::createWindow(QWebEnginePage::WebWindowType type) {
    Q_UNUSED(type);

    WebBrowser *webBrowser = new WebBrowser();
    webBrowser->setAttribute(Qt::WA_DeleteOnClose);

    return webBrowser;
}

void WebBrowser::OnUrlChanged(QUrl url) {
    qDebug() << "url changed " << url;
}
