#include "State.hpp"

Context::Context(std::unique_ptr<State> initialState) : currentState(std::move(initialState)) {}

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
