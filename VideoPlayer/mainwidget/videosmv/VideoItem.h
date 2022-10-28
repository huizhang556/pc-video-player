#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QWidget>

namespace Ui {
class VideoItem;
}

class VideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit VideoItem(QWidget *parent = nullptr);
    explicit VideoItem(const QString& picPath, const QString& introduce, const QString& author, QWidget *parent = nullptr);
    ~VideoItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:


private:
    Ui::VideoItem *ui;
    QString     m_picPath;
    QString     m_intro;
    QString     m_author;

private:
    void        setItemPicture();
    void        setItemIntroduce();
    void        setItemAuthor();
};

#endif // VIDEOITEM_H
