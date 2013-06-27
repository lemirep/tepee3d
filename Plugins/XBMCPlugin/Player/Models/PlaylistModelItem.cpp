#include "PlaylistModelItem.h"

PlaylistModelItem::PlaylistModelItem(QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_playlistItemsModel = new Models::ListModel(new PlayableItemModel(NULL));
}

PlaylistModelItem::PlaylistModelItem(int playlistId, PlaylistModelItem::PlaylistTypes playlistType, QObject *parent)
    : Models::SubListedListItem(parent),
      m_playlistId(playlistId),
      m_playlistType(playlistType)
{
    this->m_playlistItemsModel = new Models::ListModel(new PlayableItemModel(NULL));
}


PlaylistModelItem::~PlaylistModelItem()
{
    delete this->m_playlistItemsModel;
}

Models::ListModel *PlaylistModelItem::submodel() const
{
    return this->m_playlistItemsModel;
}


int PlaylistModelItem::id() const
{
    return this->m_playlistId;
}


QVariant PlaylistModelItem::data(int role) const
{
    switch (role)
    {
    case playlistId:
        return this->id();
    case playlistType:
        return this->getPlaylistType();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModelItem::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[playlistId] = "playlistId";
    roleNames[playlistType] = "playlistType";

    return roleNames;
}

PlaylistModelItem::PlaylistTypes PlaylistModelItem::getPlaylistType() const
{
    return this->m_playlistType;
}


PlaylistModelItem::PlaylistTypes PlaylistModelItem::typeFromString(QString typeString)
{
    if (typeString.compare("audio") == 0)
        return Audio;
    if (typeString.compare("video") == 0)
        return Video;
    if (typeString.compare("picture") == 0)
        return Pictures;
}
