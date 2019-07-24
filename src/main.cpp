#include <QtWidgets/QApplication>
#include <QtCore/QVector>

#include "Game.h"
#include "GameEntry.h"
#include "HighScores.h"

#include <fstream>
#include <iostream>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    Game flappyBird;
    
    flappyBird.run(app);
    
    
    HighScores highscore("HighScores.txt", 10u);
    highscore.loadHighScores();
    
    highscore.addScore(GameEntry("Julia", 5));
    highscore.addScore(GameEntry("Paul", 8));
    highscore.addScore(GameEntry("titus", 11));
    highscore.addScore(GameEntry("Sylvester", 12));
    
    highscore.saveHighScores();

    
    return 0;
}
