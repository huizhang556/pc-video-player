#ifndef MEDIALOADSTATUS_H
#define MEDIALOADSTATUS_H

#include <QWidget>

namespace Ui {
class MediaLoadStatus;
}

class MediaLoadStatus : public QWidget
{
    Q_OBJECT

public:
    explicit MediaLoadStatus(QWidget *parent = nullptr);
    ~MediaLoadStatus();

private:
    Ui::MediaLoadStatus *ui;
};

#endif // MEDIALOADSTATUS_H
