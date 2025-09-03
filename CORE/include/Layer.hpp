// CORE/include/Layer.hpp

#pragma once
#include "Event.hpp"

#include <algorithm>
#include <vector>

namespace Lobster
{
	class LOBSTER_API Layer
	{
	public:
		Layer(const std::string& name = "null");
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return name; }
	private:
		std::string name;
	};

	class LOBSTER_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return layers.rend(); }
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layer_insert;
	};
}