#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager() {
    if (!b_baby.loadFromFile("resources/sujet_micro-projet_CSC4526_2023_2024.wav")) {
        std::cout << "Failed to load baby" << std::endl;
    }
    baby.setBuffer(b_baby);
    if (!b_gunshot.loadFromFile("resources/gunshot.wav")) {
        std::cout << "Failed to load gunshot" << std::endl;
    }
    gunshot.setBuffer(b_gunshot);
    if (!b_explosion.loadFromFile("resources/explosion.wav")) {
        std::cout << "Failed to load explosion" << std::endl;
    }
    explosion.setBuffer(b_explosion);
}

void SoundManager::playBaby() {
    baby.play();
}

void SoundManager::playGunshot() {
    gunshot.play();
}

void SoundManager::playExplosion() {
    explosion.play();
}