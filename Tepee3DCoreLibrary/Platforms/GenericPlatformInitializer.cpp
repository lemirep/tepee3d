#include "GenericPlatformInitializer.h"

GenericPlatformInitializer::GenericPlatformInitializer() : IPlatformInitializer()
{
}

bool GenericPlatformInitializer::initPlatform()
{
    return true;
}

QDir GenericPlatformInitializer::getDataDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    return dir;
}

QDir GenericPlatformInitializer::getServicesSharedLibrariesDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(GENERIC_SERVICES_LIBRARIES_DIR);
    return dir;
}

QDir GenericPlatformInitializer::getRoomSharedLibraryDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(GENERIC_ROOM_LIBRARY_DIR);
    return dir;
}

QDir GenericPlatformInitializer::getWidgetSharedLibrariesDirectory() const
{
    QDir    dir = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
       dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS")
    {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(GENERIC_WIDGET_LIBRARIES_DIR);
    return dir;
}

QString GenericPlatformInitializer::getPlatformName() const
{
#if defined Q_OS_QNX
    return QNX_PLATFORM;
#elif defined Q_OS_MACX
    return MAC_PLATFORM;
#elif defined Q_OS_IOS
    return IOS_PLATFORM;
#elif defined Q_OS_LINUX
    #if defined Q_PROCESSOR_X86_64
        return LINUX_64_PLATFORM;
    #else
        return LINUX_32_PLATFORM;
    #endif
#elif defined Q_OS_UNIX
    #if define Q_PROCESSOR_X86_64
        return UNIX_64_PLATFORM;
    #else
        return UNIX_32_PLATFORM;
    #endif
#elif defined Q_OS_WIN32
    return WINDOWS_32_PLATFORM;
#elif defined Q_OS_WIN64
    return WINDOWS_64_PLATFORM;
#endif
}
