//
// Created by Honzik on 22.03.17.
//

#ifndef MALIARIK_LEVELSCREEN_H
#define MALIARIK_LEVELSCREEN_H

#include <JN/IGameScreen.hpp>
#include <JN/Camera2D.hpp>
#include <JN/ControlManager.hpp>
#include "Player.h"
#include "Platform.h"
#include "Elevator.h"

#include <Box2D/Box2D.h>

class LevelScreen : public JN::IGameScreen {
public:
    int getNextScreenIndex() const override;

    int getPrevScreenIndex() const override;

    void build() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update() override;

    void draw() override;

protected:
    JN::Camera2D m_camera;
    JN::ControlManager *m_controlManager;
    Player * m_player;
    JN::SpriteBatch m_spriteBatch;
    JN::GLSLProgram m_textureProgram;

    b2World * m_world = nullptr;
    Platform * m_platforms[7];
    Elevator * m_elevator1 = nullptr;
    Elevator * m_elevator2 = nullptr;

};


#endif //MALIARIK_LEVELSCREEN_H
