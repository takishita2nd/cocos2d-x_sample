//
// Created by ntaki on 2020/11/21.
//

#include "GameStatus.h"

GameStatus gameStatus;

void createGameData()
{
    gameStatus.Charactors = new std::list<Character*>();
    for(int i = 0; i < 4; i++)
    {
        Character* character = createCharactor();
        gameStatus.Charactors->push_back(character);
    }
}

void destroyDamadata()
{
    auto charactor = gameStatus.Charactors->begin();
    for(int i = 0; i < gameStatus.Charactors->size(); i++)
    {
        free(charactor.operator*());
        charactor++;
    }
    delete gameStatus.Charactors;
}
