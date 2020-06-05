#include "filetypestrategy.h"

////рамер файлов по их типам
//Object FileTypeStrategy::sizeType (QString path, Object &tmp)
//{
//    QDir currentFolder( path );
//    currentFolder.setFilter( QDir::AllEntries);
//    currentFolder.setSorting( QDir::Name );
//
//    QFileInfoList folderitems( currentFolder.entryInfoList() );
//
//    for( QFileInfo i: folderitems )
//    {
//        QString iname( i.fileName() );
//        if ( iname == "." || iname == ".." || iname.isEmpty() )
//            continue;
//        if(i.isDir())
//        {
//            tmp = sizeType(path+"/"+iname, tmp);
//        }
//        if(i.isFile())
//        {
//            if(tmp.names.empty())
//            {
//                tmp.names<<i.completeSuffix();
//                tmp.sizes<<i.size();
//            }
//            else
//            {
//                bool chek = false;
//                for(QString str: tmp.names)
//                {
//                    if(i.completeSuffix() == str)
//                    {
//                        tmp.sizes[tmp.names.indexOf(str,0)] += i.size();
//                        chek=true;
//                    }
//                }
//                if(!chek)
//                {
//                    tmp.names<<i.completeSuffix();
//                    tmp.sizes<<i.size();
//                }
//            }
//        }
//    }
//    return tmp;
//}
//
//void FileTypeStrategy::DoStrategy(QString& path)
//{
//    QDir currentFolder(path);
//    Object element;
//    currentFolder.setFilter( QDir::AllEntries);
//    currentFolder.setSorting( QDir::Name );
//    QFileInfoList folderitems( currentFolder.entryInfoList() );
//    foreach ( QFileInfo i, folderitems )
//    {
//        QString iname( i.fileName() );
//        if ( iname == "." || iname == ".." || iname.isEmpty() )
//            continue;
//        if(i.isFile())
//        {
//            if(element.names.empty())
//            {
//                element.names<<i.completeSuffix();
//                element.sizes<<i.size();
//            }
//            else
//            {
//                bool chek = false;
//                foreach (QString str, element.names)
//                {
//                    if(i.completeSuffix() == str)
//                    {
//                        element.sizes[element.names.indexOf(str,0)] += i.size();
//                        chek=true;
//                    }
//                }
//                if(!chek)
//                {
//                    element.names<<i.completeSuffix();
//                    element.sizes<<i.size();
//                }
//            }
//        }
//        if(i.isDir())
//        {
//            element = sizeType(path+"/"+iname, element);
//        }
//    }
//}
