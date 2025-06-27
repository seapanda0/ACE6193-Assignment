#include "State.hpp"

Context::Context(std::unique_ptr<State> initialState, CardManager *a_cardManager) : currentState(std::move(initialState)), cardManager(a_cardManager) {}

void Context::setState(std::unique_ptr<State> nextState)
{
    currentState = std::move(nextState);
    request();
}

void Context::request()
{
    if (currentState)
    {
        currentState->handle(this);
    }
}

void Context::exit()
{
    currentState.reset();
}

void Context::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}