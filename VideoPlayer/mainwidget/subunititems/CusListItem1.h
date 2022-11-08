#ifndef CUSLISTITEM1_H
#define CUSLISTITEM1_H

#include <QWidget>
#include <QFont>
#include <QFontMetrics>

namespace Ui {
class CusListItem1;
}

class CusListItem1 : public QWidget
{
    Q_OBJECT

public:
    explicit CusListItem1(QWidget *parent = nullptr);
    explicit CusListItem1(const QString& first,const QString& second,  QWidget *parent = nullptr);
    ~CusListItem1();
    void    initWorkUI();
    void    setFirstPageText();
    void    setSecondTopText();
    void    setSecondBottomText();

public slots:
    void    slot_setCurrentItemPage(int index);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void    setFontSize(int size);
    void    setFontFamily(const QString& family);


private:
    Ui::CusListItem1 *ui;
    QString     m_firstText;
    QString     m_secTopText;
    QString     m_secBomText;
    QFont       m_font;//字体
    int         m_fontScale;//字体缩放比例

signals:
    void    sig_itemEnter();
    void    sig_itemLeave();
};

#endif // CUSLISTITEM1_H
