//
// Created by ntaki on 2021/01/10.
//

#include "Mock.h"

std::list<char*> *questList = nullptr;

std::list<char*>* getQuestList()
{
    if(questList == nullptr)
    {
        questList = new std::list<char*>();
        char* quest1 = "クエスト1";
        questList->push_back(quest1);
    }
    return questList;
}

void deleteMock()
{
    if(questList != nullptr)
    {
        delete questList;
    }
}