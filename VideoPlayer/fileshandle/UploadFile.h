#ifndef UPLOADFILE_H
#define UPLOADFILE_H

#include <QWidget>

namespace Ui {
class UploadFile;
}

class UploadFile : public QWidget
{
    Q_OBJECT

public:
    explicit UploadFile(QWidget *parent = nullptr);
    ~UploadFile();


private:
    Ui::UploadFile *ui;
};

#endif // UPLOADFILE_H
