#ifndef METHODPRINT_H
#define METHODPRINT_H
#include"strategy.h"
#include"foldersrtategy.h"
#include"filetypestrategy.h"
#include<QAbstractItemView>
#include<QStandardItemModel>
#include<QTableView>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "QGridLayout"
#include "QBarSet"
#include "QBarSeries"
#include "QBarCategoryAxis"

class AbstractBridge
{
public:
    AbstractBridge() {};
    virtual void UpdateData(Object obj) = 0;
    virtual ~AbstractBridge() {};
};

class TableBridge : public AbstractBridge
{
public:
    TableBridge(QStandardItemModel *Tmodel,QTableView * tableView):Tmodel_(Tmodel), tableView_(tableView){};
    void UpdateData( Object obj);
    ~TableBridge(){};
private:
    QStandardItemModel *Tmodel_;
    QTableView * tableView_;
};

class PieBridge : public AbstractBridge
{
public:
    PieBridge(QtCharts::QChartView *chartView,QtCharts::QChart *chart):chartView_(chartView),chart_(chart){};
    void UpdateData(Object obj);
    ~PieBridge(){};
private:
    QtCharts::QChartView *chartView_;
    QtCharts::QChart *chart_;
};

class BarBridge : public AbstractBridge
{
public:
    BarBridge(QtCharts::QChartView *chartView,QtCharts::QChart *chart, QtCharts::QValueAxis *axisY):chartView_(chartView),chart_(chart),axisY_(axisY){};
    void UpdateData(Object obj);
    ~BarBridge(){};
private:
    QtCharts::QChartView *chartView_;
    QtCharts::QChart *chart_;
    QtCharts::QValueAxis *axisY_;
};

#endif // METHODPRINT_H
