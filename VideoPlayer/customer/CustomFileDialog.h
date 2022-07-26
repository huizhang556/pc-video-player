#ifndef CUSTOMFILEDIALOG_H
#define CUSTOMFILEDIALOG_H

#include <QFileDialog>
#include "ui_CustomFileDialog.h"

class QFileDialog;

class CustomFileDialog : public QDialog
{
	Q_OBJECT

public:
	CustomFileDialog(QWidget *parent = 0);
	~CustomFileDialog();

public:
	QStringList selectedFiles() const;
	void setFileMode(QFileDialog::FileMode mode);
    void setDirectory(const QString &directory);
    void setNameFilter(const QString &filter);
    void setNameFilters(const QStringList &filter);
    void setTitleName(const QString& titleName);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);

private slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onAccepted();
	void onRejected();
	void onFileDialogFinished(int);

private:

private:
	QFileDialog* m_fileDialog;
	Ui_CustomFileDialogClass ui;
};

#endif // CUSTOMFILEDIALOG_H
