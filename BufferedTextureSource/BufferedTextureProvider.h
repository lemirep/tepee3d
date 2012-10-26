#ifndef BUFFEREDTEXTUREPROVIDER_H
#define BUFFEREDTEXTUREPROVIDER_H

#include <QtQuick/QSGTextureProvider>
#include "BufferedTextureQSGTexture.h"
#include <stdlib.h>

class BufferedTextureQSGTexture;

class BufferedTextureProvider : public QSGTextureProvider
{
    Q_OBJECT

private:

public:

    BufferedTextureProvider();
    QSGTexture* texture() const;

    BufferedTextureQSGTexture  *sourceTexture;
    QSGTexture::Filtering filtering;
    QSGTexture::Filtering mipmapFiltering;
    QSGTexture::WrapMode horizontalWrap;
    QSGTexture::WrapMode verticalWrap;

};

#endif // BUFFEREDTEXTUREPROVIDER_H
