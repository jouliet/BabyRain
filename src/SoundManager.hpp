#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
public:
    SoundManager() = default;

    void loadSound(const std::string& name, const std::string& filename);

    void playSound(const std::string& name);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> sounds;
};