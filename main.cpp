#include <QCoreApplication>
#include "strategy.h"
#include <QTextStream>

//размер текущей папки
quint32 sizeFolder ( QString path )
{
    QTextStream cin(stdin), cout(stdout);
    QDir currentFolder( path );

    quint32 finalsize = 0;

    currentFolder.setFilter( QDir::AllEntries);//фильтр
    currentFolder.setSorting( QDir::Name );//сортировка по имени

    QFileInfoList infolist( currentFolder.entryInfoList() );//информация о каждой записи

    for( QFileInfo i: infolist )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
        cout<<i.size()<<"   -"<<iname<<endl;
        finalsize += i.size();
    }
    cout<<finalsize<<" byat"<<endl;
    return finalsize;
}

//размер +вложенных папок
quint32 sizeListFolder ( QString path )
{
    QTextStream cin(stdin), cout(stdout);
    QDir currentfolder( path );

    quint32 finalsize = 0;

    currentfolder.setFilter( QDir::AllEntries);
    currentfolder.setSorting( QDir::Name );

    QFileInfoList infolist( currentfolder.entryInfoList() );

    for ( QFileInfo i: infolist )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
            finalsize += sizeListFolder( path+"/"+iname );
        else
            finalsize += i.size();
            cout<<iname<<" -"<< i.size()<<endl;
    }
    cout<<"FINAL:"<<finalsize<<endl;
    return finalsize;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin), cout(stdout);
    QString ap;
    cin>>ap;
    cout<<sizeFolder(ap)<<flush;
    return a.exec();
}
