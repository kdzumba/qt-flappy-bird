#include "HighScores.h"

#include <fstream>
#include <iostream>
#include <algorithm>

HighScores::HighScores(std::string ScoresFile, int maxEntries):
m_inputScoresFile{ScoresFile}, m_maxEntries{maxEntries}
{
    if(!m_inputScoresFile.is_open())
    {
        std::cout << "Could not open file " << ScoresFile << std::endl;
        std::cout << "Terminating the program";
        std::exit(EXIT_FAILURE);
    }
    
    m_gameEntries.reserve(maxEntries);
}


HighScores::~HighScores()
{
    //close all files that are open when object is destroyed
    if(m_inputScoresFile.is_open())
    {
        m_inputScoresFile.close();
    }
}


void HighScores::loadHighScores()
{
    //name and score for creating and initialising game entries
    std::string name;
    int score;
    
    while(m_inputScoresFile.good())
    {
        m_inputScoresFile >> name >> score;
        m_gameEntries.push_back(GameEntry(name, score));
    }
    
    //TODO sort the vector after loading in the high scores
}


void HighScores::saveHighScores()
{
    std::ofstream savedScores("HighScores.txt");
    if(!savedScores.is_open())
    {
        std::cout << "Could not save score" << std::endl;
        std::cout << "Terminating program" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    for(auto i = 0u; i < m_gameEntries.size(); i++)
    {
        savedScores << m_gameEntries[i].name() << " " << m_gameEntries[i].score();
    }
}


void HighScores::addScore(const GameEntry& entry)
{
    if(m_gameEntries.size() < m_maxEntries)
    {
        m_gameEntries.push_back(entry);
    }
    else
    {
        for(auto& ent : m_gameEntries)
        {
            if(ent.score() < entry.score() && entry.name() != ent.name())
            {
                ent = entry;
                return;
            }
        }
    }
}


std::vector<GameEntry> HighScores::highScores() const
{
    return m_gameEntries;
}

