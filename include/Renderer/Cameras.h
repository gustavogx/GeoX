#pragma once
#include "Core/Core.h"

#include "glm/glm.hpp"

namespace GX{

    class OrthographicCamera{
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::vec3 m_Position;
        float m_Rotation = 0.0f;

    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& position ) { m_Position = position; RecalculateViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); } // this is a 2D camera

        const glm::vec3& GetPosition() const { return m_Position; }
        float GetRotation() const { return m_Rotation; }
    
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();
    };

}