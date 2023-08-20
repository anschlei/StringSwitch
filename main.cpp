#include "StringSwitch.h"


void InputValidationWithScopedMarco(const char* pInput)
{
	STRING_SWITCH(STRING_COMPARE(pInput),
		STRING_CASE("default", std::cout << "Scoped: called default : " << pInput << "\n";),
		STRING_CASE("John", std::cout << "Scoped: Hello, " << pInput << "! \n";),
		STRING_CASE("Marc", std::cout << "Scoped: Hello, " << pInput << "! \n";),
		STRING_CASE("Marc", std::cout << "Scoped: Error: Hello, " << pInput << "! \n";),
		STRING_CASE("Han", std::cout << "Scoped: Hello, " << pInput << "! \n";)
	)
}

void InputValidationWithUnscopedMarco(const char* pInput)
{
	INIT_STRING_SWITCH(
		STRING_CASE("default", std::cout << "Unscoped: called default : " << pInput << "\n";),
		STRING_CASE("John", std::cout << "Unscoped: Hello, " << pInput << "! \n";),
		STRING_CASE("Marc", std::cout << "Unscoped: Hello, " << pInput << "! \n";),
		STRING_CASE("Marc", std::cout << "Unscoped: Error: Hello, " << pInput << "! \n";),
		STRING_CASE("Han", std::cout << "Unscoped: Hello, " << pInput << "! \n";)
	)

	/*function stuff etc ... */
	
	STRING_SWITCH_COMPARE(pInput)
}

void InputValidationWithoutMarco(const char* pInput)
{
	static StringSwitch stringSwitch
	(
		{
			{
				"default",
				 std::function<void()>([&] {std::cout << "Wihtout macro : called default : " << pInput << "\n"; })
			},
			{
				"John",
				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << pInput << "! \n"; })
			},
			{
				"Marc",
				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << pInput << "! \n"; })
			},
			{
				"Marc",
				std::function<void()>([&] {std::cout << "Wihtout macro : Error, Hello, " << pInput << "! \n"; })
			},
			{
				"Han",
				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << pInput << "! \n"; })
			}
		}
	);
	stringSwitch.Switch(pInput);
}

int main()
{
	const char caseVariable[] = "Marc";
	InputValidationWithScopedMarco(caseVariable);
	InputValidationWithUnscopedMarco(caseVariable);
	InputValidationWithoutMarco(caseVariable);

	return 0;
}