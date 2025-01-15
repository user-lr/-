#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWebEngineView>
#include <QWebEnginePage>

class CustomWebEnginePage : public QWebEnginePage {
    Q_OBJECT
public:
    CustomWebEnginePage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) override {
        if (isMainFrame && type == NavigationType::NavigationTypeLinkClicked) {
            emit linkClicked(url);  // 发射信号
            return false; // 返回 false 以阻止默认行为
        }
        return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
    }

signals:
    void linkClicked(const QUrl &url);
};

class WebBrowser : public QWebEngineView {
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = nullptr);
    ~WebBrowser();

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

signals:
    void urlChanged(const QUrl &url);

private slots:
    void OnUrlChanged(QUrl url);
};

#endif // WEBBROWSER_H
