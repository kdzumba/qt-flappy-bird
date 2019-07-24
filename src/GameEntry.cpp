#include "GameEntry.h"

GameEntry::GameEntry(const std::string& name, int score):
m_name{name}, m_score{score} {                     }


std::string GameEntry::name() const
{
    return m_name;
}


int GameEntry::score() const
{
    return m_score;
}