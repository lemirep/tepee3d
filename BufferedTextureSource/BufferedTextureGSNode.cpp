#include "BufferedTextureGSNode.h"
#include <iostream>

BufferedTextureGSNode::BufferedTextureGSNode() : QObject(), QSGSimpleTextureNode()
{
    this->setFlag(QSGSimpleTextureNode::UsePreprocess, true);
}

void    BufferedTextureGSNode::makeDirtyTexture()
{
    std::cout << "makeDirtyTextureSlot" << std::endl;
    this->markDirty(QSGSimpleTextureNode::DirtyMaterial);
}
