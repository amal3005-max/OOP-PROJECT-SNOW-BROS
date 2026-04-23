
#include "statemanager.h"
//#include "state.h"
#include "game.h"

StateManager::StateManager()
{
    currentState = nullptr;
}

StateManager::~StateManager()
{
    delete currentState;
}

void StateManager::changeState(State* newState)
{
    delete currentState;
    currentState = newState;
}

void StateManager::handleInput(sf::Event& event)
{
    if (currentState != nullptr)
    {
        currentState->handleInput(event);
    }
}

void StateManager::update(float deltaTime)
{
    if (currentState != nullptr)
    {
        currentState->update(deltaTime);
    }
}

void StateManager::render(sf::RenderWindow& window)
{
    if (currentState != nullptr)
    {
        currentState->render(window);
    }
}