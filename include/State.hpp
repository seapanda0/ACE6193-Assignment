#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <iostream>
#include <memory>

class State;
class Context;

class State
{
private:
    Context *appContext;

public:
    virtual ~State() = default;
    virtual void handle(Context *context) = 0;
    // virtual std::string getName() const = 0;
};

class Context
{
private:
    std::unique_ptr<State> currentState;

public:
    Context(std::unique_ptr<State> initialState);
    void setState(std::unique_ptr<State> nextState);
    void request();    
};

/* IDLE State Start */
class IdleState : public State {

public:
    void handle (Context * context) override;
};

/* IDLE State Start*/

/* INITIAL State Start */
class InitialState : public State {

public:
    void handle (Context * context) override;
};
/* INITIAL State End */

#endif
