#ifndef SCREEN_MANAGER
#define SCREEN_MANAGER
#pragma once

#include <string>
#include <map>
#include<iostream>


class GameScreen;
class ScreenManager {
public:
    static void addScreen(std::string name, GameScreen* screen);

    static void Update(float delta);
    static void Draw();

    static GameScreen* currentScreen;

private:
    ScreenManager();
    ~ScreenManager();

    static std::map<std::string, GameScreen*> screens;
};

#endif