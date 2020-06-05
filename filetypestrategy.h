#ifndef FILETYPESTRATEGY_H
#define FILETYPESTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FileTypeStrategy: public Strategy
{
public:
  FileTypeStrategy(){};
  void DoStrategy(QString&  path);
protected:
  void sizeType(const QString &path, QHash<QString, int> &hash) ;
};

#endif // FILETYPESTRATEGY_H
