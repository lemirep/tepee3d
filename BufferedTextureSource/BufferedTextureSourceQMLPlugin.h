#ifndef BUFFEREDTEXTURESOURCEQMLPLUGIN_H
#define BUFFEREDTEXTURESOURCEQMLPLUGIN_H

#include <Qt/qqmlextensionplugin.h>
#include <iostream>
#include "BufferedTextureSource.h"


class BufferedTextureSourceQMLPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "BufferedTextureSource")

public :

    BufferedTextureSourceQMLPlugin();
//    void    initializeEngine(QQmlEngine *engine, const char *uri)
    void    registerTypes(const char *uri);

};



#endif // BUFFEREDTEXTURESOURCEQMLPLUGIN_H
