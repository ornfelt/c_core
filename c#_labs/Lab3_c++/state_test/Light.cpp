#include<iostream> 
#include "Light.h"
#include "ConcreteLightStates.h"

using namespace std;

Light::Light()
{
	// All lights are initially turned off
	currentState = &LightOff::getInstance();
}

void Light::setState(LightState& newState)
{
	currentState->exit(this);  // do stuff before we change state
	currentState = &newState;  // actually change states now
	currentState->enter(this); // do stuff after we change state
	cout << "Changed light state" << endl;
}

void Light::toggle()
{
	// Delegate the task of determining the next state to the current state
	cout << "Toggling light..." << endl;
	currentState->toggle(this);
	cout << "Light toggled" << endl;
}
