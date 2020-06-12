#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "QTableView"
#include "QList"
#include "QBarSet"
#include "QBarSeries"
#include "QBarCategoryAxis"
#include "QValueAxis"
#include <QVector>
#include "strategy.h"
#include "foldersrtategy.h"
#include "filetypestrategy.h"
#include "methodprint.h"
#include <QAbstractItemModel>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    vlayout = new QVBoxLayout;

    strat2=new fileTypeStrategy();
    strat1=new folderSrtategy();
    chart = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart);
    tableView = new QTableView();
    Tmodel = new QStandardItemModel;

    axisY = new QtCharts::QValueAxis();
    print1= new TableBridge(Tmodel);
    print2= new PieBridge(chart);
    print3= new BarBridge(chart, axisY);

    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);

    ui->comboBox->addItem("по папкам");
    ui->comboBox->addItem("по файлам");

    ui->comboBox_2->addItem("таблица");
    ui->comboBox_2->addItem("диаграмма");
    ui->comboBox_2->addItem("гистограмма");

    ui->widget->setContentsMargins(0,0,0,0);
    ui->treeView->model()->dataChanged(ui->treeView->currentIndex(), ui->treeView->currentIndex());
    QObject::connect(model,SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),this, SLOT(on_treeView_clicked(const QModelIndex &)));

    tableView->setModel(Tmodel);
    tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete vlayout;
    delete strat2;
    delete strat1;
    delete Tmodel;
    delete print1;
    delete print2;
    delete print3;
    delete axisY;
    delete chart;
    delete chartView;
    delete tableView ;
}

void MainWindow:: Folder()
{
  strat1->DoStrategy(ui->treeView->currentIndex(), model, obj);
  changePercentageDisplay();
}

void MainWindow:: FileType()
{
    strat2->DoStrategy(ui->treeView->currentIndex(), model, obj);
    changePercentageDisplay();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QFileInfo fileinfo = model->fileInfo(index);
    switch(ui->comboBox->currentIndex())
    {
    case FOLDER:
       return  Folder();
    case FILETYPE:
       return FileType();
    }
}

void MainWindow:: changePercentageDisplay()
{
    switch(ui->comboBox_2->currentIndex())
    {
    case Table:
       print1->UpdateData(obj);break;
    case Pie:
       {print2->UpdateData(obj); axisY->hide();break;}
    case Bar:
       {print3->UpdateData(obj); axisY->show();break;}
    }

   if(chartView->isVisible() && ui->comboBox_2->currentIndex()==Table)
   {
     tableView->show();
     chartView->hide();
   }
   else if(tableView->isVisible() && (ui->comboBox_2->currentIndex()==Pie || ui->comboBox_2->currentIndex()==Bar))
   {
       chartView->show();
       tableView->hide();
   }

   if(ui->comboBox_2->currentIndex()==Pie || ui->comboBox_2->currentIndex()==Bar)
   {
       vlayout->addWidget(chartView);
   }

   else if(ui->comboBox_2->currentIndex()==Table)
   {
       vlayout->addWidget(tableView);
   }

   ui->widget->setLayout(vlayout);
}

void MainWindow::on_comboBox_2_currentTextChanged()
{
   changePercentageDisplay();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="по папкам")
    {
        Folder();
    }
    if(arg1=="по файлам")
    {
       FileType();
    }
}

