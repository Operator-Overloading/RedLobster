// CORE/src/Layer.cpp

#include "Layer.hpp"

namespace Lobster
{
	Layer::Layer(const std::string& name) : name(name) {}


	LayerStack::LayerStack()
	{
		layer_insert = layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layer_insert = layers.emplace(layer_insert,layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(),layers.end(),layer);

		if(it != layers.end())
		{
			layers.erase(it);
			layer_insert--;
		}

		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin(),layers.end(),overlay);

		if(it != layers.end())
			layers.erase(it);

		overlay->OnDetach();
	}
}