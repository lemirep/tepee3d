#ifndef TEPEE3DTOUCHAREAQMLEXTENSIONPLUGIN_H
#define TEPEE3DTOUCHAREAQMLEXTENSIONPLUGIN_H

#include <QQmlExtensionPlugin>
#include "Tepee3DTouchArea.h"


class Tepee3DTouchAreaQmlExtensionPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.tepee3d.QmlExtensionPlugins.tepee3dtoucharea")

    // QQmlTypesExtensionInterface interface
public:
    void registerTypes(const char *uri);
};

#endif // TEPEE3DTOUCHAREAQMLEXTENSIONPLUGIN_H
