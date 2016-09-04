#include "GameScreen.h"
#include "Tilemap.h"

GameScreen::GameScreen() {
    map = new Tilemap("assets/testemenor.tmx");
}

GameScreen::~GameScreen() {

}

void GameScreen::Update(float delta) {

}

void GameScreen::Draw() {
    map->Draw();
}