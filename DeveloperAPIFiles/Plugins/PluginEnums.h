#ifndef PLUGINENUMS_H
#define PLUGINENUMS_H

#include <QObject>

namespace Plugins
{

class PluginEnums : public QObject
{
    Q_OBJECT
    Q_ENUMS(PluginState)

public :
    enum    PluginState
    {
        pluginIdleState = 0,
        pluginSelectedState,
        pluginFocusedState
    };
};

}

#endif // PLUGINENUMS_H
