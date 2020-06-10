#ifndef FILETYPESTRATEGY_H
#define FILETYPESTRATEGY_H
#include "strategy.h"

class fileTypeStrategy : public Strateg
{
public:
    void DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object&);
};

#endif // FILETYPESTRATEGY_H
