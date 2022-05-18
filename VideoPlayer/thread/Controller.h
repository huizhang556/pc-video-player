#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "thread/Worker.h"
#include "browser/NewWork.h"
#include <QThread>
#include <QObject>
#include <QWebEngineDownloadItem>
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

public slots:


private:
    QThread     *workerThread = nullptr;
    Worker      *worker       = nullptr;
    NewWork     *NewWork      = nullptr;
signals:
    void    sig_operate(const QString &);
};

#endif // CONTROLLER_H
