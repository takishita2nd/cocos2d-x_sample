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
        char* quest2 = "クエスト2";
        char* quest3 = "クエスト3";
        char* quest4 = "クエスト4";
        char* quest5 = "クエスト5";
        char* quest6 = "クエスト6";
        char* quest7 = "クエスト7";
        char* quest8 = "クエスト8";
        char* quest9 = "クエスト9";
        char* quest10 = "クエスト10";
        questList->push_back(quest1);
        questList->push_back(quest2);
        questList->push_back(quest3);
        questList->push_back(quest4);
        questList->push_back(quest5);
        questList->push_back(quest6);
        questList->push_back(quest7);
        questList->push_back(quest8);
        questList->push_back(quest9);
        questList->push_back(quest10);
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