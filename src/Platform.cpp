//
// Created by Honzik on 22.03.17.
//

#include "Platform.h"

void Platform::doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) {

}

Platform::Platform(b2World *world, glm::vec2 position, float width, int type) {
    // create body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x + width / 2.0f, position.y + PLATFORM_THICKNESS / 2.0f);
    m_body = world->CreateBody(&bodyDef);
    m_body->SetType(b2BodyType::b2_staticBody);
    //create shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2.0f, PLATFORM_THICKNESS / 2.0f);
    //create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    m_body->CreateFixture(&fixtureDef);

    m_dims = glm::vec2(width, PLATFORM_THICKNESS);
    m_position = position;

    m_texture = JN::ResourceManager::getTexture("../textures/platform.png").id;
}
