//
// Created by Honzik on 23.03.17.
//

#include "Elevator.h"

void Elevator::doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) {

    switch (m_state) {
        case ElevatorState::goingUp :
            if (glm::length(m_destination - glm::vec2(m_position)) < 0.1f) {
                m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
                m_speed = 0.0f;
                m_state = ElevatorState::waitingUp; break;
            }

            if (m_speed < m_maxSpeed) m_speed += ACCELERATION_STEP;
            m_body->SetLinearVelocity(b2Vec2(m_direction.x * m_speed, m_direction.y * m_speed));
            break;
        case ElevatorState::goingDown :
            if (glm::length(glm::vec2(m_position) - m_source) < 0.1f) {
                m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
                m_speed = 0.0f;
                m_state = ElevatorState::waitingDown; break;
            }

            if (m_speed < m_maxSpeed) m_speed += ACCELERATION_STEP;
            m_body->SetLinearVelocity(b2Vec2(-m_direction.x * m_speed, -m_direction.y * m_speed));
            break;
        case ElevatorState::waitingUp :
            m_delayCounter++;
            if (m_delayCounter >= m_delay) {
                m_delayCounter = 0.0f;
                m_state = ElevatorState::goingDown;
            }
            break;
        case ElevatorState::waitingDown :
            m_delayCounter++;
            if (m_delayCounter >= m_delay) {
                m_delayCounter = 0.0f;
                m_state = ElevatorState::goingUp;
            }
            break;
        }


    // update gameObject position from b2 body
    m_position = glm::vec2(m_body->GetPosition().x - m_dims.x /2.0f, m_body->GetPosition().y - m_dims.y /2.0f);

}

Elevator::Elevator(b2World *world, glm::vec2 sourcePosition, glm::vec2 destinationPosition, float speed, float delay) {

    m_source = sourcePosition;
    m_destination = destinationPosition;
    m_maxSpeed = speed;
    m_dims = glm::vec2(WIDTH, HEIGHT);
    m_position = sourcePosition;
    m_direction = glm::normalize(destinationPosition - sourcePosition);
    m_delay = delay;

    // create body
    b2BodyDef bodyDef;
    bodyDef.position.Set(sourcePosition.x + WIDTH / 2.0f, sourcePosition.y + HEIGHT / 2.0f);
    m_body = world->CreateBody(&bodyDef);
    m_body->SetType(b2BodyType::b2_kinematicBody);
    //create shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(WIDTH / 2.0f, HEIGHT / 2.0f);
    //create fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    m_body->CreateFixture(&fixtureDef);



    //m_texture = JN::ResourceManager::getTexture("../textures/platform.png").id;
}
