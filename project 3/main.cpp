#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureManager.h"
#include "Random.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace sf;

void readConfig(int& width, int& height, int& mines){
    string tempWidth;
    string tempHeight;
    string tempMines;
    ifstream inFile("boards/config.cfg");
    getline(inFile,tempWidth);
    width = stoi(tempWidth);
    //cout<<width;
    getline(inFile,tempHeight);
    height = stoi(tempHeight);
    //cout<<height;
    getline(inFile,tempMines);
    mines = stoi(tempMines);
    //cout<<mines;
}
void test(string& filename,vector<vector<Tile>> &a){
    string row;
    string filename1 = "boards/" + filename + ".brd";
    vector<vector<string>> testBoard;
    ifstream inFile(filename1);
    string line;
    while (getline(inFile,line)){
        vector<string> testRow;
        for (int i = 0; i < line.length(); i++)
            testRow.push_back(line.substr(i, 1));
        testBoard.push_back(testRow);
    }
    for (int i = 0; i < testBoard.size(); i++) {
        for (int j = 0; j < testBoard[0].size(); j++) {
            if (testBoard[i][j] == '1'){
                a[j][i].isMine = true;
            }
        }

    }

}
void setNeighbors(vector<vector<Tile>> &x, int& width, int& height){
    for (int i = 0; i < width; i++){
        for (int j = 0;j<height;j++){
            if (i == 0 && j == 0){       //top left corner
                x[i][j].neighbors[4] = &x[i+1][j];
                x[i][j].neighbors[5] = &x[i+1][j+1];
                x[i][j].neighbors[6] = &x[i][j+1];
            }
            else if (i == width-1 && j == 0){     //top right corner
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[6] =&x[i][j+1];
                x[i][j].neighbors[7] =&x[i-1][j+1];
            }
            else if (i ==0 && j == height -1)  {    //bottom left corner
                x[i][j].neighbors[2] =&x[i][j-1];
                x[i][j].neighbors[3] =&x[i+1][j-1];
                x[i][j].neighbors[4] =&x[i+1][j];
            }
            else if (i == width-1 && j == height - 1){   //bottom right corner
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[1] =&x[i-1][j-1];
                x[i][j].neighbors[2] =&x[i][j-1];
            }
            else if(i !=0 && i != width-1 && j ==0){              //top row no corners
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[4] =&x[i+1][j];
                x[i][j].neighbors[5] =&x[i+1][j+1];
                x[i][j].neighbors[6] =&x[i][j+1];
                x[i][j].neighbors[7] =&x[i-1][j+1];
            }
            else if (i !=0 && i != width-1 && j ==height-1){   //bottom row no corners
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[4] =&x[i+1][j];
                x[i][j].neighbors[1] =&x[i-1][j-1];
                x[i][j].neighbors[2] =&x[i][j-1];
                x[i][j].neighbors[3] =&x[i+1][j-1];
            }
            else if(i == 0 && j != 0 && j!= height-1){     //left column no corners
                x[i][j].neighbors[6]=&x[i][j+1];
                x[i][j].neighbors[4] =&x[i+1][j];
                x[i][j].neighbors[5] =&x[i+1][j+1];
                x[i][j].neighbors[2] =&x[i][j-1];
                x[i][j].neighbors[3] =&x[i+1][j-1];
            }
            else if (i == width-1 && j != height - 1 && j!=0){    //right column no corners
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[6] =&x[i][j+1];
                x[i][j].neighbors[7] =&x[i-1][j+1];
                x[i][j].neighbors[1] =&x[i-1][j-1];
                x[i][j].neighbors[2] =&x[i][j-1];
            }
            else{       //middle
                x[i][j].neighbors[0] =&x[i-1][j];
                x[i][j].neighbors[6] =&x[i][j+1];
                x[i][j].neighbors[7] =&x[i-1][j+1];
                x[i][j].neighbors[1] =&x[i-1][j-1];
                x[i][j].neighbors[2] =&x[i][j-1];
                x[i][j].neighbors[4] =&x[i+1][j];
                x[i][j].neighbors[5] =&x[i+1][j+1];
                x[i][j].neighbors[3] =&x[i+1][j-1];
            }

        }
    }
}
void randomMines(vector<vector<Tile>> &a, int&width, int& height,int& mines){
    int tempMines = mines;
    int count = 0;
    while(count != tempMines){
        int x = Random::Int(0,width-1);
        int y = Random::Int(0,height-1);
        if (!a[x][y].isMine){
            a[x][y].isMine = true;
            count++;
        }

    }
}
void resetBoard(vector<vector<Tile>> &a, int& width, int& height){
    a.clear();
    vector<Tile> row(width);
    for (int i = 0;i <width;i++){
        for (int j = 0; j<height; j++){
            a.push_back(row);
            a[i][j].setPosition(i*32,j*32);
        }
    }

}
bool win(vector<vector<Tile>> &a, bool& b, bool& c, int& flagsLeft, int& width, int& height, int& mines){
    int numRevealed = 0;
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if (a[i][j].isClicked){
                numRevealed++;
            }
        }
    }
    if (numRevealed == (height*width)-mines  && !c){
        b = true;
    }
    return b;
}
void updateCounter(Sprite& neg, Sprite& hundred,  Sprite& ten, Sprite& one, int& flagsLeft){
    int temp = abs(flagsLeft);
    int ones = temp % 10;
    temp /= 10;
    int tens = temp % 10;
    temp /= 10;
    int hundreds = temp %10;
    if (flagsLeft < 0){
        neg.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
    }
    hundred.setTextureRect(Rect<int>(21 * hundreds, 0, 21, 32));
    ten.setTextureRect(Rect<int>(21 * tens, 0, 21, 32));
    one.setTextureRect(Rect<int>(21 * ones, 0, 21, 32));
}

