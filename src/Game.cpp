#include "Pipe.h"
#include "Game.h"
#include "Button.h"

#include <cstdlib>
#include <ctime>

#include <QtGui/QFont>
#include <QtCore/QRect>
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsTextItem>

//Spacing between the upper and the lower pipe to be 70 pixels wide
const int PIPE_DISTANCE = 360;

Game::Game(): m_player{NULL}, m_state{GAME_STATE::playing}, m_score{0}
{
    m_gameScene = new GameScene;
    m_gameScene -> show();

    srand(std::time(NULL));
}


Game::~Game()
{
    delete m_player;
    delete m_gameScene;
}

void Game::run(QApplication& gameApplication)
{
    displayMainMenu();
    gameApplication.exec();
}


void Game::start()
{
    m_gameScene -> clear(); 
    m_player = new Flappy;
    
    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnPipes()));
    
    if(m_state == GAME_STATE::playing)
    {
        timer -> start(3000);
    }
    else
    {
        timer -> stop();
    }

    m_gameScene -> addItem(m_player);
    m_gameScene -> setFocusItem(m_player);

    
    connect(m_player, SIGNAL(outOfScene()), this, SLOT(gameOver()));
    connect(m_player, SIGNAL(inCollision()), this, SLOT(gameOver()));
    connect(m_player, SIGNAL(scoreIncreased()), this, SLOT(increaseScore()));
    
    setPlaying();
    qDebug() << m_score;
}


void Game::spawnPipes()
{
    if(m_state == GAME_STATE::playing)
    {
        Pipe* downPipe = new Pipe;         
        Pipe* upPipe = new Pipe;
        
        upPipe -> rotatePixmap();

        //Set the height of the pipe to be between 300 and 100 above ground
        int random_height = rand() % 201 + 100;
        
        
        downPipe -> setPos(downPipe -> x(), random_height);

        //Create the top pipe at a height difference of PIPE_DISTANCE FROM the bottom pipe
        upPipe -> setPos(downPipe -> x(), downPipe -> y() - PIPE_DISTANCE);
        
        //Add the top and bottom pipes to the game scene
        m_gameScene -> addItem(downPipe);
        m_gameScene -> addItem(upPipe);
    }
}


void Game::displayMainMenu()
{
    //Create the title text
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("FlappyBird"));
    QFont titleFont("Californian FB", 50);
    title -> setFont(titleFont);
    
    int txPos = m_gameScene -> width() / 2 - title -> boundingRect().width() / 2;
    int tyPos = 150;
    title -> setPos(txPos, tyPos);
    m_gameScene -> addItem(title);
    
    //Create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = m_gameScene -> width() / 2 - playButton -> boundingRect().width() / 2;
    int byPos = 275;
    playButton -> setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    m_gameScene -> addItem(playButton);
    
    //Create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = m_gameScene -> width() / 2 - quitButton -> boundingRect().width() / 2;
    int qyPos = 350;
    quitButton -> setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), m_gameScene -> view(), SLOT(close()));
    m_gameScene -> addItem(quitButton);
    
}


void Game::displayGameOver()
{
    m_gameScene -> clear();
    
    m_player = new Flappy;
    
    //Create the title text
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("GAMEOVER"));
    QFont titleFont("Courier New", 50);
    title -> setFont(titleFont);
    
    int txPos = m_gameScene -> width() / 2 - title -> boundingRect().width() / 2;
    int tyPos = 150;
    title -> setPos(txPos, tyPos);
    m_gameScene -> addItem(title);
    
    //Create the play button
    Button* playButton = new Button(QString("Play Again"));
    int bxPos = m_gameScene -> width() / 2 - playButton -> boundingRect().width() / 2;
    int byPos = 275;
    playButton -> setPos(bxPos, byPos);
    
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    
    
    m_gameScene -> addItem(playButton);
    
    //Create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = m_gameScene -> width() / 2 - quitButton -> boundingRect().width() / 2;
    int qyPos = 350;
    quitButton -> setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), m_gameScene -> view(), SLOT(close()));
    m_gameScene -> addItem(quitButton);
    
}


void Game::gameOver()
{
    m_state = GAME_STATE::over;
    m_player -> setEnabled(false);
    
    qDebug() << m_score;

    displayGameOver();
}


void Game::setPlaying()
{
    if(m_state != GAME_STATE::playing)
    {
        m_state = GAME_STATE::playing;
    }
}


void Game::increaseScore()
{
    m_score += 0.5;
}

