#include "CaptureTest.h"
#include <QKeyEvent>
#include "capturescreen.h"

CaptureTest::CaptureTest(QWidget *parent)
	: QWidget(parent)
	, m_captureHelper(NULL)
{
	ui.setupUi(this);
}

// 监控键盘事件;
void CaptureTest::keyPressEvent(QKeyEvent *event)
{
	// 监控Ctrl + Alt + D键;
	if (event->key() == Qt::Key_D  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier))
	{
		startCatureImage();
	}
}

// 按下 Ctrl + Alt + D键，开始截图;
void CaptureTest::startCatureImage()
{
	// 点击截图按钮开始截图;
	m_captureHelper = new CaptureScreen();
	connect(m_captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
	m_captureHelper->show();
}

// 显示在界面上;
void CaptureTest::onCompleteCature(QPixmap captureImage)
{
	ui.label->setPixmap(captureImage);
	m_captureHelper->deleteLater();
	m_captureHelper = NULL;
}