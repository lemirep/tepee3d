/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include "QmlAsTexture.h"
#include "QDebug"

QmlAsTexture::QmlAsTexture(QQuickItem* parent) : QQuickItem(parent)
{
    this->sourceItem = NULL;
    this->textureId = 0;
    this->effectItem = NULL;
    this->provider = NULL;
    this->texture = NULL;
    this->setFlag(ItemHasContents, true);
}

// THIS METHOD IS EXECUTED IN THE RENDERING THREAD
QSGNode*    QmlAsTexture::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    qDebug() << "Updating paint node";
    if (!this->provider && this->sourceItem)
    {
        qDebug() << "Setting provider";
        this->provider = this->sourceItem->textureProvider();
        QObject::connect(this->provider, SIGNAL(textureChanged()), this, SLOT(textureChanged()), Qt::DirectConnection);
    }

    if (this->provider && !this->texture)
    {
        this->texture = this->provider->texture();
        qDebug() << "Texture Id " << this->texture->textureId() << " SIZE " << this->texture->textureSize();
        if (this->texture->textureId() == 0)
        {
            this->texture = NULL;
            this->update();
        }
        else
            emit textureChanged();
    }

    //if (this->texture && this->effectItem)
    //     this->effectItem->triggerDynamicTextureUpdate();

    //    this->update();
    return oldNode;
}

// THIS METHOD IS EXECUTED IN THE RENDERING THREAD
void        QmlAsTexture::textureChanged()
{
    if (!this->effectItem)
        return ;
    QSGDynamicTexture *txt  = dynamic_cast<QSGDynamicTexture*>(this->provider->texture());
    if (txt)
    {
        qDebug() << "Texture Id " << txt->textureId() << " SIZE " << txt->textureSize();
        this->effectItem->setDynamicTexture(txt->textureId(), txt->textureSize());
    }
}

void        QmlAsTexture::setSourceItem(QQuickItem *sourceItem)
{
    if (this->sourceItem != sourceItem)
    {
        this->sourceItem = sourceItem;
        if (this->sourceItem)
        {
            this->sourceItem->setParentItem(this);
            this->sourceItem->setParent(this);
            this->update();
        }
        emit sourceItemChanged();
    }
}

QQuickItem* QmlAsTexture::getSourceItem()
{
    return this->sourceItem;
}

void            QmlAsTexture::setEffectItem(QQuickEffect *effectItem)
{
    qDebug() << " SETTING EFFECT ITEM";
    if (this->effectItem != effectItem)
    {
        this->effectItem = effectItem;
        if (this->effectItem)
        {
            qDebug() << "EFFECT ITEM SET ";
            this->update();
        }
        emit effectItemChanged();
    }
}

QQuickEffect*   QmlAsTexture::getEffectItem()
{
    return this->effectItem;
}

//void        QmlAsTexture::paint(QPainter *painter)
//{
//    // DO NOTHING HERE HOPING THE CHILDREN ARE ALSO RENDERED IN THE IMAGE
//}
