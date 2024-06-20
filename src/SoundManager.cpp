#include "SoundManager.hpp"
#include <iostream>

bool SoundManager::loadSound(const std::string& filename) {
    if (!buffer.loadFromFile(filename)) {
        return false;
    }
    sound.setBuffer(buffer);
    return true;
}

void SoundManager::playSound() {
    sound.play();
}