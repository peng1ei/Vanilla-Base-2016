#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <functional>

// ��ʾ�б�������߻���ִ��Ч��
// ��ĳЩ����ʵ��ֻ��ִ��һ�Σ�����ȴ������ÿһ֡����ȥִ��
// �����ͽ�����Ч�ʣ���ʹ����ʾ�б�������ǰִ��ĳЩ����ָ��
// ��ִֻ��һ�Σ���������ִ��Ч��
class DisplayList
{
public:
	GLuint mDisplayList;
	void Init(std::function<void()> foo);
	void Draw();
};

