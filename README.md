# Small and Simple StringSwitch

## How to use

You can use a String Switch with macro or without macro. But warning, marcos are very hard to debug !


### With Macro

#### scoped macro

```
const char charString[] = "Marc";
STRING_SWITCH(STRING_COMPARE(charString),
	STRING_CASE("default", std::cout << "Scoped: called default : " << charString << "\n";),
	STRING_CASE("John", std::cout << "Scoped: Hello, " << charString << "! \n";),
	STRING_CASE("Marc", std::cout << "Scoped: Hello, " << charString << "! \n";),
	STRING_CASE("Marc", std::cout << "Scoped: Error: Hello, " << charString << "! \n";),
	STRING_CASE("Han", std::cout << "Scoped: Hello, " << charString << "! \n";)
)
```

#### unscoped macro

```
const char charString[] = "Marc";
INIT_STRING_SWITCH(
	STRING_CASE("default", std::cout << "Unscoped: called default : " << charString << "\n";),
	STRING_CASE("John", std::cout << "Unscoped: Hello, " << charString << "! \n";),
	STRING_CASE("Marc", std::cout << "Unscoped: Hello, " << charString << "! \n";),
	STRING_CASE("Marc", std::cout << "Unscoped: Error: Hello, " << charString << "! \n";),
	STRING_CASE("Han", std::cout << "Unscoped: Hello, " << charString << "! \n";)
)

* other function stuff etc ... *

STRING_SWITCH_COMPARE(charString)
```

### Without Macro
```
#include "StringSwitch.h"
const char charString[] = "Marc";
static StringSwitch stringSwitch
(
	{
		{
			"default",
			 std::function<void()>([&] {std::cout << "Wihtout macro : called default : " << charString << "\n"; })
		},
		{
			"John",
			std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
		},
		{
			"Marc",
			std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
		},
		{
			"Marc",
			std::function<void()>([&] {std::cout << "Wihtout macro : Error, Hello, " << charString << "! \n"; })
		},
		{
			"Han",
			std::function<void()>([&] {std::cout << "Wihtout macro : Hello, " << charString << "! \n"; })
		}
	}
);
stringSwitch.Switch(charString);
```