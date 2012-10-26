#ifndef BUFFEREDTEXTUREGSNODE_H
#define BUFFEREDTEXTUREGSNODE_H

#include <QSGSimpleTextureNode>

class BufferedTextureGSNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    BufferedTextureGSNode();

private slots:
    void    makeDirtyTexture();
};

#endif // BUFFEREDTEXTUREGSNODE_H
