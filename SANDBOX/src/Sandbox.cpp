// SANDBOX/src/Sandbox.cpp

#include "Core.hpp"

#include <iostream>

using namespace Lobster;

class MainLayer : public Layer
{
public:
	void OnAttach() override {}
	void OnDetach() override {}
	void OnUpdate(float dt) override {}
	void OnEvent(Event& event) override
	{
	}
};

class Sandbox : public Application
{
public:
	void OnStart() override
	{
		PushLayer(new MainLayer{});
	}
	void OnUpdate(float dt) override
	{
	}
};

int main()
{
	return Sandbox{}.Run();
}