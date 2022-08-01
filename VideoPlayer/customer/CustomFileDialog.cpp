#include "customfiledialog.h"

#include <QPainter>
#include <QMouseEvent>
#include <QHeaderView>
#include <QListView>
#include <QTreeView>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDebug>

class NoFocusDelegate : public QStyledItemDelegate
{
public:
	NoFocusDelegate(QObject *parent) :QStyledItemDelegate(parent)
    {

    }

public:
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		QStyleOptionViewItem itemOptin(option);
		if (itemOptin.state & QStyle::State_HasFocus)
            itemOptin.state = itemOptin.state ^ QStyle::State_HasFocus;
		return QStyledItemDelegate::paint(painter, itemOptin, index);
    }
};

CustomFileDialog::CustomFileDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_fileDialog = new QFileDialog(this, Qt::SubWindow | Qt::FramelessWindowHint);
    m_fileDialog->setAttribute(Qt::WA_TranslucentBackground);
	m_fileDialog->setOption(QFileDialog::DontUseNativeDialog, true);
    ui.bodylayout->addWidget(m_fileDialog);//QWidget承载了QFileDialog

//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

	QLabel* lookinLabel = m_fileDialog->findChild<QLabel*>("lookInLabel");
	if (lookinLabel)
		lookinLabel->setText(QString::fromLocal8Bit("文件目录："));

	QComboBox* fileTypeCombo = m_fileDialog->findChild<QComboBox*>("fileTypeCombo");
	if (fileTypeCombo)
		fileTypeCombo->setMinimumHeight(24);
	QComboBox* lookInCombo = m_fileDialog->findChild<QComboBox*>("lookInCombo");
	if (lookInCombo)
		lookInCombo->setMinimumHeight(24); 
	QLineEdit* fileNameEdit = m_fileDialog->findChild<QLineEdit*>("fileNameEdit");
	if (fileNameEdit)
		fileNameEdit->setMinimumHeight(24);

	QDialogButtonBox *buttonBox = m_fileDialog->findChild<QDialogButtonBox *>("buttonBox");
	if (QPushButton *button = buttonBox->button(QDialogButtonBox::Open)){
		button->setStyleSheet("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #00BAFF, stop: 1 #00A1FF);font-size: 12px;color: #FFFFFF;border-radius:2px;}"
							  "QPushButton:hover{background: #00C1FF;font-size: 12px;color: #FFFFFF;border-radius:2px;}"
							  "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
		button->setFixedSize(68, 24);
	}
	if (QPushButton *button = buttonBox->button(QDialogButtonBox::Save)){
		button->setStyleSheet("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #00BAFF, stop: 1 #00A1FF);font-size: 12px;color: #FFFFFF;border-radius:2px;}"
							  "QPushButton:hover{background: #00C1FF;font-size: 12px;color: #FFFFFF;border-radius:2px;}"
							  "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
		button->setFixedSize(68, 24);
	}
	if (QPushButton *button = buttonBox->button(QDialogButtonBox::Cancel)){
		button->setStyleSheet("QPushButton{border: 1px solid #DDDDDD;font-size: 12px;color: #666666;border-radius:2px;}"
							  "QPushButton:hover{font-size: 12px;color: #00A1FF;border: 1px solid #00A1FF;border-radius:2px;}"
							  "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
		button->setText(QString::fromLocal8Bit("取消"));
		button->setFixedSize(68, 24);
	}

	if (m_fileDialog->fileMode() != QFileDialog::ExistingFiles)
	{
		connect(m_fileDialog, SIGNAL(finished(int)), this, SLOT(onFileDialogFinished(int)));
	}

	connect(ui.sysMin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
	connect(ui.sysClose, SIGNAL(clicked(bool)), this, SLOT(onShowClose(bool)));
}

CustomFileDialog::~CustomFileDialog()
{

}



void CustomFileDialog::paintEvent(QPaintEvent *event)
{
	// 背景图
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	__super::paintEvent(event);
}

void CustomFileDialog::mousePressEvent(QMouseEvent *event)
{
	QDialog::mousePressEvent(event);
}

void CustomFileDialog::onAccepted()
{
	QDialog::accept();
}

void CustomFileDialog::onRejected()
{
	QDialog::reject();
}

void CustomFileDialog::onShowClose(bool)
{
	close();
}

void CustomFileDialog::onShowMin(bool)
{
	showMinimized();
}

void CustomFileDialog::setTitleName(const QString& titleName)
{
	ui.titleLabel->setText(titleName);
	setWindowTitle(titleName);
}

QStringList CustomFileDialog::selectedFiles() const
{
    return m_fileDialog->selectedFiles();
}

void CustomFileDialog::setFileMode(QFileDialog::FileMode mode)
{
	m_fileDialog->setFileMode(mode);
	//支持多选
	if (m_fileDialog->fileMode() == QFileDialog::ExistingFiles)
	{
		QListView *pListView = m_fileDialog->findChild<QListView*>("listView");
		if (pListView){
			pListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
			pListView->setItemDelegate(new NoFocusDelegate(pListView));
		}
		QTreeView *pTreeView = m_fileDialog->findChild<QTreeView*>("treeView");
		if (pTreeView){
			pTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
			pTreeView->setItemDelegate(new NoFocusDelegate(pTreeView));
			pTreeView->header()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		}

		QDialogButtonBox *buttonBox = m_fileDialog->findChild<QDialogButtonBox *>("buttonBox");
		buttonBox->disconnect();
		connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));//改成自己的槽
		connect(buttonBox, SIGNAL(rejected()), this, SLOT(onRejected()));//改成自己的槽
    }
}

void CustomFileDialog::setDirectory(const QString &directory)
{
    m_fileDialog->setDirectory(directory);
}

void CustomFileDialog::setNameFilter(const QString &filter)
{
    m_fileDialog->setNameFilter(filter);
}

void CustomFileDialog::setNameFilters(const QStringList &filter)
{
    m_fileDialog->setNameFilters(filter);
}

void CustomFileDialog::onFileDialogFinished(int result)
{
	if (result == QDialog::Accepted)
	{
		QDialog::accept();
	}
	else
	{
		QDialog::reject();
	}
}
