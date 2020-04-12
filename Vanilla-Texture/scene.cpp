#include "scene.h"
#include "texture.h"

Texture texture;

void Init() {
	// 设置投影矩阵
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

	// 重置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 设置擦除背景颜色
	glClearColor(0.1, 0.4, 0.6, 1.0);

	// 开启面剔除功能
	glEnable(GL_CULL_FACE);

	///![0] 灯光初始化
	// 可编程管线中总共只有 8 盏灯
	//	GL_LIGHT0
	//  GL_LIGHT1
	//	...
	//  GL_LIGHT7

	// 开启光照
	glEnable(GL_LIGHTING);
	
	// 启用 0 号光源
	glEnable(GL_LIGHT0);

	// 设置0号灯光的颜色
	// 环境/漫反射/镜面反射等可以分别设置不同颜色的光照
	float blackColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float whiteColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);  // 环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);  // 漫反射光
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); // 镜面反射光

	// 设置光源类型
	//	direction light -- 方向光，如太阳光
	//  point light -- 点光源
	//  spot light -- 聚光灯
	// {0.0f, 1.0f, 0.0f, 0.0f} -- 最后一个写0表示是方向光，表示点在无穷远处，如太阳
	float lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// 设置物体的材质，物体对各种光（环境/漫反射/镜面反射）的反射系数
	// 全黑{ 0.0f, 0.0f, 0.0f, 1.0f } -- 什么都不反射，一片漆黑
	float blackMaterial[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float ambientMaterial[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float diffuseMaterial[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float specularMaterial[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);

	///![0]

	texture.Init("../Assets/test.bmp");
}

void Draw() {
	// 重置模型视图矩阵
	glLoadIdentity();

	// 绘制之前清除颜色缓冲区
	glClear(GL_COLOR_BUFFER_BIT);

	// 开启纹理功能
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);

	// 立即绘图模式
	glBegin(GL_TRIANGLES);

	// 漫反射和镜面反射和法线都有关系
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0, -0.5, Z_PLAN+3);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, -0.5, Z_PLAN+3);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, -0.5f, Z_PLAN-5.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}