#pragma once

#include <QtWidgets/QWidget>
#include "ui_CaptureTest.h"

class CaptureScreen;
class CaptureTest : public QWidget
{
	Q_OBJECT

public:
	CaptureTest(QWidget *parent = Q_NULLPTR);

private:
	// 监控键盘事件;
	void keyPressEvent(QKeyEvent *event);
	// 按下Ctrl + Alt + D键;键，开始截图;
	void startCatureImage();
private slots:
	// 显示在界面上;
	void onCompleteCature(QPixmap captureImage);

private:
	Ui::CaptureTestClass ui;
	// 截图对象指针;
	CaptureScreen* m_captureHelper;
};
