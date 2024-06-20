#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
public:
    bool loadSound(const std::string& filename);

    void playSound();

private:
    sf::SoundBuffer buffer;
    sf::Sound       sound;
};