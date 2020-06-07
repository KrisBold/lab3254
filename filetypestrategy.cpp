#include "filetypestrategy.h"
#include <QTextStream>

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
    QVector<QString> types;
    int finalSize = 0;
    QDir currentFolder(path);
    QHash<QString, int> hash;

    if (!currentFolder.exists())
    {
        return;
    }

    if (currentFolder.isEmpty())
    {
        objects.append(Object(path, 0, 100));
        return;
    }

    if (QFileInfo(path).isDir())
    {
        for(QFileInfo i: currentFolder.entryInfoList(QDir::Dirs))
        {
            if (QFileInfo(path).dir().isEmpty())
            {
                objects.append(Object(path, 0, 100));
                return ;
            }
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

    if(objects.size()==0)
    {
        objects.append(Object(path, 0, 100));
    }

}

