#include "PluginBase.h"
//DEBUG
#include <iostream>

Plugins::PluginBase::PluginBase()
{
    std::cout << "NEW PLUGINBASE INSTANCE CREATED " << std::endl;
}

Plugins::PluginBase* Plugins::PluginBase::getPluginBase()
{
    return this;
}

void    Plugins::PluginBase::resultFromSQL()
{
    std::cout << "PLUGIN BASE RESULT FROM SQL" << std::endl;
}
