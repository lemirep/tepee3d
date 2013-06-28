#include "PlaylistModelItem.h"

PlaylistModelItem::PlaylistModelItem(QObject *parent) : Models::SubListedListItem(parent)
{
    this->m_playlistItemsModel = new Models::ListModel(new PlayableItemModel(NULL));
    this->m_playlistTypeString = "";
    this->m_playlistId = -1;
}

PlaylistModelItem::PlaylistModelItem(int playlistId, const QString& playlistTypeString, QObject *parent)
    : Models::SubListedListItem(parent),
      m_playlistId(playlistId),
      m_playlistTypeString(playlistTypeString)
{
    this->m_playlistItemsModel = new Models::ListModel(new PlayableItemModel(NULL));
    qDebug() << "Type " << this->m_playlistTypeString;
    qDebug() << "Id " << this->m_playlistId;
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
    case playlistTypeString:
        return this->getPlaylistTypeString();
    default :
        return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModelItem::roleNames() const
{
    QHash<int, QByteArray> roleNames;

    roleNames[playlistId] = "playlistId";
    roleNames[playlistTypeString] = "playlistTypeString";

    return roleNames;
}

QString PlaylistModelItem::getPlaylistTypeString() const
{
    return this->m_playlistTypeString;
}

