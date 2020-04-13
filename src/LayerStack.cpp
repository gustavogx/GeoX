#include "Core/GeoXPCH.h"
#include "LayerStack.h"

namespace GX {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	u_int32_t LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		return m_LayerInsertIndex++;
	}

	u_int32_t LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace(m_Layers.end() - 1, overlay);
		return m_Layers.size()-2;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopLayer(const u_int32_t &index)
	{
		auto it = m_Layers.begin() + index;
		if (it < m_Layers.begin() + m_LayerInsertIndex)
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(const u_int32_t &index)
	{
		auto it = m_Layers.begin() + index;
		if (it >= m_Layers.begin() + m_LayerInsertIndex && it < m_Layers.end())
		{
			(*it)->OnDetach();
			m_Layers.erase(it);
		}
	}
}
