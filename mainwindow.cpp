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
#include <QAbstractItemModel>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    QObject::connect(model,SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),this, SLOT(reprint(const QModelIndex &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: Folder()
{
  strat=new folderSrtategy();
  strat->DoStrategy(ui->treeView->currentIndex(), model, obj);
  if(ui->comboBox_2->currentText()=="таблица")
      PrintTable(ui, obj);
  if(ui->comboBox_2->currentText()=="диаграмма")
      PrintPieChart(ui, obj);
  if(ui->comboBox_2->currentText()=="гистограмма")
      PrintBarChart(ui,obj);
  delete strat;
}

void MainWindow:: FileType()
{
    strat=new fileTypeStrategy();
    strat->DoStrategy(ui->treeView->currentIndex(), model, obj);
    if(ui->comboBox_2->currentText()=="таблица")
        PrintTable(ui, obj);
    if(ui->comboBox_2->currentText()=="диаграмма")
        PrintPieChart(ui, obj);
    if(ui->comboBox_2->currentText()=="гистограмма")
        PrintBarChart(ui,obj);
    delete strat;
}

void MainWindow:: on_treeView(const QModelIndex &index)
{
    QFileInfo fileinfo = model->fileInfo(index);
    if(ui->comboBox->currentText()=="по папкам")
    {
        Folder();
    }
    if(ui->comboBox->currentText()=="по файлам")
    {
        FileType();
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
   on_treeView(index);
}

void MainWindow::PrintTable(Ui::MainWindow *ui, Object obj)
{
    QTableView * tableView;
    tableView = new QTableView(ui->widget);
    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Имя");
    horizontalHeader.append("Размер");
    horizontalHeader.append("Процент");
    QStandardItemModel *Tmodel = new QStandardItemModel;
    QStandardItem *item;
    Tmodel->setHorizontalHeaderLabels(horizontalHeader);
    int rowcounter = 0;
    for(int i=0; i<obj.size.size(); i++)
    {
            item = new QStandardItem(obj.name[i]);
            Tmodel->setItem(rowcounter, 0, item);

            item = new QStandardItem(QString::number(obj.size[i]));
            Tmodel->setItem(rowcounter, 1, item);

            if(obj.percent[i]<0.01 && obj.percent[i]!=0)
            {
               item = new QStandardItem("<0.01%");
               Tmodel->setItem(rowcounter, 2, item);
            }
            else
            {
                item = new QStandardItem(QString::number(obj.percent[i],'f', 2)+"%");
                Tmodel->setItem(rowcounter, 2, item);
            }
            rowcounter++;
    }
    tableView->setModel(Tmodel);
    tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);

    if(vlayout->count()!=0)
    {
        while(vlayout->count())
        {
          vlayout->removeItem(vlayout->itemAt(0));
        }
    }
    vlayout->setMargin(0);
    hlayout->setMargin(0);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(tableView);
    ui->widget->setLayout(vlayout);

}

void MainWindow::PrintPieChart(Ui::MainWindow *ui,Object obj)
{
    QPieSeries *series = new QPieSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        series->append(obj.name[i], obj.percent[i]);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if(vlayout->count()!=0)
    {
        while(vlayout->count())
        {
          vlayout->removeItem(vlayout->itemAt(0));
        }
    }
    vlayout->setMargin(0);
    hlayout->setMargin(0);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(chartView);
    ui->widget->setLayout(vlayout);

}
//вывод инвормации в виде гистограммы
void MainWindow::PrintBarChart(Ui::MainWindow *ui,Object obj)
{
    QBarSeries *series = new QBarSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        QBarSet *set0 = new QBarSet(obj.name[i]);
        *set0<<obj.percent[i];
        series->append(set0);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if(vlayout->count()!=0)
    {
        while(vlayout->count())
        {
          vlayout->removeItem(vlayout->itemAt(0));
        }
    }
    vlayout->setMargin(0);
    hlayout->setMargin(0);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(chartView);
    ui->widget->setLayout(vlayout);
}

//изменение вида вывода информации
void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1=="таблица")
    {
        PrintTable(ui, obj);
    }
    if(arg1=="диаграмма")
    {
        PrintPieChart(ui, obj);
    }
    if(arg1=="гистограмма")
    {
        PrintBarChart(ui,obj);
    }
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

void MainWindow::reprint(const QModelIndex & index)
{
   on_treeView(index);
}
