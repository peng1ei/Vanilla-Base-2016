#pragma once
#include <windows.h>
#include <gl/GL.h>

class Texture
{
public:

	void Init(const char *file);

	// �� GPU �У���������ʾ��Դ��ID������ unsigned int ��ʶ��Դ
	GLuint mTextureID; // gpu resource id
};

