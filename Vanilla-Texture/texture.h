#pragma once
#include <windows.h>
#include <gl/GL.h>

class Texture
{
public:

	void Init(const char *file);

	// 在 GPU 中，用整数表示资源的ID，即用 unsigned int 标识资源
	GLuint mTextureID; // gpu resource id
};

