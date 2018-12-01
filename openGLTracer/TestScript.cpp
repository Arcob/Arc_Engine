#include "TestScript.h"



/*TestScript::TestScript()
{
}


TestScript::~TestScript()
{
}*/

void TestScript::Start()
{
	std::cout << "box Start" << std::endl;
}

void TestScript::Update()
{
	std::cout << gameObject()->name() << std::endl;
}