
#include "BufferedTextureSourceQMLPlugin.h"


BufferedTextureSourceQMLPlugin::BufferedTextureSourceQMLPlugin() : QQmlExtensionPlugin()
{
    std::cout << " CONSTRUCTOR OF PLUGIN" << std::endl;
}

void    BufferedTextureSourceQMLPlugin::registerTypes(const char *uri)
{
    std::cout << "--------REGISTERING TYPES --------- " << uri << std::endl;
    qDebug(uri);
    Q_ASSERT(uri == QLatin1String("Tepee3D"));
    // Name of import, version major, version minor, Name of C++ QQuickItem to register in QML
    qmlRegisterType<BufferedTextureSource>("BufferedTextureSourcePlugin", 1, 0, "BufferedTextureSource");
}
