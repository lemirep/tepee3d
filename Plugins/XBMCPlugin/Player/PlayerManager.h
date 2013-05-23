#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#define MAJOR_ID_REQUEST 4
#define REQUEST_ID_BUILDER(id) ((MAJOR_ID_REQUEST * 10) + id)

class PlayerManager
{
public:
    PlayerManager();
};

#endif // PLAYERMANAGER_H
