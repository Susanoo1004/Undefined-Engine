#pragma once
#include <vector>

#include "utils/flag.h"

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
	/// Virtual destructor of Resource
	/// </summary>
	virtual ~Resource();
	/// <summary>
	/// Check if the Resource is valid
	/// </summary>
	/// <returns>Return if the Resource is valid</returns>
	virtual bool IsValid();
};