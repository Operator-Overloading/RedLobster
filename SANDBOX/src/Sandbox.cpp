// SANDBOX/src/Sandbox.cpp

#include "Core.hpp"

using namespace Lobster;

class Sandbox : public Application
{
public:
	void OnStart() override
	{
	}
	void OnUpdate(float dt) override
	{
	}
};

int main()
{
	return Sandbox{}.Run();
}