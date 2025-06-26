#include "State.hpp"

/*Context Start*/
// void Context::run() {

// }
/*Context End*/


/*INITIAL State Start*/
// std::unique_ptr<State> nextState;

void InitialState::handle(Context *context)
{
    std::cout << "Welcome to Simple Flashcard Program\n";

    context -> setState(std::make_unique<IdleState>());
}
/*INITIAL State End*/

/* IDLE State Start*/
void IdleState::handle(Context *context)
{
    std::cout << "Main Menu:\n";

}
/* IDLE State End*/
