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
}

void FolderSrtategy::Print()
{
    QTextStream cin(stdin), cout(stdout);
    double finalsize=0;

    for(auto j:objs)
    {
        finalsize+=j.getSize();
    }

    cout<<"finalsize: "<<finalsize<<endl;
    for(auto j:objs)
    {
        double per=double(100*(j.getSize() / finalsize));
        if(per!=0 && per<0.01)
        {
          cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per: <0.01%"<<endl;
        }
        else cout<<j.getName()<<" Size:"<<j.getSize()<<"byte Per:"<<QString::number(per,'f', 2)<<"%"<<endl;
    }
}
