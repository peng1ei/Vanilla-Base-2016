#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <unordered_map>

class Texture
{
protected:
	void Init(const char*imagePath,bool invertY);
public:
	GLuint mTextureID;//gpu
	std::string mPath;
	static Texture*LoadTexture(const char*imagePath, bool invertY = true);
	static void UnloadTexture(Texture*texture);
	static std::unordered_map<std::string, Texture*> mCachedTextures;
};