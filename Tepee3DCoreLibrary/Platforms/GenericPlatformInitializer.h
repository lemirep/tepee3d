#ifndef GENERICPLATFORMINITIALIZER_H
#define GENERICPLATFORMINITIALIZER_H

#include "IPlatformInitializer.h"
#include <QCoreApplication>

#define GENERIC_DATA_DIR ""
#define GENERIC_WIDGET_LIBRARIES_DIR "libraries/widget_libraries"
#define GENERIC_ROOM_LIBRARY_DIR "libraries/room_library"
#define GENERIC_SERVICES_LIBRARIES_DIR "libraries/services_lib"

class GenericPlatformInitializer : public IPlatformInitializer
{
public:
    GenericPlatformInitializer();
    bool        initPlatform();
    QDir       getDataDirectory() const;
    QDir       getWidgetSharedLibrariesDirectory() const;
    QDir       getServicesSharedLibrariesDirectory() const;
    QDir       getRoomSharedLibraryDirectory() const;
    QString  getPlatformName() const;
};

#endif // GENERICPLATFORMINITIALIZER_H
