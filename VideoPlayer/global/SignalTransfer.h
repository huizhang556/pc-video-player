#ifndef SIGNALTRANSFER_H
#define SIGNALTRANSFER_H

#include <QObject>



/*此类做信号中转使用*/
class SignalTransfer : public QObject
{
    Q_OBJECT
public:
    explicit SignalTransfer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SIGNALTRANSFER_H
