#include "methodprint.h"
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
#include "QTableView"
#include <QHeaderView>

void TableBridge:: UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout)
{
    QTableView * tableView;
    tableView = new QTableView();
    QStringList horizontalHeader;
    horizontalHeader.append("Имя");
    horizontalHeader.append("Размер");
    horizontalHeader.append("Процент");
    QStandardItemModel *Tmodel = new QStandardItemModel;
    Tmodel->setHorizontalHeaderLabels(horizontalHeader);
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
}

void PieBridge:: UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout)
{
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        series->append(obj.name[i], obj.percent[i]);
    }
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
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
}

void BarBridge:: UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout)
{
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        QtCharts::QBarSet *set0 = new QtCharts::QBarSet(obj.name[i]);
        *set0<<obj.percent[i];
        series->append(set0);
    }
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
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
}
