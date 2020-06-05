#ifndef FILETYPESTRATEGY_H
#define FILETYPESTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FileTypeStrategy: public Strategy
{
public:
  FileTypeStrategy(){};
  void DoStrategy(QString&  path);
  Object sizeType (QString path, Object &tmp);
};

#endif // FILETYPESTRATEGY_H
