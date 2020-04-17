#pragma once
#include "Core/Core.h"

#ifdef GX_PLATFORM_LINUX
	#include "Platform/Linux/LinuxTimestep.h"
#endif

namespace GX {

class Timestep{
private:
	float m_Time;
public:
	Timestep(float time = 0.0f) : m_Time(time) {}

	operator float() const { return m_Time; }

	float GetSeconds() const { return m_Time; }
	float GetMilliseconds() const { return m_Time * 1000.0f; }

};

}