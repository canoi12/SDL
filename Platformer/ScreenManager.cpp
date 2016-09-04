#include "ScreenManager.h"
#include "GameScreen.h"

std::map<std::string, GameScreen*> ScreenManager::screens;

GameScreen* ScreenManager::currentScreen;

ScreenManager::ScreenManager() {}
ScreenManager::~ScreenManager() {}

void ScreenManager::addScreen(std::string name, GameScreen* screen) {
    screens.insert(std::pair<std::string, GameScreen*>(name, screen));

    currentScreen = screen;
}

void ScreenManager::Update(float delta) {
    if (currentScreen != NULL)
        currentScreen->Update(delta);
}

void ScreenManager::Draw() {
    if (currentScreen != NULL)
        currentScreen->Draw();
}