int main(){
    int width;
    int height;
    int mines;
    int tempMines = mines;
    readConfig(width,height,mines);
    int flagsLeft = 0;
    flagsLeft = mines;
    sf::RenderWindow window(sf::VideoMode(width*32, height*32+88), "Minesweeper!");
    bool debugReset = false;
    bool isWin = false;
    bool isLose = false;
    int numRevealed = 0;
    vector<Tile> row(width);
    vector<vector<Tile>> board;
    Sprite face;
    face.setTexture(TextureManager::getTexture("face_happy"));
    face.setPosition(((window.getSize().x)/2)-32,(window.getSize().y)-88);
    Sprite debug;
    debug.setTexture(TextureManager::getTexture("debug"));
    debug.setPosition((((window.getSize().x)/2)+96),(window.getSize().y)-88);
    Sprite button1;
    button1.setTexture(TextureManager::getTexture("test_1"));
    button1.setPosition((((window.getSize().x)/2)+96+64),(window.getSize().y)-88);
    Sprite button2;
    button2.setTexture(TextureManager::getTexture("test_2"));
    button2.setPosition((((window.getSize().x)/2)+96+128),(window.getSize().y)-88);
    Sprite button3;
    button3.setTexture(TextureManager::getTexture("test_3"));
    button3.setPosition((((window.getSize().x)/2)+96+128+64),(window.getSize().y)-88);
    Sprite neg;
    neg.setTexture(TextureManager::getTexture("digits"));
    neg.setTextureRect(Rect<int>(0, 0, 21, 32));
    neg.setPosition(0,window.getSize().y-64);
    Sprite hundreds;
    hundreds.setTexture(TextureManager::getTexture("digits"));
    hundreds.setTextureRect(Rect<int>(0, 0, 21, 32));
    hundreds.setPosition(21,window.getSize().y-64);
    Sprite tens;
    tens.setTexture(TextureManager::getTexture("digits"));
    tens.setTextureRect(Rect<int>(0, 0, 21, 32));
    tens.setPosition(42,window.getSize().y-64);
    Sprite ones;
    ones.setTexture(TextureManager::getTexture("digits"));
    ones.setTextureRect(Rect<int>(0, 0, 21, 32));
    ones.setPosition(63,window.getSize().y-64);
    updateCounter(neg,hundreds,tens,ones,flagsLeft);

    for (int i = 0;i <width;i++){
        for (int j = 0; j<height; j++){
            board.push_back(row);
            board[i][j].setPosition(i*32,j*32);
        }
    }
    randomMines(board,width,height,mines);
    setNeighbors(board,width,height);
    for (int i = 0;i <width;i++){
        for (int j = 0; j<height; j++){
            board[i][j].num();
        }
    }
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                //flag
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == Mouse::Right && !isLose &&!isWin){
                    Vector2i mousepos = Mouse::getPosition(window);
                    for (int i = 0;i <width;i++){
                        for (int j = 0; j<height; j++){
                            auto bounds3 = board[i][j].background.getGlobalBounds();
                            if (bounds3.contains(mousepos.x, mousepos.y)){
                                board[i][j].flagged();
                                if (board[i][j].isFlagged){
                                    flagsLeft--;
                                }
                                else if (!board[i][j].isClicked){
                                    flagsLeft++;
                                }
                                updateCounter(neg,hundreds,tens,ones,flagsLeft);
                            }
                        }
                    }
                }
                //face button clicked
                if (event.mouseButton.button == Mouse::Left){
                    Vector2i mousepos = Mouse::getPosition(window);
                    auto bounds = face.getGlobalBounds();
                    if (bounds.contains(mousepos.x, mousepos.y)) {
                        face.setTexture(TextureManager::getTexture("face_happy"));
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                if(board[i][j].isDebug)
                                    debugReset = true;
                            }
                        }
                        resetBoard(board,width,height);
                        randomMines(board,width,height,mines);
                        setNeighbors(board,width,height);
                        isLose = false;
                        isWin = false;
                        flagsLeft = mines;
                        tempMines = mines;
                        updateCounter(neg,hundreds,tens,ones,flagsLeft);
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                board[i][j].num();
                            }
                        }
                        if (debugReset){
                            for (int i = 0; i < width; i++){
                                for (int j = 0; j < height;j++){
                                    board[i][j].toggleDebug();
                                    debugReset = false;
                                }
                            }
                        }

                    }
                    //debug button clicked
                    auto bounds4 = debug.getGlobalBounds();
                    if (bounds4.contains(mousepos.x, mousepos.y) && !isWin) {
                        for (int i = 0; i < width; i++){
                            for (int j = 0; j < height;j++){
                                board[i][j].toggleDebug();
                            }
                        }
                    }
                    //test 1 clicked
                    auto bounds5 = button1.getGlobalBounds();
                    if (bounds5.contains(mousepos.x, mousepos.y)) {
                        face.setTexture(TextureManager::getTexture("face_happy"));
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                if(board[i][j].isDebug)
                                    debugReset = true;
                            }
                        }
                        resetBoard(board,width,height);
                        string filename = "testboard1";
                        test(filename,board);
                        setNeighbors(board,width,height);
                        flagsLeft = 0;
                        tempMines = 0;
                        isLose = false;
                        isWin = false;
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                board[i][j].num();
                                if (board[i][j].isMine){
                                    flagsLeft++;
                                    tempMines++;
                                }
                            }
                        }
                        updateCounter(neg,hundreds,tens,ones,flagsLeft);
                        if (debugReset){
                            for (int i = 0; i < width; i++){
                                for (int j = 0; j < height;j++){
                                    board[i][j].toggleDebug();
                                    debugReset = false;
                                }
                            }
                        }
                    }
                    //test 2 clicked
                    auto bounds6 = button2.getGlobalBounds();
                    if (bounds6.contains(mousepos.x, mousepos.y)) {
                        face.setTexture(TextureManager::getTexture("face_happy"));
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                if(board[i][j].isDebug)
                                    debugReset = true;
                            }
                        }
                        resetBoard(board,width,height);
                        string filename = "testboard2";
                        test(filename,board);
                        setNeighbors(board,width,height);
                        flagsLeft = 0;
                        tempMines = 0;
                        isLose = false;
                        isWin = false;
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                board[i][j].num();
                                if (board[i][j].isMine){
                                    flagsLeft++;
                                    tempMines++;
                                }
                            }
                        }
                        updateCounter(neg,hundreds,tens,ones,flagsLeft);
                        if (debugReset){
                            for (int i = 0; i < width; i++){
                                for (int j = 0; j < height;j++){
                                    board[i][j].toggleDebug();
                                    debugReset = false;
                                }
                            }
                        }
                    }
                    //test 3 clicked
                    auto bounds7 = button3.getGlobalBounds();
                    if (bounds7.contains(mousepos.x, mousepos.y)) {
                        face.setTexture(TextureManager::getTexture("face_happy"));
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                if(board[i][j].isDebug)
                                    debugReset = true;
                            }
                        }
                        resetBoard(board,width,height);
                        string filename = "testboard3";
                        test(filename,board);
                        setNeighbors(board,width,height);
                        flagsLeft = 0;
                        tempMines = 0;
                        isLose = false;
                        isWin = false;
                        for (int i = 0;i <width;i++){
                            for (int j = 0; j<height; j++){
                                board[i][j].num();
                                if (board[i][j].isMine){
                                    flagsLeft++;
                                    tempMines++;
                                }
                            }
                        }
                        updateCounter(neg,hundreds,tens,ones,flagsLeft);
                        if (debugReset){
                            for (int i = 0; i < width; i++){
                                for (int j = 0; j < height;j++){
                                    board[i][j].toggleDebug();
                                    debugReset = false;
                                }
                            }
                        }
                    }
                    //tile clicked
                    for (int i = 0;i <width;i++){
                        for (int j = 0; j<height; j++){
                            auto bounds2 = board[i][j].background.getGlobalBounds();
                            if (bounds2.contains(mousepos.x, mousepos.y) && !isLose && !isWin) {
                                board[i][j].reveal();
                                if (board[i][j].isMine && board[i][j].isClicked){
                                    isLose = true;
                                    face.setTexture(TextureManager::getTexture("face_lose"));
                                    for (int k = 0; k < width; k++){
                                        for (int l = 0; l < height; l++){
                                            if (board[k][l].isFlagged && board[k][l].isMine){
                                                board[k][l].isFlagged = !board[k][l].isFlagged;
                                            }
                                            if (board[k][l].isMine){
                                                board[k][l].reveal();
                                            }
                                        }
                                    }
                                }
                                else{
                                    if (win(board, isWin, isLose, flagsLeft,width,height,tempMines)){
                                        face.setTexture(TextureManager::getTexture("face_win"));
                                        for (int k = 0; k < width; k++){
                                            for (int l = 0; l < height; l++){
                                                if (board[k][l].isMine && !board[k][l].isFlagged){
                                                    board[k][l].flagged();
                                                    flagsLeft--;
                                                    updateCounter(neg,hundreds,tens,ones,flagsLeft);

                                                }
                                                if (board[k][l].isDebug){
                                                    board[k][l].toggleDebug();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear();
        for (int i = 0;i <width;i++){
            for (int j = 0; j<height; j++){
                board[i][j].draw(window);
            }
        }
        window.draw(face);
        window.draw(debug);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        if (flagsLeft < 0){
            window.draw(neg);
        }
        window.draw(hundreds);
        window.draw(tens);
        window.draw(ones);
        window.display();
    }

    return 0;
}
