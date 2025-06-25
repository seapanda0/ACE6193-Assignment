#include <iostream>
#include <memory>
#include <string>

// Forward declarations
class Context;
class StateA;
class StateB;
class StateC;

// Abstract State base class
class State {
public:
    virtual ~State() = default;
    virtual void handle(Context* context) = 0;
    virtual std::string getName() const = 0;
};

// Concrete State declarations (full definitions will come after Context)
class StateA : public State {
public:
    void handle(Context* context) override;
    std::string getName() const override { return "StateA"; }
};

class StateB : public State {
public:
    void handle(Context* context) override;
    std::string getName() const override { return "StateB"; }
};

class StateC : public State {
public:
    void handle(Context* context) override;
    std::string getName() const override { return "StateC"; }
};

// Context class that maintains current state
class Context {
private:
    std::unique_ptr<State> currentState;
    
public:
    Context(std::unique_ptr<State> initialState) 
        : currentState(std::move(initialState)) {}
    
    void setState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
        std::cout << "State changed to: " << currentState->getName() << std::endl;
    }
    
    void request() {
        if (currentState) {
            currentState->handle(this);
        }
    }
    
    std::string getCurrentStateName() const {
        return currentState ? currentState->getName() : "No State";
    }
};

// State implementations (after Context is fully defined)
void StateA::handle(Context* context) {
    std::cout << "StateA: Processing request and transitioning to StateB" << std::endl;
    context->setState(std::make_unique<StateB>());
}

void StateB::handle(Context* context) {
    std::cout << "StateB: Processing request and transitioning to StateC" << std::endl;
    context->setState(std::make_unique<StateC>());
}

void StateC::handle(Context* context) {
    std::cout << "StateC: Processing request and transitioning back to StateA" << std::endl;
    context->setState(std::make_unique<StateA>());
}

// Traffic Light FSM - Forward declarations
class TrafficLightContext;
class RedState;
class YellowState;
class GreenState;

class TrafficLightState {
public:
    virtual ~TrafficLightState() = default;
    virtual void nextState(TrafficLightContext* context) = 0;
    virtual std::string getColor() const = 0;
    virtual int getDuration() const = 0; // seconds
};

// Traffic Light State declarations
class RedState : public TrafficLightState {
public:
    void nextState(TrafficLightContext* context) override;
    std::string getColor() const override { return "RED"; }
    int getDuration() const override { return 30; }
};

class YellowState : public TrafficLightState {
public:
    void nextState(TrafficLightContext* context) override;
    std::string getColor() const override { return "YELLOW"; }
    int getDuration() const override { return 5; }
};

class GreenState : public TrafficLightState {
public:
    void nextState(TrafficLightContext* context) override;
    std::string getColor() const override { return "GREEN"; }
    int getDuration() const override { return 25; }
};

class TrafficLightContext {
private:
    std::unique_ptr<TrafficLightState> currentState;
    
public:
    TrafficLightContext(std::unique_ptr<TrafficLightState> initialState)
        : currentState(std::move(initialState)) {}
    
    void changeState(std::unique_ptr<TrafficLightState> newState) {
        currentState = std::move(newState);
    }
    
    void next() {
        std::cout << "Current: " << currentState->getColor() 
                  << " (" << currentState->getDuration() << "s)" << std::endl;
        currentState->nextState(this);
    }
    
    std::string getCurrentColor() const {
        return currentState ? currentState->getColor() : "Unknown";
    }
};

// Traffic Light State implementations
void RedState::nextState(TrafficLightContext* context) {
    context->changeState(std::make_unique<GreenState>());
}

void YellowState::nextState(TrafficLightContext* context) {
    context->changeState(std::make_unique<RedState>());
}

void GreenState::nextState(TrafficLightContext* context) {
    context->changeState(std::make_unique<YellowState>());
}

// Example usage and demonstration
int main() {
    std::cout << "=== Basic State Pattern Demo ===" << std::endl;
    
    // Create context with initial state
    Context fsm(std::make_unique<StateA>());
    
    // Demonstrate state transitions
    for (int i = 0; i < 5; ++i) {
        std::cout << "\nRequest " << (i + 1) << ":" << std::endl;
        fsm.request();
    }
    
    std::cout << "\n=== Traffic Light FSM Demo ===" << std::endl;
    
    // Create traffic light FSM
    TrafficLightContext trafficLight(std::make_unique<RedState>());
    
    // Demonstrate traffic light state transitions
    for (int i = 0; i < 6; ++i) {
        std::cout << "\nCycle " << (i + 1) << ":" << std::endl;
        trafficLight.next();
    }
    
    return 0;
}