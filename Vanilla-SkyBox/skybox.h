#pragma once
#include <windows.h>
#include <gl/gl.h>
#include "texture.h"

// 天空盒一般为 1x1x1 或 0.5x0.5x0.5 的盒子，套在摄像机上
// 一直跟着摄像机跑
// 天空位于最远的地方
class SkyBox
{
public:
	Texture *front, *back, *right, *left, *top, *bottom;
	void Init(const char *path);
	void Draw(float cameraX, float cameraY, float cameraZ);
};

