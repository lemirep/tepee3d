#include <QGuiApplication>
#include <QPluginLoader>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <CoreLibraryInterface.h>

#define CORE_LIBRARY_DIRECTORY "libraries/core"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QGuiApplication *app = new QGuiApplication(argc, argv);
    CoreLibraryInterface *coreEngine = NULL;
    QDir libDir;
    QPluginLoader loader;

#ifndef Q_OS_ANDROID
    libDir = QCoreApplication::applicationDirPath();
    libDir.cd(CORE_LIBRARY_DIRECTORY);
    qDebug() << libDir.absolutePath();
    qDebug() << libDir.absoluteFilePath(libDir.entryList(QDir::Files).first());
    loader.setFileName(libDir.absoluteFilePath(libDir.entryList(QDir::Files).first()));
#endif

#ifdef Q_OS_ANDROID
    libDir = QDir("/data/data/org.qtproject.example.Tepee3D/lib");
    qDebug() << libDir.absolutePath();
    qDebug() << libDir.absoluteFilePath("libCoreLibrary.so");
     loader.setFileName(libDir.absoluteFilePath("libCoreLibrary.so"));
#endif

    qDebug() << "Trying to load Core Library";
    if ((coreEngine = qobject_cast<CoreLibraryInterface *>(loader.instance())) != NULL)
    {
        qDebug() << "Core Library Loaded";
        coreEngine->initCoreEngine();
        QObject::connect(coreEngine->getObject(), SIGNAL(quit()), app, SLOT(quit()));
    }
    else
    {
        qDebug() << "Couldnt load core library";
        qDebug() << loader.errorString();
    }
    return app->exec();
}
