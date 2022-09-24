#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
class Tile{

    Sprite cover;
    Sprite _flag;

public:
    Sprite extra;
    int adjMine = 0;
    int numRevealed = 0;
    bool isClicked;
    bool isDebug;
    bool isMine;
    bool isFlagged;
    Sprite background;
    vector<Tile*> neighbors;
    int x;
    int y;
    Tile();
    void draw(RenderWindow& window);
    void reveal();
    void flagged();
    void setPosition(int x, int y);
    void num();
    void toggleDebug();
};

