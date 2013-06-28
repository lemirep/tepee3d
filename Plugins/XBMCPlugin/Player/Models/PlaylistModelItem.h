#include <ListModel.h>
#include <SubListedListItem.h>
#include "PlayableItemModel.h"

class PlaylistModelItem : public Models::SubListedListItem
{
    Q_OBJECT
public :
    enum PlaylistModelItemRoles
    {
        playlistId = Qt::UserRole + 1,
        playlistTypeString
    };

    enum PlaylistTypes
    {
        Audio = 1,
        Video,
        Pictures
    };

private:

    int m_playlistId;
    QString       m_playlistTypeString;
    Models::ListModel *m_playlistItemsModel;

public :
    PlaylistModelItem(QObject *parent = 0);
    PlaylistModelItem(int playlistId, const QString& playlistTypeString, QObject *parent = 0);
    ~PlaylistModelItem();


    // SubListedListItem interface
public:
    Models::ListModel *submodel() const;

    // ListItem interface
public:
    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    QString       getPlaylistTypeString() const;
};
