#include "Light.h"
#include "ConcreteLightStates.h"

// https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

int main()
{
	//class LightState;
	Light light;
	light.setState(LowIntensity::getInstance());
	light.setState(HighIntensity::getInstance());
	light.toggle();
	return 0;
}
