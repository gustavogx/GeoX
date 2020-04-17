#pragma once
#include "Core/Core.h"

namespace GX{

    class GraphicsContext{
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}