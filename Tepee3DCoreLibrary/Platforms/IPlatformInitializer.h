#ifndef IPLATFORMINITIALIZER_H
#define IPLATFORMINITIALIZER_H

#include <QString>
#include <QDir>

#define QNX_PLATFORM "qnx"
#define IOS_PLATFORM "ios"
#define MAC_PLATFORM "mac"
#define LINUX_32_PLATFORM "linux_32"
#define LINUX_64_PLATFORM "linux_64"
#define UNIX_32_PLATFORM "unix_32"
#define UNIX_64_PLATFORM "unix_64"
#define WINDOWS_32_PLATFORM "windows_32"
#define WINDOWS_64_PLATFORM "windows_64"
#define ANDROID_PLATFORM "android"


class IPlatformInitializer
{
public :
    virtual bool            initPlatform() = 0;
    virtual QDir           getDataDirectory() const = 0;
    virtual QDir           getWidgetSharedLibrariesDirectory() const = 0;
    virtual QDir           getServicesSharedLibrariesDirectory() const = 0;
    virtual QDir           getRoomSharedLibraryDirectory() const = 0;
    virtual QString      getPlatformName() const = 0;
};

#endif // IPLATFORMINITIALIZER_H
