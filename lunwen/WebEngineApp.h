#ifndef WEBENGINEAPP_H
#define WEBENGINEAPP_H

#include <QObject>
#include <QWebEngineView>
#include <QWebChannel>
#include "QtObject.h"

class WebEngineApp : public QObject
{
    Q_OBJECT
public:
    explicit WebEngineApp(QObject *parent = nullptr);
    void initWebEngineView(const QString &htmlFilePath);

private:
    QWebEngineView *view;
    QWebChannel *channel;
    QtObject *qtObject;
};

#endif // WEBENGINEAPP_H
