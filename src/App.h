//
// Created by Honzik on 26.12.16.
//

#ifndef MALIARIK_APP_H
#define MALIARIK_APP_H

#include <JN/IMainGame.hpp>
#include <JN/IGameScreen.hpp>
#include "MainMenu.h"
#include "LevelScreen.h"

class App: public JN::IMainGame {

public:

private:
    void onInit() override;

    void addScreens() override;

    void onExit() override;

    MainMenu m_mainMenuScreen;
    LevelScreen m_levelScreen;


};


#endif //MALIARIK_APP_H
