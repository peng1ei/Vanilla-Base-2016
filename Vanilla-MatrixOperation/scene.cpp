#include "scene.h"
void Init() {
	glMatrixMode(GL_PROJECTION);

	// ���Լ������׶��ķ�Χ��
	// Zplan�ķ�Χ��[zNear, zFar]��zNear > 0, zFar > 0
	//		clipHalfHeight = Zplan * tan((fov/2)*PI/180.0f);  
	//		clipHalfWidth  = clipHalfHeight * aspect;
	//		aspect = w / h; // eg: 800.0f / 600.0f
	float fovy = 50.0f;
	float aspect = 800.0f / 600.0f;
	float zNear = 0.1f;
	float zFar = 1000.0f;

	// ������׶����ָ��Zƽ��Ĳü����εĿ��͸�
	// left = -clipHalfWidth;
	// right = clipHalfWidth;
	// bottom = -clipHalfWidth;
	// top = clipHalfWidth;
	float clipHalfHeight = -Z_PLAN *tan(ANGLE_TO_RADIAN(fovy/2));
	float clipHalfWidth = clipHalfHeight * aspect;

	// ������ left��left��bottom��top ָ���ķ�Χ�Ķ������ݽ����ü�
	// ���ᱻ��ʾ����Ļ����
	float left = -clipHalfWidth;
	float right = clipHalfWidth;
	float bottom = -clipHalfHeight;
	float top = clipHalfHeight;
	float clipWidth = 2 * clipHalfWidth;
	float clipHeight = 2 * clipHalfHeight;

	printf("Clip Range��\n");
	printf("  left: %f\n", left);
	printf(" right: %f\n", right);
	printf("bottom: %f\n", bottom);
	printf("   top: %f\n", top);
	printf("clip width:    %f\n", clipWidth);
	printf("clip height:   %f\n\n", clipHeight);

	gluPerspective(fovy, aspect, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.1, 0.4, 0.6, 1.0);

	glEnable(GL_CULL_FACE);
}

void Draw() {
	// ����ģ����ͼ����
	//glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	// ����ģ�;���
	// һ��˳��Ϊ������ -> ��ת -> ƽ��
	//glScalef(1.0f, 1.0, 1.0f);
	//glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	//glTranslatef(1.0f, -1.0, 0.0f);

	// ʹ�� glPushMatrix������������еĲ����������ջ���ľ������
	// glPushMatrix ����Ƕ��
	glPushMatrix();
	
	// ���⽻����ת��ƽ�Ƶ�˳��ᵼ�²�ͬ�Ľ��
	// �������Ծ�����ֵ�˳���й�ϵ������������ľ���˳��
	glScalef(1.0f, 1.0, 1.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, -1.0, 0.0f);

	// ������ͼģʽ
	glBegin(GL_TRIANGLES);
	glColor4ub(255, 0, 0, 255);
	glVertex3f(0.0, 1.0, Z_PLAN);

	glColor4ub(0, 255, 0, 255);
	glVertex3f(-1.0, 0.0, Z_PLAN);

	glColor4ub(0, 0, 255, 255);
	glVertex3f(1.0, 0.0f, Z_PLAN);
	glEnd();

	glPopMatrix();
}