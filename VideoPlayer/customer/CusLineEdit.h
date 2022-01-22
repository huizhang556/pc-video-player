#ifndef CUSLINEEDIT_H
#define CUSLINEEDIT_H

#include <QWidget>
#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFocusEvent>


class CusLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CusLineEdit(QWidget *parent = nullptr);
    ~CusLineEdit();

    void setLineEditText(QString str);

    QString getLineEditText();//获取输入框内容

    void setFixSize(QSize size);//设置整体大小

    void setLineEditSize(QSize size);//设置输入框固定大小

    void setLineEditMinSize(QSize size);//设置输入框最小大小

    void setButtonSize(QSize size);//设置搜索按钮固定大小

    void setButtonMinSize(QSize size);//设置搜索按钮最小大小

    void setSearchButtonText(QString str);//设置输搜索按钮文字

    void setSearchLineEditText(const QString text);//设置输入框文字

    void setSearchHidden(bool hide);//搜索按钮隐藏且不可使用

    void setLineEditHidden(bool hide);//设置输入框隐藏

    void addLineEditAction(QIcon icon, QString str);//输入框添加action

    void setLineEditPlaceholderText(QString str);//输入框提示文

    void setLineEditValidator(const QValidator *regx);//输入框输入的正则表达式

    void setLineEditStyleSheet(const QString str);//输入框的样式

    void setButtonStyleSheet(const QString str);//设置按钮的样式

//    void showLineEditHistory(bool show);//控制历史记录搜索框的显隐

    void lineEditClear();//输入框的文字清理

    void initHistoryUI();//初始化历史记录UI

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:

    void setHistoryUiHidden(bool hide);//设置历史记录UI显隐

signals:

private slots:

    QString slots_lineEditTextChange(const QString & str);


private:
    QLineEdit       *m_lineEdit = nullptr;
    QPushButton     *m_button = nullptr;
    QVBoxLayout     *vlayout = nullptr;
    QWidget         *widget = nullptr;

};

#endif // CUSLINEEDIT_H
