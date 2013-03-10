#ifndef ROOMPROPERTIES_H
#define ROOMPROPERTIES_H

#include <QVector3D>
#include <QObject>
#include "ListModel.h"
#include "PluginBase.h"
#include "PluginModelItem.h"

namespace Room
{

class RoomProperties : public QObject
{
    Q_OBJECT

private :

    QString                         roomName;
    QVector3D                       position;
    QVector3D                       scale;

    Models::ListModel*              pluginsModel;

public:
    explicit RoomProperties(QObject *parent = 0);
    ~RoomProperties();

    void                            setScale(const QVector3D& scale);
    void                            setRoomName(const QString& name);
    void                            setPosition(const QVector3D& position);

    QString                         getRoomName()      const;

    QVector3D                       getPosition()      const;
    QVector3D                       getScale()         const;

    Models::ListModel*              getRoomPluginsModel() const;

signals:
    
public slots:
    
};

}

#endif // ROOMPROPERTIES_H
