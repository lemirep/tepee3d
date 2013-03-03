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


    static PluginState valueOf(int value)
    {
        switch (value)
        {
        case 0 :
            return pluginIdleState;
        case 1 :
            return pluginSelectedState;
        case 2:
            return pluginFocusedState;
        default :
            return pluginIdleState;
        }
    }
};

}

#endif // PLUGINENUMS_H
