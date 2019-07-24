#ifndef GAME_H
#define GAME_H

#include <QtWidgets/QApplication>
#include <QtGui/QColor>

#include "GameScene.h"
#include "FlappyBird.h"
#include "Menu.h"

enum class GAME_STATE{
    playing,
    over
};

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
   ~Game();
    void run(QApplication& gameApplication);
    void displayMainMenu();
    
public slots:
    void start();
    void spawnPipes();
    void displayGameOver();
    void gameOver();
    void setPlaying();
    void increaseScore();
    
signals:
    void sceneCleared();

private:
    Flappy* m_player;
    GameScene* m_gameScene;
    GAME_STATE m_state;
    int m_score;
    Menu* m_mainMenu;
    
};

#endif //GAME_H
