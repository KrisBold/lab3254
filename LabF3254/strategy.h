#ifndef STRATEGY_H
#define STRATEGY_H
#include <QDir>
#include <QFileSystemModel>
#include <QStringList>
#include <QVector>

struct Object
{
   QStringList name;
   QVector<quint64> size;
   QVector<double> percent;
};

class Strateg
{
public:
    virtual ~Strateg(){}
    virtual void DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object& obj) = 0;
};

class strategy
{
private:
    Strateg* strateg;
public:
    strategy(Strateg *strat): strateg(strat)
    {

    }
    ~strategy()
    {
        delete strateg;
    }
    void DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object& obj)
    {
        strateg->DoStrategy(index, model, obj);
    }
};

#endif // STRATEGY_H
