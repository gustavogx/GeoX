// Core
#pragma once
#include "Core/GeoXPCH.h"
#include "Data/InputCodes/KeyCodes.h"
#include "Data/InputCodes/MouseCodes.h"

#define GX_DEBUG

#ifdef GX_DEBUG
	#define GX_ENABLE_ASSERTS
#endif

#ifdef GX_ENABLE_ASSERTS
	#define GX_ASSERT(x, ...) { if(!(x)) { LOG_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
	#define GX_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
#else
	#define GX_ASSERT(x, ...)
	#define GX_CORE_ASSERT(x, ...)
#endif

#define GX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1<<x)

namespace GX{

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}
