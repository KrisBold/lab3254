#include <QCoreApplication>
#include "include/FileManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileManager::instance().startTerminalThread().startCheckThread();

    QCoreApplication::exec();
}
