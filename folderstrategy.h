#ifndef FOLDERSTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FolderSrtategy: public Strategy
{
public:
    FolderSrtategy(){};
    void DoStrategy(QString&  path);
    void Print();
private:
    qint64 sizeFolder(QString  path);
    qint64 sizeListFolder(QString  path);
    QVector<Object> objs;
};

#endif // FOLDERSTRATEGY_H
