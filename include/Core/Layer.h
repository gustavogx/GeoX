#pragma once

#include "Core/Core.h"
#include "Core/Timestep.h"
#include "Core/Base/Event.h"

namespace GX {

	class Layer
	{

	private:
		bool m_Visible;

	public:
		Layer(const std::string& name = "");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline bool& IsVisible() { return m_Visible; }
		inline bool  IsVisible() const { return m_Visible; }
		
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}