//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//
//	string_view.cpp
//
//	This demonstrates the std::string_view 
//	as well as the simple heap allocation tracking
//
//	compile: clang++ string_view.cpp -std=c++17 -o string_view
//
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

#include <iostream>
#include <string>

unsigned int s_AllocCount = 0;

// overloaded operator new to track how many times
// has this program allocated memory in heap
void* operator new(size_t size)
{
	s_AllocCount++;
	std::cout << "Allocated " << size << "bytes" << std::endl;
	return malloc(size);
}

// print std::string
void print_string(const std::string &str)
{
	std::cout << str << std::endl;
}

// print std::string_view
void print_string(const std::string_view &str)
{
        std::cout << str << std::endl;
}

int main()
{
        // NOTE: clang std::string requires 32 bytes or longer to allocated into heap
        std::string str00 = "Bonjour, I am going to live in heap... Bonne nuit...";

#if 0	// use substr	
	// clang std::string requires 32 bytes or longer to allocated into heap
	std::string str01 = str00.substr(0, 37);
	std::string str02 = str00.substr(39, 41);

#else	// use string_view
	// basically, it has a pointer to the string + the size (like "view"ing a window [  o O  ])
	std::string_view str01(str00.c_str(), 37);
        std::string_view str02(str00.c_str() + 39, 41);
#endif

	// substrings result
        print_string(str00);
        print_string(str01);
        print_string(str02);

	// summary
	std::cout << "------------------------------------------\n";
	std::cout << "  Total:  " << s_AllocCount << " allocations." << std::endl;
	std::cout << "------------------------------------------\n";

	return 0;
}

