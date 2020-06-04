#ifndef STRATEGY_H
#define STRATEGY_H
#include <QDir>
#include <QStringList>
#include <QVector>

struct Object
{
  QStringList objName;
  QVector<qint32> objSize;
};

class Strategy
{
public:
    Strategy(){};
    virtual ~Strategy(){};
    virtual void DoStrategy(QString&  path)=0;
};


#endif // STRATEGY_H
