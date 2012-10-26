#include "ServicesManager.h"

// FOR DEBUG
#include <iostream>

Services::ServicesManager::ServicesManager(QObject *parent) : QObject(parent)
{
    this->loadServicesLibraries();
}

void    Services::ServicesManager::exposeContentToQml(QQmlContext *context)
{

}

bool    Services::ServicesManager::loadServicesLibraries()
{
    QDir    serviceDirectory = QApplication::applicationDirPath();

    // GO TO LIB DIRECTORIES
#if defined(Q_OS_WIN)
    if (serviceDirectory.dirName().toLower() == "debug" || serviceDirectory.dirName().toLower() == "release")
        serviceDirectory.cdUp();
#elif defined(Q_OS_MAC)
    if (serviceDirectory.dirName() == "MacOS")
    {
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
        serviceDirectory.cdUp();
    }
#endif
    serviceDirectory.cdUp();
    serviceDirectory.cd(SERVICE_LIBRARIES_DIRECTORY);

    std::cout << "SERVICE DIR " << serviceDirectory.absolutePath().toStdString() << std::endl;
    // LOAD ALL SERVICES LIBRARIES FOUND IN DIRECTORY

    foreach (QString filename, serviceDirectory.entryList(QDir::Files))
    {
        std::cout << "SERVICE LIBRARY " << filename.toStdString() << std::endl;
        QPluginLoader loader(serviceDirectory.absoluteFilePath(filename));
        ServiceInterface* service = qobject_cast<ServiceInterface *>(loader.instance());
        if (service)
        {
            service->initLibraryConnection(this);
            std::cout << "LIBRARY INITIALIZED" << std::endl;
        }
        else
        {
            std::cout << "ERRORS : "<< loader.errorString().toStdString() << std::endl;
            std::cout << "FAILED TO LOAD LIBRARY" << std::endl;
        }
    }
    return true;
}
