#include "gepch.h"
#include "LayerStack.h"

namespace Pangolin {
	Pangolin::LayerStack::LayerStack() {}

	Pangolin::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void Pangolin::LayerStack::push_layer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layer_insert_index, layer);
		m_layer_insert_index++;
	}

	void Pangolin::LayerStack::push_overlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void Pangolin::LayerStack::pop_layer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_layer_insert_index--;
		}
	}

	void Pangolin::LayerStack::pop_overlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
			m_layers.erase(it);
	}
}
