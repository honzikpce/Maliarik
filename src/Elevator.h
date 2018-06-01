//
// Created by Honzik on 23.03.17.
//

#ifndef MALIARIK_ELEVATOR_H
#define MALIARIK_ELEVATOR_H

#include <JN/GameObject.h>
#include <Box2D/Box2D.h>

enum class ElevatorState {
    goingUp,
    goingDown,
    waitingUp,
    waitingDown
};

class Elevator : public JN::GameObject{


public:
    Elevator(b2World * world, glm::vec2 sourcePosition, glm::vec2 destinationPosition, float speed, float delay);

protected:
    void doOnUpdate(JN::ControlManager &controlManager, JN::Camera2D &camera) override;
    b2Body * m_body;
    b2Fixture * m_fixture;
    glm::vec2 m_destination;
    glm::vec2 m_source;

    const float HEIGHT = 0.5f;
    const float WIDTH = 2.0f;
    glm::vec2 m_direction;
    ElevatorState m_state = ElevatorState::goingUp;
    float m_delay;
    float m_delayCounter = 0.0f;
    float m_maxSpeed;
    const float ACCELERATION_STEP = 0.02f;
};


#endif //MALIARIK_ELEVATOR_H
