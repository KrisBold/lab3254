#include <QCoreApplication>
#include "strategy.h"
#include <QTextStream>
#include "folderstrategy.cpp"
#include "filetypestrategy.cpp"
#include "folderstrategy.h"
#include "filetypestrategy.h"

//C:\Projects/45
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin), cout(stdout);
    QString path;
    FileTypeStrategy strat1; FolderSrtategy strat2;
    cin>>path;
    cout<<"Srtategy FOLDERS:"<<endl;
    strat2.DoStrategy(path);
    cout<<"Srtategy TYPES:"<<endl;
    strat1.DoStrategy(path);
    return a.exec();
}
