
#include "Core/Input/Input.h"

#ifdef GX_PLATFORM_LINUX
	#include "Platform/Linux/LinuxInput.h"
#endif

namespace GX {

	ScopePointer<Input> Input::s_Instance = Input::Create();

	ScopePointer<Input> Input::Create()
	{
	#ifdef GX_PLATFORM_LINUX
		return MakeScopePointer<LinuxInput>();
	#else
		GX_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 