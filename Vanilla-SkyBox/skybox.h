#pragma once
#include <windows.h>
#include <gl/gl.h>
#include "texture.h"

// ��պ�һ��Ϊ 1x1x1 �� 0.5x0.5x0.5 �ĺ��ӣ������������
// һֱ�����������
// ���λ����Զ�ĵط�
class SkyBox
{
public:
	Texture *front, *back, *right, *left, *top, *bottom;
	void Init(const char *path);
	void Draw(float cameraX, float cameraY, float cameraZ);
};

