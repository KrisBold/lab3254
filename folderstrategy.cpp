#include "folderstrategy.h"
#include <QTextStream>
//вложенные папки не выводить
QVector<Object> objs;

qint64 FolderSrtategy:: sizeFolder ( QString path )
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
            //cout<<"File: "<<iname<<" Size:"<<i.size()<<endl;
            objs.append(Object (iname, i.size(), 0));
            finalsize += i.size();
       }
        else continue;
    }
    return finalsize;
}

qint64 FolderSrtategy:: sizeListFolder ( QString path)
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

    //cout<<"Directory: "<<path<<"  Size:"<<finalsize<<endl;
    objs.append(Object (path, finalsize, 0));
    return finalsize;
}

void FolderSrtategy::DoStrategy(QString&  path)
{
    QTextStream cin(stdin), cout(stdout);
    QDir currentfolder(path);
    qint64 size1=0;

    if (!currentfolder.exists())
    {
        cout<< "Path doesn't exist" << endl;
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
           size1=sizeListFolder(path+"/"+iname);
        }
    }
    qint64 size2= sizeFolder(path);

    double finalsize=size1+size2;

    cout<<"Print:"<<finalsize<<endl;
    for(auto j:objs)
    {
        double per=double(100*(j.getSize() / finalsize));
        if(per!=0 && per<0.01)
        {
          cout<<j.getName()<<" Size:"<<j.getSize()<<" Per: <0.01%"<<endl;
        }
        else cout<<j.getName()<<" Size:"<<j.getSize()<<" Per:"<<QString::number(per,'f', 2)<<endl;
    }
}
