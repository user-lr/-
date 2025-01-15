#ifndef QTOBJECT_H
#define QTOBJECT_H

#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>

class QtObject : public QObject
{
    Q_OBJECT

public:
    explicit QtObject(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void sendToHtml(const QString &content);

public slots:
    void updateContent(const QString &content) {

        QProcess *process = new QProcess(this);  // 创建 QProcess 对象

        QObject::connect(process, &QProcess::finished, [this, process](int exitCode, QProcess::ExitStatus /*exitStatus*/) {
            QByteArray output = process->readAllStandardOutput();
            QByteArray errorOutput = process->readAllStandardError();

            QString outputString = QString::fromLocal8Bit(output);
            QString errorString = QString::fromLocal8Bit(errorOutput);
            QString mm=QString::number(exitCode);

            qDebug() << "Process finished with exit code:" << exitCode;
            qDebug() << "Sending to HTML: " << outputString + errorString;

            emit sendToHtml("输出:"+outputString + errorString+"exitcode:"+mm);//内容改变

            if (exitCode != 0) {
                qDebug() << "Error Output: " << errorString;
                QMessageBox::critical(nullptr, "Error", "Process failed: " + errorString);
            }
            process->deleteLater();
        });

        QString program = "cmd";
        QStringList arguments;
        arguments << "/C" << content;


        //arguments << "D:/Cisco Packet Tracer 8.2.2";

        process->start(program, arguments);
        if (!process->waitForFinished()) {
            qDebug() << "Process failed to start or finish.";
            QMessageBox::critical(nullptr, "Error", "Failed to start or finish the process.");
            process->deleteLater();
            return;
        }
    }
};

#endif // QTOBJECT_H
