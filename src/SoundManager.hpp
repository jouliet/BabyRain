#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
public:
    SoundManager();

    void                playBaby();
    void                playGunshot();
    void                playExplosion();

private:
    sf::SoundBuffer     b_baby;
    sf::Sound           baby;

    sf::SoundBuffer     b_gunshot;
    sf::Sound           gunshot;

    sf::SoundBuffer     b_explosion;
    sf::Sound           explosion;
};