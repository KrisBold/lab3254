#include "folderstrategy.h"
#include <QTextStream>

qint64 FolderSrtategy:: sizeFolder ( QString path )
{
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
            objs.append(Object (iname, i.size(), 0));
            finalsize += i.size();
       }
        else continue;
    }
    return finalsize;
}

qint64 FolderSrtategy:: sizeListFolder ( QString path)
{
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

    if(path.count(QRegExp("/"))<2)
    {
       objs.append(Object (path, finalsize, 0));
    }

    return finalsize;
}

void FolderSrtategy::DoStrategy(QString&  path)
{
    QDir currentfolder(path);

    if (!currentfolder.exists())
    {
        return;
    }

    if (currentfolder.isEmpty())
    {
        objs.append(Object(path, 0, 100));
        return;
    }

    if (QFileInfo(path).dir().isEmpty())
    {
        objs.append(Object(path, 0, 100));
        return ;
    }

    QFileInfoList infolist( currentfolder.entryInfoList() );

    for( QFileInfo i: infolist )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
        {
           sizeListFolder(path+"/"+iname);
        }
    }
    sizeFolder(path);
    double finalsize=0;

    for(auto j:objs)
    {
        finalsize+=j.getSize();
    }

    for(auto j=objs.begin(); j != objs.end(); j++)
    {
        if(finalsize!=0)
        {
            j->percent=100*(j->getSize() / finalsize);
        }
        else j->percent=100;
    }
}

