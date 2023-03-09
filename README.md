# GReflection 

### A Header only, compile time binded c++ reflection framework that supports inheritance



all you have to do is include and inherit base class :) 

and say 
```c++ 
auto reflection = CLASS_NAME::static_class(); 
```

then all the magic goes inside and you will get below :)

``` c++
#include "reflection/reflection.hpp"

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

class SampleChild : public Sample 
{
public:
    GENERATE_BODY()

private:
    REFLECT_FIELD(int, x_child);
    REFLECT_FIELD(int, w_child);
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
```

then you will get a compile time binded reflection class representation.

which enables duck typing and etc...

more details will be added in future
