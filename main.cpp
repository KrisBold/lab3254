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
    QString path;
    FileTypeStrategy strat1; FolderSrtategy strat2;
    cin>>path;
    double finalsize=0;

    cout<<"\nSrtategy FOLDERS:"<<endl;
    strat2.DoStrategy(path);

    for(auto j:strat2.objs)
    {
        finalsize+=j.getSize();
    }

    for(auto j:strat2.objs)
    {
        j.percent=double(100*(j.getSize() / finalsize));
        if(j.getPer()!=0 && j.getPer()<0.01)
        {
          cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per: <0.01%"<<endl;
        }
        else cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per:"<<QString::number(j.getPer(),'f', 2)<<"%"<<endl;
    }

    cout<<"\nSrtategy TYPES:"<<endl;
    strat1.DoStrategy(path);

    for(auto j: strat1.objects)
    {
        if(j.getPer()!=0 && j.getPer()<0.01)
        {
           cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per:<0.01%"<<endl;
        }
        else cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per:"<<QString::number(j.getPer(),'f', 2)<<"%"<<endl;
    }

    return a.exec();
}
