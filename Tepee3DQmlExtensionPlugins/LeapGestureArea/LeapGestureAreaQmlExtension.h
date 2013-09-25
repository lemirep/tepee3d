#ifndef LEAPGESTUREAREAQMLEXTENSION_H
#define LEAPGESTUREAREAQMLEXTENSION_H

#include "LeapGestureArea.h"
#include <QQmlExtensionPlugin>

class LeapGestureAreaQmlExtension : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.QmlExtensionPlugins.leapgesturearea")

public :
    void registerTypes(const char *uri);
};


#endif // LEAPGESTUREAREAQMLEXTENSION_H
