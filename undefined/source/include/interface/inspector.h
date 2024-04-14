#pragma once
#include "utils/flag.h"
#include <refl.hpp>
#include "resources/model.h"
#include "world/scene_manager/scene.h"

class UNDEFINED_ENGINE Inspector
{
	STATIC_CLASS(Inspector)

public:
	static void Init();
	static void ShowWindow(Scene scene);

    template <typename T>
    void Display(T* obj)
    {
        constexpr refl::type_descriptor<T> descriptor = refl::reflect<T>();
        // iterate over the members of T
        refl::util::for_each(descriptor.members, [&]<typename DescriptorT>(const DescriptorT)
        {
            if constexpr (!refl::descriptor::is_function<DescriptorT>(DescriptorT{}))
            {
                using MemberT = typename DescriptorT::value_type;

                if constexpr (refl::is_reflectable<T>())
                {
                    Display<MemberT>(&DescriptorT::get(obj));
                }
            }
        });
    }

private:
    std::shared_ptr<Model> picking;
};