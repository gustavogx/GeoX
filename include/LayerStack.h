#pragma once

#include "Core/Core.h"
#include "Layer.h"

namespace GX {

	class LayerStack
	{
	private:
		std::vector<Layer*> m_Layers;
		u_int32_t m_LayerInsertIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack();

		u_int32_t PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PopLayer(const u_int32_t &index);

		u_int32_t PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);
		void PopOverlay(const u_int32_t &index);

		inline Layer& Get(const u_int32_t &index) { return *m_Layers.at(index); }

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	};

}