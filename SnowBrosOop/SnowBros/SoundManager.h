//#pragma once
//#include <SFML/Audio.hpp>
//#include <string>
//
//class SoundManager
//{
//private:
//    sf::Music music;
//
//public:
//    void play(const std::string& filename, bool loop = true)
//    {
//        music.stop();
//        if (music.openFromFile(filename))
//        {
//            music.setLoop(loop);
//            music.setVolume(60.f);
//            music.play();
//        }
//    }
//
//    void stop() { music.stop(); }
//    void pause() { music.pause(); }
//    void resume() { music.play(); }
//    void setVolume(float v) { music.setVolume(v); }
//};
//
//#pragma once
//#include <SFML/Audio.hpp>
//#include <string>
//
//class SoundManager
//{
//private:
//    sf::Music music;
//
//public:
//    void play(const std::string& filename, bool loop = true)
//    {
//        music.stop();
//        if (music.openFromFile(filename))
//        {
//            music.setLoop(loop);
//            music.setVolume(60.f);
//            music.play();
//        }
//    }
//
//    void stop() { music.stop(); }
//    void pause() { music.pause(); }
//    void resume() { music.play(); }
//    void setVolume(float v) { music.setVolume(v); }
//};
//
//// Global instance — accessible from any .cpp that includes this header
//inline SoundManager& gSound()
//{
//    static SoundManager instance;
//    return instance;
//}

#pragma once
#include <SFML/Audio.hpp>
#include <string>

class SoundManager
{
private:
    sf::Music music;

public:
    void play(const std::string& filename, bool loop = true)
    {
        music.stop();
        if (music.openFromFile(filename))
        {
            music.setLoop(loop);
            music.setVolume(60.f);
            music.play();
        }
    }

    void stop() { music.stop(); }
    void pause() { music.pause(); }
    void resume() { music.play(); }
    void setVolume(float v) { music.setVolume(v); }
};

inline SoundManager& gSound()
{
    static SoundManager instance;
    return instance;
}