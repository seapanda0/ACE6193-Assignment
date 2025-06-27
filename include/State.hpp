#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <iostream>
#include <memory>
#include "cardManager.hpp"

class State;
class Context;

class State
{

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
    CardManager * cardManager;
    // Context(std::unique_ptr<State> initialState);
    Context(std::unique_ptr<State> initialState, CardManager * a_cardManager);
    void setState(std::unique_ptr<State> nextState);
    void request();
    void exit();
    void clearScreen();
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

/*StudySession State start*/
class StudySessionState : public State {

public:
    void handle (Context * context) override;
};
/*StudySession State end*/

/*Add Card State start*/
class AddCardState : public State {

public:
    void handle (Context * context) override;
};
/*Add Card State end*/
/*Delete Card State start*/
class DeleteCardState : public State {

public:
    void handle (Context * context) override;
};
/*Delete Card State end*/


#endif
