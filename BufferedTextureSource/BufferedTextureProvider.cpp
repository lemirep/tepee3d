#include "BufferedTextureProvider.h"

#include <iostream>

BufferedTextureProvider::BufferedTextureProvider() : QSGTextureProvider()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<NEW TEXTURE PROVIDER CREATED" << std::endl;
    this->sourceTexture = new BufferedTextureQSGTexture();
}

QSGTexture* BufferedTextureProvider::texture() const
{
    std::cout << "????????REQUESTING TEXTURE FORM PROVIDER " << std::endl;
    this->sourceTexture->setFiltering(this->filtering);
    this->sourceTexture->setMipmapFiltering(this->mipmapFiltering);
    this->sourceTexture->setHorizontalWrapMode(this->horizontalWrap);
    this->sourceTexture->setVerticalWrapMode(this->verticalWrap);
    return this->sourceTexture;
}
