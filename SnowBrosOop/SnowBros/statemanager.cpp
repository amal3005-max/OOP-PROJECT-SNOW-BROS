
#include "statemanager.h"
#include "game.h"

StateManager::StateManager()
{
    currentState = nullptr;
    previousState = nullptr;
    running = true;

}

StateManager::~StateManager()
{
    delete currentState;
    delete previousState;
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

void StateManager::pauseState(State* pauseState)
{
    if (currentState)
        previousState = currentState;

    currentState = pauseState;
}
void StateManager::resumeState()
{
    if (currentState)
        delete currentState;

    currentState = previousState; 
    previousState = nullptr;
}

void StateManager::quit()
{
    running = false;
}

bool StateManager::isRunning() const
{
    return running;
}