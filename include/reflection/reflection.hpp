
#pragma once
#include "reflection_utils.hpp"
#include "reflection_types.hpp"
#include "reflection_concepts.hpp"
#include "reflection_helper.hpp"
#include "reflection_generator.hpp"

#include "field_reflection.hpp"
#include "function_reflection.hpp"
#include "class_reflection.hpp"

#include "meta/type_list.hpp"
#include <frozen/unordered_map.h>

#define REFLECT_CLASS_INFO()                                                             \
    static auto static_class()                                                           \
    {                                                                                    \
        static auto self_class = refl::rclass::make_class<this_type>();                  \
        return &self_class;                                                              \
    }

#define REFLECT_CLASS()                                                                  \
public:                                                                                  \
    DECLARE_TYPE();                                                                      \
    using pedigree_list = meta::list::push_front<super::pedigree_list, this_type>;       \
                                                                                         \
public:                                                                                  \
    template <std::size_t, class>                                                        \
    struct detail_field_reflection;                                                      \
    template <std::size_t, class>                                                        \
    struct detail_function_reflection;                                                   \
                                                                                         \
private:

#define GENERATE_BODY()                                                                  \
    REFLECT_CLASS();                                                                     \
                                                                                         \
public:                                                                                  \
    REFLECT_CLASS_INFO();

#define GENERATE_BASE_OBJECT_BODY()                                                      \
public:                                                                                  \
    using super         = std::nullptr_t;                                                \
    using this_type     = ReflectionBase;                                                \
    using pedigree_list = meta::typelist<super>;

class ReflectionBase
{
public:
    GENERATE_BASE_OBJECT_BODY()
};