#include "ConcreteLightStates.h"
#include<iostream> 

using namespace std;

void LightOff::toggle(Light* light)
{
	// Off -> Low
	light->setState(LowIntensity::getInstance());
}

LightState& LightOff::getInstance()
{
	static LightOff singleton;
	return singleton;
}

void LowIntensity::toggle(Light* light)
{
	// Low -> Medium
	light->setState(MediumIntensity::getInstance());
}

LightState& LowIntensity::getInstance()
{
	static LowIntensity singleton;
	cout << "LowIntensity::getInstance" << endl;
	return singleton;
}

void MediumIntensity::toggle(Light* light)
{
	// Medium -> High
	light->setState(HighIntensity::getInstance());
}

LightState& MediumIntensity::getInstance()
{
	static MediumIntensity singleton;
	return singleton;
}

void HighIntensity::toggle(Light* light)
{
	// High -> Low
	light->setState(LightOff::getInstance());
}

LightState& HighIntensity::getInstance()
{
	static HighIntensity singleton;
	return singleton;
}
