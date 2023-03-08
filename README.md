# GReflection 

### A Header only, compile time binded c++ reflection framework that supports inheritance



all you have to do is include and inherit base class :) 

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
```

then you will get a compile time binded reflection class representation.

which enables duck typing and etc...

more details will be added in future
