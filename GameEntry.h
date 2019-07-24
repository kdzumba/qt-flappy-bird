#ifndef GAMEENTRY_H
#define GAMEENTRY_H

#include <string>

class GameEntry
{
public:
    GameEntry(const std::string& name = "Knowledge", int score = 0);
    
    std::string name() const;
    int score() const;
    
private:
    std::string m_name;
    int m_score;
};

#endif // GAMEENTRY_H
