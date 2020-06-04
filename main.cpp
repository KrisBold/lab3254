#include <QCoreApplication>
#include "strategy.h"
#include <QTextStream>
#include "folderstrategy.cpp"
#include "filetypestrategy.cpp"
#include "folderstrategy.h"
#include "filetypestrategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin), cout(stdout);
    QString ap;
    FolderSrtategy pj;
    cin>>ap;
    pj.DoStrategy(ap);
    return a.exec();
}
