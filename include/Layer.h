#pragma once

#include "Core/Core.h"
//#include "Hazel/Core/Timestep.h"
#include "Base/EventBase.h"

namespace GX {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {} //Timestep ts) {}
		//virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}