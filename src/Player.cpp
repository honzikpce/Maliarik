//
// Created by Honzik on 22.03.17.
//

#include "Player.h"

void Player::doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) {

    if (controlManager.isKeyDown(SDLK_LEFT))  {
        m_body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f), true);
    }
    if (controlManager.isKeyDown(SDLK_RIGHT))  {
        m_body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f), true);
    }

    if (controlManager.isKeyPressed(SDLK_UP))  {
        m_body->ApplyForceToCenter(b2Vec2(0.0f, 1000.0f), true);
    }

    if (fabs(m_body->GetLinearVelocity().x) > 5.0f) {
        m_body->SetLinearVelocity(
                    b2Vec2((m_body->GetLinearVelocity().x > 0.0f) ? 5.0f : -5.0f,
                           m_body->GetLinearVelocity().y));
    }

    m_position = glm::vec2(m_body->GetPosition().x - m_dims.x /2.0f, m_body->GetPosition().y - m_dims.y /2.0f);

    /*

    if (controlManager.isKeyDown(SDLK_LEFT))  {
        m_speed -= ACCELERATION_STEP;
        if (m_speed < -MAX_SPEED) m_speed = -MAX_SPEED;
    }
    else if (m_speed < 0.0f) {
        m_speed += ACCELERATION_STEP;
        if (fabs(m_speed) < ACCELERATION_STEP) m_speed = 0.0f;
    }
    if (controlManager.isKeyDown(SDLK_RIGHT)) {
        m_speed += ACCELERATION_STEP;
        if (m_speed > MAX_SPEED) m_speed = MAX_SPEED;
    }
    else if (m_speed > 0.0f) {
        m_speed -= ACCELERATION_STEP;
        if (fabs(m_speed) < ACCELERATION_STEP) m_speed = 0.0f;
    }

    m_position.x += m_speed;

    if (controlManager.isKeyPressed(SDLK_LEFT)) m_invertedTexture = false;
    if (controlManager.isKeyPressed(SDLK_RIGHT)) m_invertedTexture = true;
     */
}

Player::Player(b2World *world, glm::vec2 position) {

    // set object attributes
    m_dims = glm::vec2(1.5f, 2.0f);
    m_position = position;
    m_speed = 0.0f;

    // create body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x + m_dims.x / 2.0f, position.y + m_dims.y / 2.0f);
    m_body = world->CreateBody(&bodyDef);
    m_body->SetType(b2BodyType::b2_dynamicBody);
    m_body->SetFixedRotation(true);
    //create shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(m_dims.x / 2.0f, m_dims.y / 2.0f);
    //create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_fixture = m_body->CreateFixture(&fixtureDef);



    //m_texture = JN::ResourceManager::getTexture("../textures/bug.png").id;

}
