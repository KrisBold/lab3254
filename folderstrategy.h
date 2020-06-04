#ifndef FOLDERSTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FolderSrtategy: public Strategy
{
public:
    FolderSrtategy(){};
    void DoStrategy(QString&  path);
private:
    quint32 sizeFolder(QString  path);
    quint32 sizeListFolder(QString  path);
};

#endif // FOLDERSTRATEGY_H
