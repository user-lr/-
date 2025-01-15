#include "WebEngineApp.h"
#include <QWebEngineView>
#include <QWebChannel>
#include <QDebug>

WebEngineApp::WebEngineApp(QObject *parent) : QObject(parent)
{
    // 创建 QWebEngineView 和 QWebChannel
    view = new QWebEngineView();
    channel = new QWebChannel();
    qtObject = new QtObject();

    // 将 QtObject 注册到 WebChannel
    channel->registerObject("QtObject", qtObject);

    // 设置页面的 WebChannel
    view->page()->setWebChannel(channel);

    // 连接 QtObject 的信号，以便在 Qt 中接收到修改后的内容后返回给 HTML 页面
    //  QObject::connect(qtObject, &QtObject::sendToHtml, [this](const QString &content) {
    //     //view->page()->runJavaScript("xxx(ss);");
    //     view->page()->runJavaScript("xxx('" + content + "');");
    // });//毫无用处
}

void WebEngineApp::initWebEngineView(const QString &htmlFilePath)
{
    // 加载 HTML 文件
    view->setUrl(QUrl::fromLocalFile(htmlFilePath));
    view->show();
}
