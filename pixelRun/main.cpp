#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace sf;
using namespace std;

bool gameGoing = true;
bool menu = false;

int gameSpeed = 1;

int gameOver() {
    cout<<"gameover"<<endl;
    return EXIT_SUCCESS;
}

int menuScene() {
    cout<<"gameover"<<endl;
    return EXIT_SUCCESS;
}

int fireSpeed() {
    return 1 * gameSpeed;
}

int gamePlay() {
    RenderWindow window(VideoMode(800, 600) ,"Pixel Run");
    window.setFramerateLimit(200);
    
    const int scale = 2;
    Clock totalTime;
    
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
    bool collected = false;
    
    RectangleShape coinCollitionBox(Vector2f(50, 50));
    coinCollitionBox.setPosition(500, 450);
    Clock coinClock;
    
    Font coinTextFont;
    coinTextFont.loadFromFile("sansation.ttf");
    if(!coinTextFont.loadFromFile("sansation.ttf")) {
        cout<<"error loading text"<<endl;
    }
    
    Text coinNumberText;
    coinNumberText.setString("panda");
    coinNumberText.setColor(Color::Black);
    coinNumberText.setCharacterSize(50);
    //fire stuff
    Texture fireTexture1;
    Texture fireTexture2;
    Texture fireTexture3;
    
    fireTexture1.loadFromFile("/Users/Newton/downloads/fire1.png");
    fireTexture2.loadFromFile("/Users/Newton/downloads/fire2.png");
    fireTexture3.loadFromFile("/Users/Newton/downloads/fire3.png");
    
    int fireRootY = 470;
    int fire1X = 600;
    int fire2X = 1000;
    int fire3X = 1400;
    int fireCollitionRootY = 490;
    
    int fireResetRandom1 = rand() % 2 + 1;
    int fireResetRandom2 = rand() % 2 + 1;
    int fireResetRandom3 = rand() % 2 + 1;
    bool fireIsReset1, fireIsReset2, fireIsReset3;
    if(fireResetRandom1 == 2) {
        fireIsReset1 = true;
    }
    else {
        fireIsReset1 = false;
    }
    if(fireResetRandom2 == 2) {
        fireIsReset2 = true;
    }
    else {
        fireIsReset2 = false;
    }
    if(fireResetRandom3 == 2) {
        fireIsReset3 = true;
    }
    else {
        fireIsReset3 = false;
    }
    
    int fireCollitionWidth = 70;
    int fireCollitionHeight = 50;
    
    Sprite fire1, fire2, fire3;
    fire1.setTexture(fireTexture1);
    fire1.setPosition(fire1X, fireRootY);
    fire2.setTexture(fireTexture1);
    fire2.setPosition(fire2X, fireRootY);
    fire3.setTexture(fireTexture1);
    fire3.setPosition(fire3X, fireRootY);
    
    Clock fireClock;
    //laserStuff
    Texture laserTexture;
    laserTexture.loadFromFile("/Users/Newton/downloads/laser.png");
    
    Sprite laser1, laser2;
    
    laser1.setTexture(laserTexture);
    laser2.setTexture(laserTexture);
    laser1.setPosition(100, 490);
    laser2.setPosition(300, 490);
    
    int laserCollitionSize = 50;
    RectangleShape laserCollition1(Vector2f(laserCollitionSize, laserCollitionSize));
    RectangleShape laserCollition2(Vector2f(laserCollitionSize, laserCollitionSize));
    
    laserCollition1.setPosition(100, 100);
    laserCollition2.setPosition(200, 200);
    //player textures
    Texture playerTexture;
    playerTexture.loadFromFile("/Users/Newton/downloads/playerNormal.png");
    
    Texture playerRunningTexture;
    playerRunningTexture.loadFromFile("/Users/Newton/downloads/playerRunning.png");
    
    Texture playerSlidingTexture;
    playerSlidingTexture.loadFromFile("//Users/Newton/downloads/playerSliding.png");
    //player
    Sprite player;
    const int playerWidth = 100;
    player.setTexture(playerRunningTexture);
    const int playerRootX = 350;
    const int playerRootY = 450;
    player.setPosition(playerRootX, playerRootY);
    int playerCoins = 0;
    //player collition box
    RectangleShape playerCollitionBox(Vector2f(50, 100));
    playerCollitionBox.setPosition(playerRootX + 20, playerRootY);
    //player actions
    
    Clock jumpClock;
    Clock runClock;
    Clock slideClock;
    
    bool playerSlideing = false;
    bool playerJumping = false;
    
    while(window.isOpen()) {
        Event event;
        
        while(window.pollEvent(event)) {
            
            if(event.type == Event::Closed) {
                window.close();
            }
            if(gameGoing == true) {
                switch (event.key.code) {
                    case Keyboard::S:
                        if(!playerSlideing) {
                            playerSlideing = true;
                            slideClock.restart();
                        }
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
        }
        //player actions
        Time runningTime = runClock.getElapsedTime();
        Time runReset = seconds(0.3);
        Time runReset2 = seconds(0.15);
        if(!playerSlideing && gameGoing == true) {
            if(runningTime < runReset2) {
                player.setTexture(playerRunningTexture);
                player.setScale(1, 1);
            }
            else {
                player.setTexture(playerTexture);
                player.setScale(3, 3);
            }
        }
        if(runningTime > runReset) {
            runClock.restart();
        }
        
        if(playerSlideing) {
            Time elapsedTime = slideClock.getElapsedTime();
            Time slideTime = seconds(0.5);
            if(elapsedTime < slideTime) {
                player.setTexture(playerSlidingTexture);
                player.setScale(1, 1);
                player.setPosition(playerRootX, 490);
                playerCollitionBox.setRotation(90);
            }
            else {
                playerSlideing = false;
                player.setPosition(playerRootX, playerRootY);
            }
        }
        
        if(playerJumping) {
            Time elapsedTime = jumpClock.getElapsedTime();
            Time jumpSecounds = seconds(1);
            if(elapsedTime < jumpSecounds) {
                player.move(0, -2);
                playerCollitionBox.move(0, -2);
            }
            else {
                player.move(0, 2);
                playerCollitionBox.move(0, 2);
            }
            if(player.getPosition().y == playerRootY) {
                playerJumping = false;
            }
        }
        
        if(!gameGoing) {
            player.setTexture(playerSlidingTexture);
            player.setScale(1, 1);
            player.setPosition(playerRootX, 490);
        }
        //coin actions
        Time coinTime = coinClock.getElapsedTime();
        Time coinReset = seconds(0.3);
        Time coinReset2 = seconds(0.15);
        if(!collected) {
            if(coinTime < coinReset2) {
                coin.setTexture(coinSideTexture);
            }
            else {
                coin.setTexture(coinFaceTexture);
            }
            
            if(coinTime > coinReset) {
                coinClock.restart();
            }
        }
        int coinMovmentSpeed = 1 * gameSpeed;
        if(gameGoing == true) {
            coin.move(-coinMovmentSpeed, 0);
        }
        coinCollitionBox.move(-coinMovmentSpeed, 0);
        if(coin.getPosition().x < -20 ) {
            collected = false;
            coin.setPosition(800, cointRootPosY);
        }
        if(coinCollitionBox.getPosition().x < -20) {
            coinCollitionBox.setPosition(800, cointRootPosY);
        }
        if(coinCollitionBox.getGlobalBounds().intersects(playerCollitionBox.getGlobalBounds())) {
            collected = true;
            playerCoins += 1;
        }
        //fire actions
        Time fireTime = fireClock.getElapsedTime();
        Time fireReset = seconds(0.3);
        Time fireReset2 = seconds(0.15);
        
        if(fireTime < fireReset) {
            cout<<"fire1"<<endl;
            fire1.setTexture(fireTexture1);
        }
        else if(fireTime < fireReset2) {
            cout<<"fire2"<<endl;
            fire1.setTexture(fireTexture3);
        }
        else {
            fire1.setTexture(fireTexture1);
        }
        
        if(fireTime > fireReset) {
            fireClock.restart();
        }
        int fireSpeed = 1 * gameSpeed;
        if(gameGoing == true) {
            fire1.move(-fireSpeed, 0);
            fire2.move(-fireSpeed, 0);
            fire3.move(-fireSpeed, 0);
        }
        if(fire1.getPosition().x < -40) {
            fire1.setPosition(800, 470);
        }
        if(fire2.getPosition().x < -40) {
            fire2.setPosition(800, 470);
        }
        if(fire2.getPosition().x < -40) {
            fire2.setPosition(800, 470);
        }
        //fire player collition
        if(playerCollitionBox.getGlobalBounds().intersects(fire1.getGlobalBounds())) {
            gameGoing = false;
        }
        else if(playerCollitionBox.getGlobalBounds().intersects(fire2.getGlobalBounds())) {
            gameGoing = false;
        }
        else if(playerCollitionBox.getGlobalBounds().intersects(fire2.getGlobalBounds())) {
            gameGoing = false;
        }
        //laser actions
        int laserSpeed = 1 * gameSpeed;
        if(gameGoing == true) {
            laser1.move(-laserSpeed, 0);
            laser2.move(-laserSpeed, 0);
            if(laser1.getPosition().x < -40) {
                laser1.setPosition(800, 490);
            }
            if(laser2.getPosition().x < -40) {
                laser2.setPosition(800, 490);
            }
        }
        //floor actions
        if(gameGoing == true) {
            floor.move(-1, 0);
            floor2.move(-1, 0);
            floor3.move(-1, 0);
        }
        
        if(floor.getPosition().x + 475 < 0) {
            floor.setPosition(0, 540);
        }
        if(floor2.getPosition().x + 475 < 475) {
            //cout<<"floor 2"<<endl;
            floor2.setPosition(0, 540);
        }
        if(floor3.getPosition().x + 475 < 950) {
            //cout<<"floor 3"<<endl;
            floor3.setPosition(0, 540);
        }
        //increment gameSpeed
        if(gameGoing == true) {
            Time totaltimer = totalTime.getElapsedTime();
            Time speedUpTime = seconds(30);
            cout<<totaltimer.asSeconds()<<endl;
            cout<<gameSpeed<<endl;
            if(totaltimer == speedUpTime) {
                cout<<"speed up"<<endl;
                gameSpeed += 0.5;
            }
        }
        //window loading
        
        window.clear(Color::White);
        window.draw(coinCollitionBox);
        window.draw(background);
        window.draw(playerCollitionBox);
        window.draw(floor);
        window.draw(floor3);
        window.draw(floor2);
        if(fireIsReset1 == true) {
            window.draw(fire1);
        }
        if(fireIsReset2 == true) {
            window.draw(fire2);
        }
        if(fireIsReset3 == true) {
            window.draw(fire3);
        }
        if(!collected) {
            window.draw(coin);
        }
        window.draw(coinNumberText);
        window.draw(player);
        window.draw(laser1);
        window.draw(laser2);
        window.draw(laserCollition1);
        window.draw(laserCollition2);
        window.display();
    }

    return EXIT_SUCCESS;
}

int main() {
    if(gameGoing) {
        gamePlay();
    }
    else  if(menu){
        menuScene();
    }
}
