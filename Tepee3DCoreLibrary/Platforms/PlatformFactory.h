#ifndef PLATFORMFACTORY_H
#define PLATFORMFACTORY_H

#include <QHash>
#include <QByteArray>
#include "GenericPlatformInitializer.h"
#include "AndroidPlatformInitializer.h"

class PlatformFactory
{
public:
    static IPlatformInitializer *getPlatformInitializer();
  private:
    static IPlatformInitializer *platformInitializer;
};

#endif // PLATFORMFACTORY_H
