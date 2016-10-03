#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.hpp"
#include <vector>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600) ,"Pixel Run");
    window.setFramerateLimit(200);
    
    const int scale = 2;
    //background stuff
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("/Users/Newton/downloads/pixelRunnerBackground.png");
    
    Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    background.setScale(9, 9);
    
    //floor sruff
    Texture floorTexture;
    floorTexture.loadFromFile("/Users/Newton/downloads/pixelRunnerFloor.png");
    Sprite floor;
    Sprite floor2;
    Sprite floor3;
    floor.setTexture(floorTexture);
    floor2.setTexture(floorTexture);
    floor3.setTexture(floorTexture);
    floor.setPosition(0, 540);
    floor2.setPosition(475, 540);
    floor3.setPosition(950, 540);
    floor.setScale(5, 5);
    floor2.setScale(5, 5);
    floor3.setScale(5, 5);
    
    //coin stuff
    Texture coinFaceTexture;
    Texture coinSideTexture;
    
    coinFaceTexture.loadFromFile("/Users/Newton/downloads/coinFace.png");
    coinSideTexture.loadFromFile("/Users/Newton/downloads/coinSide.png");
    
    Sprite coin;
    const int cointRootPosY = 450;
    coin.setTexture(coinFaceTexture);
    coin.setPosition(500, 450);
    
    Clock coinClock;
    //player textures
    Texture playerTexture;
    
    if(!playerTexture.loadFromFile("/Users/Newton/downloads/playerNormal.png")) {
        cout<<"error loading player"<<endl;
    }
    
    Texture playerRunningTexture;
    
    if(!playerRunningTexture.loadFromFile("/Users/Newton/downloads/playerRunning.png")) {
        cout<<"error loading player running"<<endl;
    }
    
    //player
    Sprite player;
    const int playerWidth = 100;
    player.setTexture(playerRunningTexture);
    const int playerRootX = 350;
    const int playerRootY = 450;
    player.setPosition(playerRootX, playerRootY);
   
    //player actions
    
    Clock jumpClock;
    Clock runClock;
    
    bool playerSlideing = false;
    bool playerJumping = false;
    
    
    while(window.isOpen()) {
        Event event;
        
        while(window.pollEvent(event)) {
            
            if(event.type == Event::Closed) {
                window.close();
            }
            
            switch (event.key.code) {
                case Keyboard::S:
                    playerSlideing = true;
                    break;
                    
                case Keyboard::W:
                    if(!playerJumping) {
                        playerJumping = true;
                        jumpClock.restart();
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        //player actions
        Time runningTime = runClock.getElapsedTime();
        Time runReset = seconds(0.3);
        Time runReset2 = seconds(0.15);
        if(runningTime < runReset2) {
            player.setTexture(playerRunningTexture);
            player.setScale(1, 1);
        }
        else {
            player.setTexture(playerTexture);
            player.setScale(3, 3);
        }
        if(runningTime > runReset) {
            runClock.restart();
        }
        
        if(playerSlideing) {
            player.setRotation(-45);
        }
        
        if(playerJumping) {
            Time elapsedTime = jumpClock.getElapsedTime();
            Time fiveSecounds = seconds(0.5);
            if(elapsedTime < fiveSecounds) {
                player.move(0, -1);
            }
            else {
                player.move(0, 1);
            }
            if(player.getPosition().y == playerRootY) {
                playerJumping = false;
            }
        }
        
        //coin actions
        
        Time coinTime = coinClock.getElapsedTime();
        Time coinReset = seconds(0.3);
        Time coinReset2 = seconds(0.15);
        if(coinTime < coinReset2) {
            coin.setTexture(coinSideTexture);
        }
        else {
            coin.setTexture(coinFaceTexture);
        }
        
        if(coinTime > coinReset) {
            coinClock.restart();
        }
        
        coin.move(-1, 0);
        if(coin.getPosition().x < -20 ) {
            coin.setPosition(800, cointRootPosY);
        }
        //coinCollitions
        if(coin.getPosition().x > player.getPosition().x && coin.getPosition().y == player.getPosition().y) {
            
        }
        //floor actions
        floor.move(-1, 0);
        floor2.move(-1, 0);
        floor3.move(-1, 0);
        
        if(floor.getPosition().x + 475 < 0) {
            floor.setPosition(0, 540);
        }
        if(floor2.getPosition().x + 475 < 475) {
            cout<<"floor 2"<<endl;
            floor2.setPosition(0, 540);
        }
        if(floor3.getPosition().x + 475 < 950) {
            cout<<"floor 3"<<endl;
            floor3.setPosition(0, 540);
        }
        
        //window loading
        
        window.clear(Color::White);
        window.draw(background);
        window.draw(floor);
        window.draw(floor3);
        window.draw(floor2);
        window.draw(coin);
        window.draw(player);
        window.display();
    }
    
    return EXIT_SUCCESS;
}
