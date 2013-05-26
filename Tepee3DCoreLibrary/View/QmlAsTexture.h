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

#ifndef QMLASTEXTURE_H
#define QMLASTEXTURE_H

#include <QQuickItem>
#include <QSGDynamicTexture>
#include <QQuickEffect>
#include <QSGTextureProvider>
#include <QTimer>

class QmlAsTexture : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* sourceItem READ getSourceItem WRITE setSourceItem NOTIFY sourceItemChanged)
    Q_PROPERTY(QQuickEffect* effectItem READ getEffectItem WRITE setEffectItem NOTIFY effectItemChanged)
public:
    QmlAsTexture(QQuickItem* parent = 0);
    QQuickItem*     getSourceItem();
    void            setSourceItem(QQuickItem* sourceItem);
    QQuickEffect*   getEffectItem();
    void            setEffectItem(QQuickEffect* effectItem);

protected:
    QSGNode *       updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData * updatePaintNodeData);

private:
    QQuickItem*         sourceItem;
    QQuickEffect*       effectItem;
    GLuint              textureId;
    QSGTextureProvider* provider;
    QSGTexture*         texture;


    void            applyTextureToEffect();

private slots:
    void            textureChanged();

signals:
    void    sourceItemChanged();
    void    effectItemChanged();


};

#endif // QMLASTEXTURE_H
