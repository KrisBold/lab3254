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

void TableBridge:: UpdateData(Object obj)
{
    Tmodel_->clear();
    QStringList horizontalHeader;
    horizontalHeader.append("Имя");
    horizontalHeader.append("Размер");
    horizontalHeader.append("Процент");
    Tmodel_->setHorizontalHeaderLabels(horizontalHeader);
    QStandardItem *item;
    Tmodel_->setHorizontalHeaderLabels(horizontalHeader);
    int rowcounter = 0;
    for(int i=0; i<obj.size.size(); i++)
    {
       item = new QStandardItem(obj.name[i]);
       Tmodel_->setItem(rowcounter, 0, item);

       item = new QStandardItem(QString::number(obj.size[i]));
       Tmodel_->setItem(rowcounter, 1, item);

       if(obj.percent[i]<0.01 && obj.percent[i]!=0)
       {
          item = new QStandardItem("<0.01%");
          Tmodel_->setItem(rowcounter, 2, item);
       }
       else
       {
           item = new QStandardItem(QString::number(obj.percent[i],'f', 2)+"%");
           Tmodel_->setItem(rowcounter, 2, item);
       }
       rowcounter++;
    }
    tableView_->setModel(Tmodel_);
    tableView_->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    tableView_->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    tableView_->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
}

void PieBridge:: UpdateData(Object obj)
{
    chart_->removeAllSeries();
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        series->append(obj.name[i], obj.percent[i]);
    }
    chart_->addSeries(series);
    chart_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chartView_->setRenderHint(QPainter::Antialiasing);
}

void BarBridge:: UpdateData(Object obj)
{
    chart_->removeAllSeries();
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    for(int i=0; i<obj.name.size(); i++)
    {
        QtCharts::QBarSet *set0 = new QtCharts::QBarSet(obj.name[i]);
        *set0<<obj.percent[i];
        series->append(set0);
    }
    chart_->addSeries(series);
    chart_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart_->addAxis(axisY_, Qt::AlignLeft);
    series->attachAxis(axisY_);
    chart_->legend()->setVisible(true);
    chart_->legend()->setAlignment(Qt::AlignBottom);
    chartView_->setRenderHint(QPainter::Antialiasing);
}
