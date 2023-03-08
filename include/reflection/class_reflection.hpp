
#pragma once

#include "field_reflection.hpp"
#include "function_reflection.hpp"
#include "reflection_helper.hpp"
namespace refl
{

class rclass
{
private:
    struct class_iface
    {
        virtual rfunction* find_function(std::string_view name) const = 0;
        virtual rfield* find_field(std::string_view name) const       = 0;
    };

    template <class Target>
    struct class_info_t;

public:
    rclass() = delete;

    template <typename Target>
    static constexpr auto make_class()
    {
        using type = class_info_t<Target>;
        return rclass(type::reflected_info());
    }
    rfunction* find_function(std::string_view name) const
    {
        return m_info->find_function(name);
    }
    rfield* find_field(std::string_view name) const { return m_info->find_field(name); }

private:
    class_iface const* m_info;

private:
    constexpr rclass(class_iface const* ptr) : m_info(ptr) {}
};

template <class Target>
struct rclass::class_info_t final : public rclass::class_iface
{
public:
    static constinit class_info_t const class_info;

    static constexpr auto m_fields =
        frozen::make_unordered_map(refl::reflect_all_t<typename Target::pedigree_list,
                                                       refl::gather_fields,
                                                       refl::field_counter>::entry());

    static constexpr auto m_funcs = frozen::make_unordered_map(
        refl::to_array<refl::gather_functions, Target, refl::func_counts<Target>>::
            entry_point());

public:
    static constexpr auto reflected_info() { return &class_info; }
    virtual rfunction* find_function(std::string_view name) const override
    {
        return m_funcs.find(name) != m_funcs.end() ? m_funcs.at(name) : nullptr;
    }
    virtual rfield* find_field(std::string_view name) const override
    {
        return m_fields.find(name) != m_fields.end() ? m_fields.at(name) : nullptr;
    }
    template <typename... Args>
    Target* make_instance(Args... args) const
    {
        return new Target{std::forward<Args>(args)...};
    }
};

template <class Target>
constinit rclass::class_info_t<Target> const rclass::class_info_t<Target>::class_info =
    {};

} // namespace refl
