#include <QGuiApplication>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include <CoreLibraryInterface.h>

#define CORE_LIBRARY_DIRECTORY "libraries/core"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication *app = new QGuiApplication(argc, argv);
    CoreLibraryInterface *coreEngine = NULL;
    QDir    libDir = QCoreApplication::applicationDirPath();

    libDir.cd(CORE_LIBRARY_DIRECTORY);
    QPluginLoader loader(libDir.absoluteFilePath(libDir.entryList(QDir::Files).first()));

    if ((coreEngine = qobject_cast<CoreLibraryInterface *>(loader.instance())) != NULL)
    {
        qDebug() << "Core Library Loaded";
        coreEngine->initCoreEngine();
        QObject::connect(coreEngine->getObject(), SIGNAL(quit()), app, SLOT(quit()));
    }
    return app->exec();
//    return -1;
}
