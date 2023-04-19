#include "Income.h"
#include "ui_Income.h"

Income::Income(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Income)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

Income::~Income()
{
    delete ui;
    delete m_calendar;
    delete m_wgtAction;
    delete m_menuDataTime;
}

void Income::initWorkUI()
{

    //tableWidget_records
    ui->tableWidget_records->setColumnCount(5);//先设置列数
    ui->tableWidget_records->setHorizontalHeaderLabels(m_header);
    ui->tableWidget_records->verticalHeader()->hide();
    ui->tableWidget_records->verticalHeader()->setDefaultSectionSize(26);//垂直固定高度26
    ui->tableWidget_records->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//垂直表头固定高度
    ui->tableWidget_records->setSelectionBehavior(QAbstractItemView::SelectRows);//只能行选择
    ui->tableWidget_records->horizontalHeader()->setSectionsMovable(true);//表头section可以拖动
    ui->tableWidget_records->setColumnWidth(0,200);
    ui->tableWidget_records->setColumnWidth(1,350);
    ui->tableWidget_records->setColumnWidth(2,150);
    ui->tableWidget_records->setColumnWidth(3,150);
    ui->tableWidget_records->setColumnWidth(4,150);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
    ui->tableWidget_records->setEditTriggers(false);//禁止编辑

    ui->stackedWidget_showType->setCurrentIndex(0);

    m_calendar = new CusCalendar();
    m_calendar->setObjectName(QString::fromUtf8("m_calendar"));
    m_menuDataTime = new QMenu();//不指定父亲，不继承父亲样式
    m_menuDataTime->setObjectName(QString::fromUtf8("m_menuDataTime"));
    m_wgtAction = new QWidgetAction(m_menuDataTime);
    m_wgtAction->setDefaultWidget(m_calendar);
    m_menuDataTime->addAction(m_wgtAction);

    ui->dateEdit_end->setDateTime(QDateTime::currentDateTime());
    ui->comboBox_gains->setView(new QListView());
    ui->comboBox_showType->setView(new QListView());

    ui->pushButton_exportrecords->setIcon(QIcon("://images/fileitem/record_export.png"));
    ui->pushButton_exportrecords->setIconSize(QSize(14,14));

    //生成游标
    tracer = new QCPItemTracer(ui->widget_lines); //生成游标
    tracer->setPen(QPen(Qt::red));//圆圈轮廓颜色
    tracer->setBrush(QBrush(Qt::red));//圆圈圈内颜色
    tracer->setStyle(QCPItemTracer::tsCircle);//圆圈
    tracer->setSize(5);//设置大小

    //游标显示
    tracerLabel = new QCPItemText(ui->widget_lines); //生成游标说明
    tracerLabel->setLayer("overlay");//设置图层为overlay，因为需要频繁刷新
    tracerLabel->setPen(QPen(Qt::black));//设置游标说明颜色
    tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);//左上
    tracerLabel->position->setParentAnchor(tracer->position);//将游标说明锚固在tracer位置处，实现自动跟随
}

