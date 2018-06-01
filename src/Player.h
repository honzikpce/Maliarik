//
// Created by Honzik on 22.03.17.
//

#ifndef MALIARIK_PLAYER_H
#define MALIARIK_PLAYER_H

#include <JN/GameObject.h>
#include <Box2D/Box2D.h>

class Player : public JN::GameObject {
public:
    Player(b2World *world, glm::vec2 position);

protected:
    void doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) override;
    const float ACCELERATION_STEP = 0.1f;
    const float MAX_SPEED = 2.0f;
    b2Body *m_body = nullptr;
    b2Fixture *m_fixture = nullptr;
};


#endif //MALIARIK_PLAYER_H
