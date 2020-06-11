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

class AbstractBridge
{
public:
    AbstractBridge() {};
    virtual void UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout) = 0;
    virtual ~AbstractBridge() {};

};


class TableBridge : public AbstractBridge
{
public:
    void UpdateData( Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout);
    ~TableBridge(){};
};

class PieBridge : public AbstractBridge
{
public:
    void UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout);
    ~PieBridge(){};
};

class BarBridge : public AbstractBridge
{
public:
    void UpdateData(Object obj,QHBoxLayout *hlayout, QVBoxLayout *vlayout);
    ~BarBridge(){};
};

#endif // METHODPRINT_H
