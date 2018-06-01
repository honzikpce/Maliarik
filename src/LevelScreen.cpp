//
// Created by Honzik on 22.03.17.
//

#include "LevelScreen.h"
#include "ConstsAndTypes.h"
#include <JN/IMainGame.hpp>

int LevelScreen::getNextScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

int LevelScreen::getPrevScreenIndex() const {
    return SCREEN_MAIN_MENU;
}

void LevelScreen::build() {
    // init camera
    m_camera.init(SCREEN_W, SCREEN_H);
    m_camera.setScale(25.0f);
    m_camera.setPosition(glm::vec2(SCREEN_W /25.0 / 2.0f, SCREEN_H / 25.0f / 2.0f));

    // get control manager from IMainGame
    m_controlManager = _mainGame->getControlManager();

    // init rendering
    m_spriteBatch.init();
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.compileShaders("../shaders/simple.vert","../shaders/simple.frag");

    // init physics
    m_world = new b2World(b2Vec2(0.0f, -12.8f));

    // init game
    m_player = new Player(m_world, glm::vec2(5.0f, 2.0f));
    m_platforms[0] = new Platform(m_world, glm::vec2(0.0f,2.0f), 25.0f, 0);
    m_platforms[1] = new Platform(m_world, glm::vec2(27.0f, 2.0f), 20.0f, 0);
    m_platforms[2] = new Platform(m_world, glm::vec2(0.0f, 12.0f), 5.0f, 0);
    m_platforms[3] = new Platform(m_world, glm::vec2(7.0f, 12.0f), 18.0f, 0);
    m_platforms[4] = new Platform(m_world, glm::vec2(0.0f, 20.0f), 5.0f, 0);
    m_platforms[5] = new Platform(m_world, glm::vec2(7.0f, 20.0f), 25.0f, 0);
    m_platforms[6] = new Platform(m_world, glm::vec2(27.0f, 12.0f), 15.0f, 0);
    m_elevator1 = new Elevator(m_world, glm::vec2(5.0f, 12.0f),glm::vec2(5.0f, 20.0f), 2.0f, 200.0f);
    m_elevator2 = new Elevator(m_world, glm::vec2(25.0f, 2.0f),glm::vec2(25.0f, 12.0f), 3.0f, 100.0f);
}

void LevelScreen::destroy() {

}

void LevelScreen::onEntry() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); ///< set background color
}

void LevelScreen::onExit() {

}

void LevelScreen::update() {
    SDL_Event evnt;

    m_world->Step(1/60.0f, 8, 3);

    while (SDL_PollEvent(&evnt))
        _mainGame->onSDLEvent(evnt);

    m_camera.update();

    m_player->update(*m_controlManager, m_camera);
    m_elevator1->update(*m_controlManager, m_camera);
    m_elevator2->update(*m_controlManager, m_camera);

}

void LevelScreen::draw() {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///< clear screen to bg color


    m_textureProgram.use();

    // activate first texture slot
    glActiveTexture(GL_TEXTURE0);

    // upload uniforms to shaders
    GLint camLocation = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(camLocation, 1, GL_FALSE, &m_camera.getCameraMatrix()[0][0]);

    GLint textureLocation = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    m_spriteBatch.begin();

    m_player->draw(m_spriteBatch);
    m_platforms[0]->draw(m_spriteBatch);
    m_platforms[1]->draw(m_spriteBatch);
    m_platforms[2]->draw(m_spriteBatch);
    m_platforms[3]->draw(m_spriteBatch);
    m_platforms[4]->draw(m_spriteBatch);
    m_platforms[5]->draw(m_spriteBatch);
    m_platforms[6]->draw(m_spriteBatch);
    m_elevator1->draw(m_spriteBatch);
    m_elevator2->draw(m_spriteBatch);

    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unUse();
}