void Income::handleSignalsAndSlots()
{
    //显示日历
    connect(ui->pushButton_date1,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    connect(ui->pushButton_date2,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    //日期填充
    connect(m_calendar,&CusCalendar::sig_calendar1,[=](QDate date){
        ui->dateEdit_start->setDate(date);
    });

    connect(m_calendar,&CusCalendar::sig_calendar2,[=](QDate date){
        ui->dateEdit_end->setDate(date);
    });

    //结果显示方式选择
    connect(ui->comboBox_showType,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        ui->stackedWidget_showType->setCurrentIndex(index);
        switch (index)
        {
        case 0://表格
        {
        }
            break;
        case 1://折线图
        {
            drawIncomeDataTo_line();
        }
            break;
        case 2://柱状图
        {
            drawIncomeDataTo_barchart();
        }
            break;
        case 3://饼图
        {
            drawIncomeDataTo_piechart();
        }
            break;
        default:
            break;
        }

    });

    //查询记录
    connect(ui->pushButton_search,&QPushButton::clicked,[=](){
        getUserIncomeRecord();
    });

    //导出记录
    connect(ui->pushButton_exportrecords,&QPushButton::clicked,[=](){
        exportTableRecords();
        qDebug() << QString(u8"导出结果记录！");
    });

    //时刻更新游标位置和内容
    connect(ui->widget_lines, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(slot_updateTracerText(QMouseEvent*)));

}

void Income::setInstallEventer()
{
    m_menuDataTime->installEventFilter(this);
    ui->dateEdit_start->installEventFilter(this);
    ui->dateEdit_end->installEventFilter(this);
}

void Income::getUserIncomeRecord()
{
    clearTable();
    QString data_start = ui->dateEdit_start->date().toString("yyyy-MM-dd");
    QString data_end   = ui->dateEdit_end->date().toString("yyyy-MM-dd");
    QList<QStringList> recordList = dataBase::getInstance()->income_getUserIncomeRecords(dataBase::getInstance()->getCurrentUserID(),data_start,data_end);
    if(recordList.count() != 0)
    {
        ui->tableWidget_records->setColumnCount(5);
        ui->tableWidget_records->setRowCount(recordList.count());
        foreach (QStringList list, recordList)
        {
            addOneUserIncomeRecordTo_UI(list);
        }
    }
}

void Income::addOneUserIncomeRecordTo_UI(QStringList& recordlist)
{
    QTableWidgetItem *item_0 = new QTableWidgetItem(recordlist.at(0));  item_0->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *item_1 = new QTableWidgetItem(recordlist.at(1));  item_1->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *item_2 = new QTableWidgetItem(recordlist.at(2));  item_2->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *item_3 = new QTableWidgetItem(recordlist.at(3));  item_3->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *item_4 = new QTableWidgetItem(recordlist.at(4));  item_4->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget_records->setItem(m_row,0,item_0);
    ui->tableWidget_records->setItem(m_row,1,item_1);
    ui->tableWidget_records->setItem(m_row,2,item_2);
    ui->tableWidget_records->setItem(m_row,3,item_3);
    ui->tableWidget_records->setItem(m_row,4,item_4);
    m_row++;
}

void Income::clearTable()
{
    m_row = 0;
    ui->tableWidget_records->clearContents();
    ui->tableWidget_records->setRowCount(0);

}

//导出表记录
void Income::exportTableRecords()
{
    qDebug() << QString(u8"导出表记录");
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Excel Files (*.xlsx)");

    if (!filePath.isEmpty()) {
        QXlsx::Document xlsx(filePath);

        // 获取 TableWidget 中的列数和行数
        int rowCount = ui->tableWidget_records->rowCount();
        int columnCount = ui->tableWidget_records->columnCount();

        // 写入表头
        for (int column = 0; column < columnCount; ++column)
        {
            QTableWidgetItem* item = ui->tableWidget_records->horizontalHeaderItem(column);
            if (item != nullptr)
            {
                //write原型：
                //bool write(int row, int col, const QVariant &value, const Format &format = Format());
                xlsx.write(1, column + 1, item->text());//从1开始，不是从0开始
            }
        }

        // 写入数据行
        for (int row = 0; row < rowCount; ++row)
        {
            for (int column = 0; column < columnCount; ++column)
            {
                QTableWidgetItem* item = ui->tableWidget_records->item(row, column);
                if (item != nullptr)
                {
                    xlsx.write(row + 2, column + 1, item->text());//row + 1 = 1 写的是表头数据，从row + 2 = 2写的是真实数据
                } else
                {
                    xlsx.write(row + 2, column + 1, "");//否则写入""
                }
            }
        }

        xlsx.save();//关闭保存
        ui->pushButton_tips->setText(QString(u8"数据导出成功！"));
        QTimer::singleShot(2000,0,[=](){
            ui->pushButton_tips->setText(QString(u8""));
        });
    }
}

//绘制折线图
void Income::drawIncomeDataTo_line()
{
    qDebug() << QString(u8"绘制折线图");
    // 生成数据，画出的是抛物线
//     QVector<double> x(101), y(101); //初始化向量x和y
//     for (int i=0; i<101; ++i)
//     {
//       x[i] = i/50.0 - 1; // x范围[-1,1]
//       y[i] = x[i]*x[i]; // y=x*x
//     }


     ui->widget_lines->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）

     // graph(0);可以获取某个数据曲线（按添加先后排序）
     // setData();为数据曲线关联数据
     // 设置y轴范围
//     double startTimestamp = QDateTime(QDate(2021, 1, 1)).toMSecsSinceEpoch() / 1000.0;
//     double endTimestamp = QDateTime(QDate(2021, 1, 31)).toMSecsSinceEpoch() / 1000.0;
//     ui->widget_lines->xAxis->setRange(startTimestamp, endTimestamp);
//     ui->widget_lines->yAxis->setRange(0,1000);
     // 设置x轴刻度并格式化
     // 将x轴标签格式化为月份和日期
//     ui->widget_lines->xAxis->setTickLabelType(QCPAxis::ltDateTime);
//     ui->widget_lines->xAxis->setDateTimeFormat("MM dd");

     // 添加数据点
//     QVector<QCPGraphData> data;
//     for (int i = 0; i < 365; ++i) {
//         double timestamp = QDateTime(QDate(2019, 1, 1).addDays(i)).toMSecsSinceEpoch();
//         double value = qSin(i * M_PI / 180.0);
//         data.append(QCPGraphData(timestamp, value));
//     }
//     ui->widget_lines->graph(0)->setData(data);


      // 生成数据，画出的是抛物线
     QVector<double> x(101), y(101); //初始化向量x和y
     for (int i=0; i<101; ++i)
     {
       x[i] = i/50.0 - 1; // x范围[-1,1]
       y[i] = x[i]*x[i]; // y=x*x
     }
     ui->widget_lines->xAxis->setRange(-1, 1);
     ui->widget_lines->yAxis->setRange(0, 1);
     ui->widget_lines->graph(0)->setData(x, y); //把数据加入到绘制器cmPlot，绘制器会自动绘制曲线


     ui->widget_lines->graph(0)->setName(u8"交易走势");// 设置图例名称
     ui->widget_lines->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
     ui->widget_lines->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色
     // 为坐标轴添加标签
     ui->widget_lines->xAxis->setLabel(QString(u8"交易日期"));
     ui->widget_lines->yAxis->setLabel(QString(u8"交易金额（元）"));
     // 设置坐标轴的范围，以看到所有数据
//     ui->widget_lines->xAxis->setRange(-1, 1);
//     ui->widget_lines->yAxis->setRange(0, 1);
     ui->widget_lines->legend->setVisible(true); // 显示图例
     //自动调整XY轴的范围，以便显示出graph(1)中所有的点
//     ui->widget_lines->graph(0)->rescaleAxes(true);

     // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
     ui->widget_lines->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
     // 重画图像
     ui->widget_lines->replot();
}

//绘制柱状图
void Income::drawIncomeDataTo_barchart()
{
    qDebug() << QString(u8"绘制柱状图");

    //绘制柱状图
    QCPAxis *xAxis = ui->widget_barchart->xAxis;//x轴
    QCPAxis *yAxis = ui->widget_barchart->yAxis;//y轴
    QCPBars *bars = new QCPBars(xAxis, yAxis);  // 使用xAxis作为柱状图的x轴，yAxis作为y轴

    bars->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars->setName("Bars"); // 设置图例
    bars->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色
    bars->setBrush(QColor(20,68,106));  // 设置柱状图的画刷颜色

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;//轴的范围
    labels << "A" << "B" << "C" << "D" << "E" << "F" << "G";//轴的刻度文字显示
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    xAxis->setTicker(textTicker);        // 设置为文字轴
    xAxis->setTickLabelRotation(60);     // 轴刻度文字旋转60度
    xAxis->setSubTicks(false);           // 不显示子刻度
    xAxis->setTickLength(0, 4);          // 轴内外刻度的长度分别是0,4,也就是轴内的刻度线不显示
    xAxis->setRange(0, 8);               // 设置x轴范围
    xAxis->setLabel("x");
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    yAxis->setRange(0, 12.1);          //设置y轴范围
    yAxis->setPadding(35);             // 轴的内边距
    yAxis->setLabel("y");
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QVector<double> fossilData;
    fossilData  << 10 << 9 << 2 << 5 << 7 << 4 << 1;//y轴坐标值
    bars->setData(ticks, fossilData);

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    ui->widget_barchart->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables);
    // 更新绘图区
    ui->widget_barchart->replot();
}

