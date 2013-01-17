#ifndef VIEWTOMODELMAPPER_H
#define VIEWTOMODELMAPPER_H

#include <QObject>
#include "RoomManager.h"

namespace View
{
// ACT AS AN INTERMEDIARY BETWEEN VIEW OBJECT/QML AND MODELS
// ALL INTERACTIONS BETWEEN THE VIEW AND THE MODEL SHOULD GO HERE

class ViewToModelMapper : public QObject
{
    Q_OBJECT
public:
    explicit ViewToModelMapper(QObject *parent = 0);
    
    static Plugins::PluginBase* getPluginFromRoom(int roomId, int pluginId);


signals:
    
public slots:
    
};
}

#endif // VIEWTOMODELMAPPER_H
