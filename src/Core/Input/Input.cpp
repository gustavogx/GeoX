
#include "Core/Input/Input.h"

#ifdef GX_PLATFORM_LINUX
	#include "Platform/Linux/LinuxInput.h"
#endif

namespace GX {

	Unique<Input> Input::s_Instance = Input::Create();

	Unique<Input> Input::Create()
	{
	#ifdef GX_PLATFORM_LINUX
		return MakeUnique<LinuxInput>();
	#else
		GX_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 