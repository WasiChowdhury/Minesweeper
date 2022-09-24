#include "TextureManager.h"
unordered_map<string, Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
    string path = "images/";
    path += textureName + ".png";
    textures[textureName].loadFromFile(path);
}

Texture& TextureManager::getTexture(string textureName) {
    if (textures.find(textureName) == textures.end()){
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::clear() {
    textures.clear();
}
