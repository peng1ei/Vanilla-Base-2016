#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <functional>

// 显示列表用于提高绘制执行效率
// 如某些绘制实际只需执行一次，但是却放在了每一帧里面去执行
// 这样就降低了效率，而使用显示列表，可以提前执行某些绘制指令
// 且只执行一次，因而能提高执行效率
class DisplayList
{
public:
	GLuint mDisplayList;
	void Init(std::function<void()> foo);
	void Draw();
};

