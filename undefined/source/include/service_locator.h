#pragma once

#include <unordered_map>

#include "wrapper/window.h"
#include "wrapper/renderer.h"
#include "wrapper/input_manager.h"

#include "utils/flag.h"

/// <summary>
/// Class for the ServiceLocator to get our services
/// </summary>
class ServiceLocator
{
    STATIC_CLASS(ServiceLocator)

public:
    /// <summary>
    /// Setup the ServiceLocator
    /// </summary>
    UNDEFINED_ENGINE static void Setup();

    /// <summary>
    /// Setup the callbacks of the services
    /// </summary>
    /// <returns></returns>
    UNDEFINED_ENGINE static void SetupCallbacks();

    /// <summary>
    /// Provide to the ServiceLocator a ServiceType
    /// </summary>
    /// <typeparam name="ServiceType">: Type of service you want to provide (e.g : Renderer, Window, ...)</typeparam>
    /// <param name="p_service">: Pointer to the service you provide</param>
    template<typename ServiceType>
    static void Provide(ServiceType* const p_service)
    {
        mServices[typeid(ServiceType).hash_code()] = p_service;
    }

    /// <summary>
    /// Get a service type stored into the ServiceLocator
    /// </summary>
    /// <typeparam name="ServiceType">: Type of service you want to get</typeparam>
    /// <returns>Return a pointer to the first service off the good type</returns>
    template<typename ServiceType>
    static ServiceType* Get()
    {
        return reinterpret_cast<ServiceType*>(mServices[typeid(ServiceType).hash_code()]);
    }

    /// <summary>
    /// Delete all the service from the ServiceLocator
    /// </summary>
    UNDEFINED_ENGINE static void CleanServiceLocator();

private:
    /// <summary>
    /// std::unordered_map of our services
    /// </summary>
    UNDEFINED_ENGINE static inline std::unordered_map<size_t, ServiceType*> mServices;
};

