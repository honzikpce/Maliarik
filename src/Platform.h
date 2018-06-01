//
// Created by Honzik on 22.03.17.
//

#ifndef MALIARIK_PLATFORM_H
#define MALIARIK_PLATFORM_H

#include <JN/GameObject.h>
#include <Box2D/Box2D.h>

class Platform : public JN::GameObject {

public:
    Platform(b2World *world, glm::vec2 position, float width, int type);
    b2Body * getBody() { return m_body; }

protected:
    void doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) override;
    b2Body * m_body;
    b2Fixture * m_fixture;
    const float PLATFORM_THICKNESS = 0.5f;
};


#endif //MALIARIK_PLATFORM_H
