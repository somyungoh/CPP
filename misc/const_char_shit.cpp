//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//
//	const_char_shit.cpp
//
//	Following-up the frustration I had during the development of
//  Hello Vulkan, this is a play around with const char*,
//  to see wtf is going on with the memory management of this type.
//
//	compile: clang++ const_char_shit.cpp -o bin/const_char_shit
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// TODO: std::vector<const char*>  what's happening?
// const char* scope?
#include <vector>
#include <iostream>

void test_init_in_vector()
{
    std::vector<const char*> vec;
    vec.push_back("I am born directly into the vector");

    std::cout << vec[0] << " - WORKS" << std::endl;
}

const char* test_scope()
{
    std::cout << "Test: CString declared in a funtion. Is it alive after function call ends?" << std::endl;
    const char* cstr = "I am born inside a function";

    return cstr;
}

int main(int args, char** argv)
{
    const char* str = test_scope();
    std::cout << str << " - ALIVE" << std::endl;

    test_init_in_vector();

    std::cout << "WTF it works...." << std::endl;

    return EXIT_SUCCESS;
}