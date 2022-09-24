#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;
using namespace sf;


class TextureManager{
    static unordered_map<string, Texture> textures;
    static void LoadTexture(string textureName);
public:
    static Texture& getTexture(string textureName);
    static void clear();
};