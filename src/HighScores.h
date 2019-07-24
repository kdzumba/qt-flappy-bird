#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "GameEntry.h"

#include <string>
#include <vector>
#include <fstream>

class HighScores
{
public:
    HighScores(std::string highScoresFilename, int maxEntries = 5u);
   ~HighScores();
   
   void loadHighScores();
   void saveHighScores();
   void addScore(const GameEntry& entry);
   std::vector<GameEntry> highScores() const;
   
private:
   std::ifstream m_inputScoresFile;
   std::ofstream m_outputScoresFile;
   int m_maxEntries;
   std::vector<GameEntry> m_gameEntries;
};

#endif // HIGHSCORES_H
