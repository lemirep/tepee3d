#include "PlatformFactory.h"

IPlatformInitializer * PlatformFactory::platformInitializer = NULL;

IPlatformInitializer *PlatformFactory::getPlatformInitializer()
{
    if (PlatformFactory::platformInitializer == NULL)
    {
#if defined Q_OS_ANDROID
        PlatformFactory::platformInitializer = new AndroidPlatformInitializer();
#else
        PlatformFactory::platformInitializer = new GenericPlatformInitializer();
#endif
    }
    return PlatformFactory::platformInitializer;
}
