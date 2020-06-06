#include "filetypestrategy.h"
#include <QTextStream>

QVector<Object> objects;

//void FileTypeStrategy:: sizeType (QString path)
//{
//    QTextStream cin(stdin), cout(stdout);
//    QDir currentFolder( path );
//
//    QFileInfoList infolist( currentFolder.entryInfoList() );
//
//    for( QFileInfo i: infolist )
//    {
//        QString iname( i.fileName() );
//        if ( iname == "." || iname == ".." || iname.isEmpty() )
//            continue;
//
//        if(i.isDir())
//        {
//            sizeType( path+"/"+iname );
//        }
//
//        if(!i.isDir())
//        {
//           objects.append(new Object (iname, i.size(), 0, i.suffix()));
//        }
//    }
//    for( auto j: types)
//    {
//        cout<<j->getName()<<" size:"<<j->getSize()<<" type:"<<j->getType()<<endl;
//    }
//}
//
void FileTypeStrategy::sizeType(const QString &path, QHash<QString, int> &hash)
{
    QDir currentFolder(path);

    for(QFileInfo i: currentFolder.entryInfoList(QDir::Dirs))
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
        sizeType(i.path() + '/' + i.fileName(), hash);
    }

    for(QFileInfo i: currentFolder.entryInfoList(QDir::Files))
    {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() )
            continue;
        hash[i.suffix()] += i.size();
    }
}

void FileTypeStrategy::DoStrategy (QString &path)
{
    QTextStream cin(stdin), cout(stdout);
    QVector<QString> types;
    int finalSize = 0;
    QDir currentFolder(path);
    QHash<QString, int> hash;

    if (!currentFolder.exists())
    {
        cout<< "Path doesn't exist" << endl;
        return;
    }

    if (QFileInfo(path).isDir())
    {
        for(QFileInfo i: currentFolder.entryInfoList(QDir::Dirs))
        {
            QString iname( i.fileName() );
            if ( iname == "." || iname == ".." || iname.isEmpty() )
                continue;
            sizeType(path+"/"+iname, hash);
        }

        for(QFileInfo i: currentFolder.entryInfoList(QDir::Files))
        {
            QString iname( i.fileName() );
            if ( iname == "." || iname == ".." || iname.isEmpty() )
                continue;
            hash[i.suffix()] += i.size();
        }

        for (auto i = hash.begin(); i != hash.end(); i++)
        {
            finalSize += i.value();
            types.append(i.key());
        }

        for (int i = 0; i < types.size(); i++)
        {
            objects.append(Object(types[i], hash[types[i]], ((double)hash[types[i]] / finalSize) * 100));
        }
    }

    else
    {
        objects.append(Object(QFileInfo(path).suffix(), path.size(), 100));
    }

    for(auto j: objects)
    {
        if(j.getPer()!=0 && j.getPer()<0.01)
        {
           cout<<j.getName()<<" size:"<<j.getSize()<<"byte Per:<0.01%"<<endl;
        }
        else cout<<j.getName()<<" size:"<<j.getSize()<<"byte Per:"<<QString::number(j.getPer(),'f', 2)<<"%"<<endl;
    }
}


