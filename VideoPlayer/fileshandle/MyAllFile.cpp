#include "MyAllFile.h"
#include "ui_MyAllFile.h"

MyAllFile::MyAllFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyAllFile)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();

}

MyAllFile::~MyAllFile()
{
    delete ui;
}

void MyAllFile::initWorkUI()
{
//    ui->treeView_allfiles->resize(QSize(215,500));
//    ui->treeView_allfiles->setMinimumWidth(215);
//    ui->treeView_allfiles->setMaximumWidth(280);

    ui->listView_list->setViewMode(QListView::IconMode);


    // 创建文件系统模型并设置根路径
    m_fileSysModel = new QFileSystemModel();

//    m_fileSysModel->setRootPath(QDir::rootPath());
    m_fileSysModel->setRootPath("E:/QtProjects/000QtDemo_51ctodemo");

//    ui->widget_pathdir->setPath(QDir::rootPath());
    // 设置文件过滤器，只显示目录和所有者可读的文件
//    m_fileSysModel->setFilter(QDir::AllDirs | QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);

    // 设置模型到视图中
    ui->treeView_allfiles->setModel(m_fileSysModel);
    ui->listView_list->setModel(m_fileSysModel);

    // 设置视图样式，并调整列宽以适应内容
    ui->treeView_allfiles->setAnimated(false);
    ui->treeView_allfiles->setIndentation(20);
    ui->treeView_allfiles->setSortingEnabled(true);
    ui->treeView_allfiles->resizeColumnToContents(0);//不自适应
}

void MyAllFile::handleSignalsAndSlots()
{
    //列表模式
    connect(ui->pushButton_listMode,&QPushButton::clicked,[=](){
        ui->stackedWidget_mode->setCurrentIndex(0);
    });

    //图标模式
    connect(ui->pushButton_iconMode,&QPushButton::clicked,[=](){
//        ui->stackedWidget_mode->setCurrentIndex(1);
            ui->treeView_allfiles->setIconSize(QSize(32, 32));
            ui->treeView_allfiles->setAnimated(false);
            ui->treeView_allfiles->setIndentation(20);
            ui->treeView_allfiles->setSortingEnabled(true);
    });

    connect(m_fileSysModel,&QFileSystemModel::directoryLoaded,[=](const QString &newPath){
        qDebug() << "new dir path:" << newPath;
//        ui->widget_pathdir->setPath(newPath);
//        QModelIndex index = m_fileSysModel->index(QDir::currentPath());
//        ui->treeView_allfiles->expand(index);
//        ui->treeView_allfiles->scrollTo(index);
    });

    connect(ui->treeView_allfiles,&QTreeView::doubleClicked,[=](const QModelIndex &index){
            qDebug() << m_fileSysModel->data(index).toString();
            ui->treeView_allfiles->setRootIndex(index);
    });

    connect(ui->listView_list,&QListView::doubleClicked,[=](const QModelIndex &index){
            qDebug() << m_fileSysModel->data(index).toString();
//            m_fileSysModel->setRootPath(m_fileSysModel->data(index).toString());
    });
}

void MyAllFile::setItemHideOrShow(QTreeWidgetItem *item, bool show)
{

}
