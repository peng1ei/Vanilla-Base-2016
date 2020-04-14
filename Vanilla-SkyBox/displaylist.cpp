#include "displaylist.h"

void DisplayList::Init(std::function<void()> foo) {
	mDisplayList = glGenLists(1);

	glNewList(mDisplayList, GL_COMPILE);// ������ʾ�б�
	foo(); // �����ڻص�����
	glEndList();
}

void DisplayList::Draw() {
	glCallList(mDisplayList);
}
