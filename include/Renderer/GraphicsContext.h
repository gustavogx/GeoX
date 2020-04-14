#pragma once

namespace GX{

    class GraphicsContext{
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}