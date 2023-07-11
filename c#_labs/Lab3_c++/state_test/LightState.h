#pragma once
#include "Light.h"

// Forward declaration to resolve circular dependency/include
class Light;

class LightState
{
public:
	virtual void enter(Light* light) = 0;
	virtual void toggle(Light* light) = 0;
	virtual void exit(Light* light) = 0;
	virtual ~LightState() {}
};