//绘制饼图
void Income::drawIncomeDataTo_piechart()
{
    qDebug() << QString(u8"绘制饼图");
    // 创建QCPLayoutElement对象
//    QCPLayoutElement *pie = new QCPLayoutElement(ui->widget_piechart);
//    ui->widget_piechart->plotLayout()->addElement(0, 0, pie);

//    // 创建QPieChart对象
//    QPieChart *pieChart = new QPieChart();
//    pie->addElement(pieChart); // 将饼图添加到QCPLayoutElement对象中

//    // 设置饼图数据
//    QVector<double> dataValues; // 数据值
//    QStringList dataLabels; // 数据标签
//    dataValues << 10 << 20 << 30 << 40;
//    dataLabels << "A" << "B" << "C" << "D";
//    pieChart->setData(dataValues);
//    pieChart->setLabels(dataLabels);

//    // 设置饼图样式
//    pieChart->setBrush(QColor(255, 0, 0)); // 饼图填充颜色
//    pieChart->setPen(QColor(0, 0, 0)); // 饼图边框颜色
    ui->widget_piechart->replot();
}

//更新游标内容
void Income::slot_updateTracerText(QMouseEvent *event)
{
//    //获得鼠标位置处对应的横坐标数据x
//    double x = ui->widget_lines->xAxis->pixelToCoord(event->pos().x());
//    //double y = cmPlot->yAxis->pixelToCoord(e->pos().y());
//    double xValue, yValue;

//    xValue = x;//xValue就是游标的横坐标
//    yValue = x*x;//yValue就是游标的纵坐标，这里直接根据产生数据的函数获得

//    tracer->position->setCoords(xValue, yValue);//设置游标位置
//    tracerLabel->setText(QString("x = %1, y = %2").arg(xValue).arg(yValue));//设置游标说明内容
//    ui->widget_lines->replot();//绘制器一定要重绘，否则看不到游标位置更新情况

    //获得鼠标位置处对应的横坐标数据x
    double x = ui->widget_lines->xAxis->pixelToCoord(event->pos().x());
    tracer->setGraph(ui->widget_lines->graph(0)); //将游标和该曲线图层想连接
    tracer->setGraphKey(x); //将游标横坐标设置成刚获得的横坐标数据x
    tracer->setInterpolating(true); //游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer->updatePosition(); //使得刚设置游标的横纵坐标位置生效
    //更新游标说明的内容
    double xValue = tracer->position->key();
    double yValue = tracer->position->value();
    tracerLabel->setText(QString("x = %1, y = %2").arg(xValue).arg(yValue));
    ui->widget_lines->replot(); //重绘
}



