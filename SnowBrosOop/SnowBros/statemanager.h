#pragma once

#include <SFML/Graphics.hpp>
#include "inputmanager.h"

class StateManager;

enum class GameMode {
    SinglePlayer,
    TwoPlayer
};

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
    GameMode mode;
public:
    StateManager();
    ~StateManager();

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
};