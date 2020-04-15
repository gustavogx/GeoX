#include "Core/Core.h"
#include "Core/Input.h"

#ifdef GX_PLATFORM_LINUX
	#include "Platform/Linux/LinuxInput.h"
#endif

namespace GX {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef GX_PLATFORM_LINUX
		return CreateScope<WindowsInput>();
	#else
		GX_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 