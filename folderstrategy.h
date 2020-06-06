#ifndef FOLDERSTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FolderSrtategy: public Strategy
{
public:
    QVector<Object> objs;
    FolderSrtategy(){};
    void DoStrategy(QString&  path);
private:
    qint64 sizeFolder(QString  path);
    qint64 sizeListFolder(QString  path);
};

#endif // FOLDERSTRATEGY_H
