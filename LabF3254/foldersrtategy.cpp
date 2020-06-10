#include "foldersrtategy.h"


quint32 listFolder ( QString path )
{
    QDir currentFolder( path );

    quint32 totalsize = 0;

    currentFolder.setFilter( QDir::AllEntries);
    currentFolder.setSorting( QDir::Name );

    QFileInfoList folderitems( currentFolder.entryInfoList() );

    for ( QFileInfo i: folderitems )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
            totalsize += listFolder( path+"/"+iname );
        else
            totalsize += i.size();
    }
    return totalsize;
}

quint32 sizeFolder ( QString path )
{
    QDir currentFolder( path );

    quint32 totalsize = 0;

    currentFolder.setFilter( QDir::AllEntries);
    currentFolder.setSorting( QDir::Name );

    QFileInfoList folderitems( currentFolder.entryInfoList() );

    for ( QFileInfo i: folderitems )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
        totalsize += i.size();

    }
    return totalsize;
}

//стретегия по папкам
void folderSrtategy::DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object& obj)
{
    obj.name.clear();
    obj.size.clear();
    obj.percent.clear();

    QFileInfo fileinfo = model->fileInfo(index);
    QDir currentFolder( fileinfo.filePath() );
    currentFolder.setFilter( QDir::Dirs);
    currentFolder.setSorting( QDir::Name );

    QFileInfoList folderitems( currentFolder.entryInfoList() );
    for ( QFileInfo i: folderitems )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;

        if ( i.isDir() )
        {
            obj.name<<iname;
            obj.size<<listFolder(fileinfo.filePath()+"/"+iname);
            obj.percent<<0;
        }
        else
            continue;
    }
    QFileInfoList folderitems1( currentFolder.entryInfoList(QDir::Files) );

    for ( QFileInfo i: folderitems1 )
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
       obj.name<<iname;
       obj.size<<i.size();
       obj.percent<<0;
    }

    double finalsize=0;

    for(int j=0; j< obj.name.size(); j++)
    {
        finalsize+=obj.size[j];
    }

    for(int j=0; j< obj.name.size(); j++)
    {
        if(finalsize!=0)
        {
            obj.percent[j]=100*(obj.size[j]/finalsize);
        }
        else
        {
            obj.percent[j]=100/obj.name.size();
        }
    }
}
