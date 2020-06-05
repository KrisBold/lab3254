#ifndef STRATEGY_H
#define STRATEGY_H
#include <QDir>
#include <QStringList>
#include <QVector>

struct Object
{
  QString name;
  qint64 size;
  double percent;
  Object(QString name, int size, double percent):name(name), size(size), percent(percent){};
  QString getName() {return name;};
  qint64 getSize(){ return size;};
  double getPer(){ return percent;};
};

class Strategy
{
public:
    Strategy(){};
    virtual ~Strategy(){};
    virtual void DoStrategy(QString&  path)=0;
};


#endif // STRATEGY_H
