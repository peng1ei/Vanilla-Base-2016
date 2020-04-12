#include "scene.h"
void Init() {
	glMatrixMode(GL_PROJECTION);

	// 可以计算出视锥体的范围：
	// Zplan的范围：[zNear, zFar]，zNear > 0, zFar > 0
	//		clipHalfHeight = Zplan * tan((fov/2)*PI/180.0f);  
	//		clipHalfWidth  = clipHalfHeight * aspect;
	//		aspect = w / h; // eg: 800.0f / 600.0f
	float fovy = 50.0f;
	float aspect = 800.0f / 600.0f;
	float zNear = 0.1f;
	float zFar = 1000.0f;

	// 计算视锥体中指定Z平面的裁剪矩形的宽和高
	// left = -clipHalfWidth;
	// right = clipHalfWidth;
	// bottom = -clipHalfWidth;
	// top = clipHalfWidth;
	float clipHalfHeight = -Z_PLAN *tan(ANGLE_TO_RADIAN(fovy/2));
	float clipHalfWidth = clipHalfHeight * aspect;

	// 超过由 left，left，bottom，top 指定的范围的顶点数据将被裁剪
	// 不会被显示到屏幕当中
	float left = -clipHalfWidth;
	float right = clipHalfWidth;
	float bottom = -clipHalfHeight;
	float top = clipHalfHeight;
	float clipWidth = 2 * clipHalfWidth;
	float clipHeight = 2 * clipHalfHeight;

	printf("Clip Range：\n");
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
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4ub(255, 255, 255, 255);
	
	// 立即绘图模式
	// 线的类型：
	//		GL_LINES
	//		GL_LINE_LOOP
	//		GL_LINE_STRIP
	glBegin(GL_LINE_STRIP);
	glColor4ub(255, 0, 0, 255);
	glVertex3f(0.0, 0.0, Z_PLAN);

	glColor4ub(0, 255, 0, 255);
	glVertex3f(-5.0, 0.0, Z_PLAN);

	//glVertex3f(-5.0, 0.0f, Z_PLAN);

	glColor4ub(0, 0, 255, 255);
	glVertex3f(-5.0, -2.0f, Z_PLAN);
	glEnd();
}