#pragma once

#include <unordered_map>

#include "wrapper/service_type.h"
#include "wrapper/window_manager.h"
#include "wrapper/renderer.h"

class ServiceLocator
{
public:

    static void Setup();

    template<typename ServiceType>
    static void Provide(ServiceType* p_service)
    {
        mServices[typeid(ServiceType).hash_code()] = p_service;
    }

    template<typename ServiceType>
    static ServiceType* Get()
    {
        return mServices[typeid(ServiceType).hash_code()];
    }


    static void CleanServiceLocator();
private:
    static inline std::unordered_map<size_t, ServiceType*> mServices;
};

