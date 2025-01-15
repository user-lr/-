#ifndef CUSTOMWEBENGINEPAGE_H
#define CUSTOMWEBENGINEPAGE_H

#include <QWebEnginePage>

class CustomWebEnginePage : public QWebEnginePage
{
    Q_OBJECT  // 确保这里有 Q_OBJECT 宏

public:
    explicit CustomWebEnginePage(QObject *parent = nullptr);

signals:
    void linkClicked(const QUrl &url);  // 自定义信号

protected:
    void linkHovered(const QString &link) ;
};

#endif // CUSTOMWEBENGINEPAGE_H
