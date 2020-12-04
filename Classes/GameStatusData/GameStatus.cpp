//
// Created by ntaki on 2020/11/21.
//

#include "GameStatus.h"

GameStatus *GameStatus::gameStatus = nullptr;

GameStatus::GameStatus()
{
    Charactors = new std::list<Character*>();
    for(int i = 0; i < 4; i++)
    {
        Character *character = new Character();
        Charactors->push_back(character);
    }
}

GameStatus::~GameStatus()
{
    for(Character *character = Charactors->front(); Charactors->empty() == true; character = Charactors->front())
    {
        delete character;
        Charactors->pop_front();
    }
    delete Charactors;
}

GameStatus * GameStatus::GetGameData()
{
    if(gameStatus == nullptr)
    {
        gameStatus = new GameStatus();
    }
    return gameStatus;
}

void GameStatus::Destroy()
{
    delete gameStatus;
}
