#include "Tile.h"
#include "TextureManager.h"

Tile::Tile() {
    background.setTexture(TextureManager::getTexture("tile_revealed"));
    cover.setTexture(TextureManager::getTexture("tile_hidden"));
    _flag.setTexture(TextureManager::getTexture("flag"));
    isClicked = false;
    isFlagged = false;
    isMine = false;
    isDebug = false;
    for (int i = 0; i < 8; i++){
        neighbors.push_back(nullptr);
    }
}
void Tile::draw(RenderWindow& window) {
    if (!isClicked) {
        window.draw(cover);
        if (isFlagged){
            window.draw(_flag);
        }
        if (isDebug && isMine){
            window.draw(extra);
        }
    }
    else{
        window.draw(background);
        window.draw(extra);
    }
}

void Tile::reveal() {
    if (!isClicked && !isFlagged){
        isClicked = true;
        if (adjMine == 0 && !isMine){
            for (int i = 0; i < 8; i++){
                if (neighbors[i] != nullptr && !neighbors[i]->isMine)
                neighbors[i]->reveal();
            }
        }
    }
}

void Tile::setPosition(int x, int y) {
    cover.setPosition(x,y);
    background.setPosition(x,y);
    _flag.setPosition(x,y);
    extra.setPosition(x,y);
    this->x = x;
    this->y = y;
}

void Tile::flagged() {
    if (!isClicked){
        isFlagged=!isFlagged;
    }
}
void Tile::num(){
    if (isMine){
        extra.setTexture(TextureManager::getTexture("mine"));
    }
    else{
        for (int i = 0; i < 8; i++){
            if (neighbors[i] != nullptr && neighbors[i]->isMine){
                adjMine++;
            }
        }
        if (adjMine ==1){
            extra.setTexture(TextureManager::getTexture("number_1"));
        }
        else if (adjMine == 2){
            extra.setTexture(TextureManager::getTexture("number_2"));
        }
        else if (adjMine ==3){
            extra.setTexture(TextureManager::getTexture("number_3"));
        }
        else if (adjMine ==4){
            extra.setTexture(TextureManager::getTexture("number_4"));
        }
        else if (adjMine ==5){
            extra.setTexture(TextureManager::getTexture("number_5"));
        }
        else if (adjMine ==6){
            extra.setTexture(TextureManager::getTexture("number_6"));
        }
        else if (adjMine ==7){
            extra.setTexture(TextureManager::getTexture("number_7"));
        }
        else if (adjMine ==8){
            extra.setTexture(TextureManager::getTexture("number_8"));
        }
    }
}

void Tile::toggleDebug() {
    isDebug = !isDebug;
}



