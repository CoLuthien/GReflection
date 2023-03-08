
#include "reflection/reflection.hpp"
#include <iostream>

class Sample : public ReflectionBase
{
public:
    GENERATE_BODY();

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b)
    {
        std::cout << "add " << a << " and " << b << '\n';
        return a + b;
    }

public:
    REFLECT_FIELD(int, x);
    REFLECT_FIELD(int, w);
};

int
main()
{
    auto* ptr   = new Sample;
    auto* clazz = Sample::static_class();

    auto func_add = clazz->find_function("add");

    if (func_add != nullptr)
    {
        int x = func_add->invoke<int>(ptr, 1, 2);
    }

    ptr->w = 0;

    std::cout << "initial w value == " << ptr->w << '\n';
    auto prop_w = clazz->find_field("w");
    if (prop_w != nullptr)
    {
        void* obj = ptr;
        int value = prop_w->get<int>(obj); // 0
        std::cout << "w value get by reflection == " << value << '\n';
        prop_w->set<int>(obj, 12); // set to 12
        std::cout << "try set w value to 12\n";
        value = prop_w->get<int>(obj); // 12
        std::cout << "w value get by reflection == " << value << '\n';
    }

    return 0;
}