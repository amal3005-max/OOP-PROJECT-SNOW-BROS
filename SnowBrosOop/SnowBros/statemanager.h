#pragma once

#include <SFML/Graphics.hpp>
#include "inputmanager.h"
#include "SoundManager.h"        // ← ADD


class StateManager;

enum class GameMode { SinglePlayer, TwoPlayer };

class State
{
protected:
    StateManager& manager;

public:
    State(StateManager& manager) : manager(manager) {}
    virtual ~State() {}

    virtual void handleInput(sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class StateManager
{
private:
    State* currentState;
    State* previousState;
    GameMode mode;
    bool running;
    SoundManager* soundManager = nullptr;   // ← ADD

public:
    StateManager();
    ~StateManager();

    void quit();
    bool isRunning() const;

    void pauseState(State* pauseState);
    void resumeState();

    void changeState(State* newState);

    void handleInput(sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void setMode(GameMode m)
    {
        mode = m;
    }
    GameMode getMode()
    {
        return mode;
    }

    void setSoundManager(SoundManager* sm) { soundManager = sm; }  // ← ADD
    SoundManager* getSound() { return soundManager; }
};