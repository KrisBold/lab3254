#ifndef FOLDERSRTATEGY_H
#define FOLDERSRTATEGY_H

#include "strategy.h"

class folderSrtategy : public Strateg
{
public:
    void DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object&);
};

#endif // FOLDERSRTATEGY_H
