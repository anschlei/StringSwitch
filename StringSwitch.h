/*
* @autor	: Andy Schleising
* @date		: 19.08.2023
* @copyright: MIT
* 
* @description: A simple string switch case which can use to compare strings like a normal switch case statements.
* It can be used with macros, "WARNING" it can be really hard to debug in many cases, or it can be used directly with the function calls.
* IMPORTANT: the first case is always the default case. Why ? I force you to think about default cases :)
* 
* @INFORMATION: 
* Scoped Macro, creates a new { } scope, this will avoid problems with default names. 
* The macro variant scoped : use the variable name: SCOPED_STRINGSWITCH
* The macro variant unscoped : use the variable name: STRINGSWITCH
* PLEASE avoid these names !
* 
* @examples
* 
* @@scoped macro
* 
*	const char charString[] = "Marc";
*	STRING_SWITCH(STRING_COMPARE(charString),
*		STRING_CASE("default", std::cout << "Scoped: called default : " << charString << "\n";),
*		STRING_CASE("John", std::cout << "Scoped: Hello, " << charString << "! \n";),
*		STRING_CASE("Marc", std::cout << "Scoped: Hello, " << charString << "! \n";),
*		STRING_CASE("Marc", std::cout << "Scoped: Error: Hello, " << charString << "! \n";),
*		STRING_CASE("Han", std::cout << "Scoped: Hello, " << charString << "! \n";)
*	)
*
* 
* @@unscoped macro
* 
*	const char charString[] = "Marc";
*	INIT_STRING_SWITCH(
*		STRING_CASE("default", std::cout << "Unscoped: called default : " << charString << "\n";),
*		STRING_CASE("John", std::cout << "Unscoped: Hello, " << charString << "! \n";),
*		STRING_CASE("Marc", std::cout << "Unscoped: Hello, " << charString << "! \n";),
*		STRING_CASE("Marc", std::cout << "Unscoped: Error: Hello, " << charString << "! \n";),
*		STRING_CASE("Han", std::cout << "Unscoped: Hello, " << charString << "! \n";)
*	)
*
*	* other function stuff etc ... *
*
*	STRING_SWITCH_COMPARE(charString)
* 
* 
* @@with function calls
* 	const char charString[] = "Marc";
*	static StringSwitch stringSwitch
*	(
*		{
*			{
*				"default",
*				 std::function<void()>([&] {std::cout << "Wihtout macro : called default : " << charString << "\n"; })
*			},
*			{
*				"John",
*				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
*			},
*			{
*				"Marc",
*				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
*			},
*			{
*				"Marc",
*				std::function<void()>([&] {std::cout << "Wihtout macro : Error, Hello, " << charString << "! \n"; })
*			},
*			{
*				"Han",
*				std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
*			}
*		}
*	);
*	stringSwitch.Switch(charString);
* 
*/

#ifndef STRING_SWITCH_H
#define STRING_SWITCH_H

#include <unordered_map>
#include <functional>
#include <vector>
#include <tuple>
#include <string>

#include <iostream>

#define STRING_CASE(a, b)  {a, std::function<void()>([&] {b})}
#define STRING_COMPARE(value) value

//Create and access a string switch with a seperated scope via macro
#define STRING_SWITCH(StringCompare, ... )				\
{														\
static StringSwitch SCOPED_STRINGSWITCH({ __VA_ARGS__ });		\
SCOPED_STRINGSWITCH.Switch(StringCompare);						\
}

//Alternative variant to declare with macro a string switch and access it later in the current scope
#define INIT_STRING_SWITCH(...)						\
static StringSwitch STRINGSWITCH({ __VA_ARGS__ });	\

#define STRING_SWITCH_COMPARE(StringCompare)		\
STRINGSWITCH.Switch(StringCompare);


/*
* @description: StringSwitch is a class that has two member variables.
* 
* @m_inventory: includes the string key with a specitifc index that is used to get the right function from m_inventoryFunctions to call.
* @m_inventoryFunctions: Contains the functions associated with the element index of the key of m_inventory.
*/
class StringSwitch 
{
public:
	/*
	* @description: The constructor of StringSwitch class, registered all cases which is given. If the key is ambiguous, they will ignored.
	* @param: std::vector<std::pair<const char*, std::function<void()>>> as a switch statement
	*/
	explicit StringSwitch(std::vector<
		std::pair<const char*,
		std::function<void()>
		>
	> _SwitchCase)
	{
		for (auto& item : _SwitchCase)
		{
			if (m_inventory.find(item.first) == m_inventory.end())
			{
				m_inventory[item.first] = m_inventory.size();
				m_inventoryFunctions.push_back(item.second);
			}
			else
			{
				std::cerr << "ERROR: StringSwitch.h: ambiguous given string value : " << item.first << " at registerd switch function. At " << m_inventoryFunctions.size() + 1 << " compared string. This is case is IGNORED !!.\n";
			}
		}
	};
	~StringSwitch() = default;

	/*
	* @description: The function Switch, call the switch(pString) case function. If the key doesn't exist, the first element will be called as default.
	* @param: const char* as a target string
	*/
	void Switch(const char* _pString)
	{
		m_inventoryFunctions.at(m_inventory[_pString])();
	};

private:
	std::unordered_map<std::string,unsigned int> m_inventory{};
	std::vector<std::function<void()>> m_inventoryFunctions{};
};

#endif // !STRING_SWITCH_H