#pragma once
#include <vector>

#include "utils/flag.h"

#include <refl.hpp>

/// <summary>
/// Base Class for all our Resources
/// </summary>
class UNDEFINED_ENGINE Resource
{
public:
	/// <summary>
	/// Constructor of Resource
	/// </summary>
	Resource();
	/// <summary>
	/// Destructor of Resource (can be override)
	/// </summary>
	virtual ~Resource();
	/// <summary>
	/// Check if the Resource is valid
	/// </summary>
	/// <returns>Return either true if it is valid or false</returns>
	virtual bool IsValid();
};

REFL_AUTO(type(Resource)
);