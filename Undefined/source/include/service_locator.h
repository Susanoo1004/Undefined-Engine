#pragma once

#include <unordered_map>

#include "wrapper/window_manager.h"
#include "wrapper/renderer.h"
#include "wrapper/input_manager.h"
#include "utils/flag.h"

class ServiceLocator
{
public:
    UNDEFINED_ENGINE static void Setup();

    template<typename ServiceType>
    static void Provide(ServiceType* p_service)
    {
        mServices[typeid(ServiceType).hash_code()] = p_service;
    }

    template<typename ServiceType>
    static ServiceType* Get()
    {
        return reinterpret_cast<ServiceType*>(mServices[typeid(ServiceType).hash_code()]);
    }

    UNDEFINED_ENGINE static void CleanServiceLocator();

private:
    UNDEFINED_ENGINE static inline std::unordered_map<size_t, ServiceType*> mServices;
};

