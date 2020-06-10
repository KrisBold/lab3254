#include "filetypestrategy.h"

void sizeType(const QString &path, QHash<QString, int> &hash)
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

//стратегия по типам
void fileTypeStrategy::DoStrategy(const QModelIndex &index, QFileSystemModel *model, Object& obj)
{
    obj.name.clear();
    obj.size.clear();
    obj.percent.clear();
    QFileInfo fileinfo = model->fileInfo(index);
    QDir currentFolder( fileinfo.filePath() );
    currentFolder.setFilter( QDir::AllEntries);
    currentFolder.setSorting( QDir::Name );
    QVector<QString> types;
    int finalSize = 0;
    QHash<QString, int> hash;

    if (QFileInfo(fileinfo.filePath()).isDir())
    {
        for(QFileInfo i: currentFolder.entryInfoList(QDir::Dirs))
        {
            if (QFileInfo(fileinfo.filePath()).dir().isEmpty())
            {
                obj.name<<fileinfo.filePath();
                obj.percent<<100;
                obj.size<<0;
                return ;
            }
            QString iname( i.fileName() );
            if ( iname == "." || iname == ".." || iname.isEmpty() )
                continue;
            sizeType(fileinfo.filePath()+"/"+iname, hash);
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
            if(finalSize!=0)
            {
                if(!types[i].isEmpty())
                {
                  obj.name<<types[i];
                  obj.size<< hash[types[i]];
                  obj.percent<<((double)hash[types[i]] / finalSize) * 100;
                }
                else
                {
                    obj.name<<"Без расширения";
                    obj.size<< hash[types[i]];
                    obj.percent<<((double)hash[types[i]] / finalSize) * 100;
                }

            }
            else
            {
                if(!types[i].isEmpty())
                {
                   obj.name<<types[i];
                   obj.size<< hash[types[i]];
                   obj.percent<<100/obj.name.size();
                }
                else
                {
                    obj.name<<"Без расширения";
                    obj.size<< hash[types[i]];
                    obj.percent<<100/obj.name.size();
                }
            }
        }
        bool nol=false;
        for (int j = 0; j < types.size(); j++)
        {
           for (int i = 0; i < types.size(); i++)
           {
               if(obj.size[i]==0)
               {
                   nol=true;
               }
               else { nol=false;break;}
           }

           if(nol==true)
           {
               obj.percent[j]=100/obj.name.size();
           }
        }

    }

    else
    {
        obj.name<<QFileInfo(fileinfo.filePath()).suffix();
        obj.size<< fileinfo.filePath().size();
        obj.percent<<100;
    }

    if(obj.name.size()==0)
    {
        obj.name<<"FOLDER EMPTY";
        obj.size<< 0;
        obj.percent<<100;
    }

}
