#ifndef STATE_HPP
#define STATE_HPP

#include <string>

class Context;

class State
{
private:
    Context *appContext;

public:
    virtual ~State() = default;
    virtual void handle(Context *context) = 0;
    virtual std::string getName() const = 0;
    virtual void onEnter(Context *context) {}
    virtual void onExit(Context *context) {}
};
#endif
