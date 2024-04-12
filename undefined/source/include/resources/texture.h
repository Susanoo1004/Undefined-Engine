#pragma once

#include <string>
#include <filesystem>
#include <array>

#include "resources/resource.h"
#include "wrapper/renderer.h"
#include "service_locator.h"
#include "utils/flag.h"

/// <summary>
/// A Class to store all the Texture data
/// </summary>
class UNDEFINED_ENGINE Texture : public Resource
{
public:
	/// <summary>
	/// A Constructor of Texture, creating a blank texture with a width and height given
	/// </summary>
	/// <param name="width">: Width of the texture created</param>
	/// <param name="height">: Height of the texture created</param>
	Texture(unsigned int width, unsigned int height);
	/// <summary>
	/// A Constructor of Texture, creating a texture with an image (e.g : png or jpg)
	/// </summary>
	/// <param name="filepath">: Path of the image you want to create a texture</param>
	/// <param name="isFlipped">: Do we need to flip the texture (by default : false)</param>
	Texture(const char* filepath, bool isFlipped = false);
	/// <summary>
	/// Destructor of Texture
	/// </summary>
	~Texture();

	/// <summary>
	/// Get the Texture ID
	/// </summary>
	/// <returns>Return the Texture ID</returns>
	unsigned int GetID() const;
	/// <summary>
	/// Set the Texture ID 
	/// </summary>
	/// <param name="newID">: New ID of the Texture</param>
	void SetID(unsigned int newID);
	/// <summary>
	/// Get the Texture width
	/// </summary>
	/// <returns>Return the Texture width</returns>
	unsigned int GetWidth() const;
	/// <summary>
	/// Get the Texture height
	/// </summary>
	/// <returns>Return the Texture height</returns>
	unsigned int GetHeight() const;
	/// <summary>
	/// Check if the Resource is valid
	/// </summary>
	/// <returns>Return either true if it is valid or false</returns>
	bool IsValid() const;

	/// <summary>
	/// Pointer for the Texture data
	/// </summary>
	const void* Data;

private:
	/// <summary>
	/// ID of the Texture
	/// </summary>
	unsigned int mID = 0;
	/// <summary>
	/// Width of the Texture
	/// </summary>
	int mWidth = 0;
	/// <summary>
	/// Height of the Texture
	/// </summary>
	int mHeight = 0;

	/// <summary>
	/// Pointer to our Renderer to simplify the calls from the ServiceLocator
	/// </summary>
	Renderer* mRenderer = nullptr;

public:
	/// <summary>
	/// Load a Cubemap
	/// </summary>
	/// <param name="faces">: std::vector of the faces of the Cubemap</param>
	/// <returns>Return the ID of the Cubemap</returns>
	static unsigned int LoadCubeMap(const std::vector<std::string>& faces);
};