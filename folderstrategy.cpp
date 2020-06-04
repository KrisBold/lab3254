#include "folderstrategy.h"
#include <QTextStream>

quint32 FolderSrtategy:: sizeFolder ( QString path )
{
    QTextStream cin(stdin), cout(stdout);
    QDir currentFolder( path );

    quint32 finalsize = 0;

    QFileInfoList infolist( currentFolder.entryInfoList() );//информация о каждой записи

    for( QFileInfo i: infolist )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
        if(!i.isDir())
        {
        cout<<iname<<" size:"<<i.size()<<endl;
        finalsize += i.size();
        }
        else continue;
    }
    return finalsize;
}

quint32 FolderSrtategy:: sizeListFolder ( QString path )
{
    QTextStream cin(stdin), cout(stdout);
    QDir currentfolder( path );

    quint32 finalsize = 0;

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
    }
    cout<<path<<"  size:"<<finalsize<<endl;
    return finalsize;
}


void FolderSrtategy::DoStrategy(QString&  path)
{
    QDir currentfolder(path);
    Object final;

    QFileInfoList infolist( currentfolder.entryInfoList() );

    for( QFileInfo i: infolist )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
        {
            final.objName<<iname;
            final.objSize<<sizeListFolder(path+"/"+iname);
        }
    }
    final.objSize<<sizeFolder(path);
}
