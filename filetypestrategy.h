#ifndef FILETYPESTRATEGY_H
#define FILETYPESTRATEGY_H
#define FOLDERSTRATEGY_H
#include "strategy.h"

class FileTypeStrategy: public Strategy
{
public:
  FileTypeStrategy(){};
  void DoStrategy(QString&  path);
  void Print();
protected:
  void sizeType(const QString &path, QHash<QString, int> &hash) ;
  QVector<Object> objects;
};

#endif // FILETYPESTRATEGY_H
