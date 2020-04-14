#include "displaylist.h"

void DisplayList::Init(std::function<void()> foo) {
	mDisplayList = glGenLists(1);

	glNewList(mDisplayList, GL_COMPILE);// 编译显示列表
	foo(); // 类似于回调函数
	glEndList();
}

void DisplayList::Draw() {
	glCallList(mDisplayList);
}
