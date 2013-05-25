#ifndef ANDROIDPLATFORMINITIALIZER_H
#define ANDROIDPLATFORMINITIALIZER_H

#include "IPlatformInitializer.h"

#define ANDROID_LIB_DIR "/data/data/org.qtproject.example.Tepee3D/lib"
#define ANDROID_DATA_DIR "/data/data/org.qtproject.example.Tepee3D"


class AndroidPlatformInitializer : public IPlatformInitializer
{
public:
    AndroidPlatformInitializer();
    bool initPlatform();
    virtual QDir           getDataDirectory() const;
    virtual QDir           getWidgetSharedLibrariesDirectory() const;
    virtual QDir           getServicesSharedLibrariesDirectory() const;
    virtual QDir           getRoomSharedLibraryDirectory() const;
    virtual QString      getPlatformName() const;
};

#endif // ANDROIDPLATFORMINITIALIZER_H
