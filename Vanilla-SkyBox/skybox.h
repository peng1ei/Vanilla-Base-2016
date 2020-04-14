#pragma once
#include <windows.h>
#include <gl/gl.h>
#include "texture.h"
#include "displaylist.h"

// 天空盒一般为 1x1x1 或 0.5x0.5x0.5 的盒子，套在摄像机上
// 一直跟着摄像机跑
// 天空位于最远的地方

// 深度缓冲区 -- Depth buffer
//  范围：[0, 1] 离 Camera 越远，值越大
/**
	
*/
class SkyBox
{
public:
	DisplayList mSkyBox;
	Texture *front, *back, *right, *left, *top, *bottom;
	void Init(const char *path);
	void Draw(float cameraX, float cameraY, float cameraZ);
};

