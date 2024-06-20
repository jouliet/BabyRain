#include "SoundManager.hpp"

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (soundBuffer->loadFromFile(filename)) {
        sounds[name] = std::move(soundBuffer);
    }
}

void SoundManager::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        sf::Sound sound;
        sound.setBuffer(*it->second);
        sound.play();
    }
}