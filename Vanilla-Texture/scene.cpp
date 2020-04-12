#include "scene.h"
#include "texture.h"

Texture texture;

void Init() {
	// ����ͶӰ����
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

	// ������׶����ָ��Zƽ��Ĳü����εĿ�͸�
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

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ���ò���������ɫ
	glClearColor(0.1, 0.4, 0.6, 1.0);

	// �������޳�����
	glEnable(GL_CULL_FACE);

	///![0] �ƹ��ʼ��
	// �ɱ�̹������ܹ�ֻ�� 8 յ��
	//	GL_LIGHT0
	//  GL_LIGHT1
	//	...
	//  GL_LIGHT7

	// ��������
	glEnable(GL_LIGHTING);
	
	// ���� 0 �Ź�Դ
	glEnable(GL_LIGHT0);

	// ����0�ŵƹ����ɫ
	// ����/������/���淴��ȿ��Էֱ����ò�ͬ��ɫ�Ĺ���
	float blackColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float whiteColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);  // ������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);  // �������
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); // ���淴���

	// ���ù�Դ����
	//	direction light -- ����⣬��̫����
	//  point light -- ���Դ
	//  spot light -- �۹��
	// {0.0f, 1.0f, 0.0f, 0.0f} -- ���һ��д0��ʾ�Ƿ���⣬��ʾ��������Զ������̫��
	float lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// ��������Ĳ��ʣ�����Ը��ֹ⣨����/������/���淴�䣩�ķ���ϵ��
	// ȫ��{ 0.0f, 0.0f, 0.0f, 1.0f } -- ʲô�������䣬һƬ���
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
	// ����ģ����ͼ����
	glLoadIdentity();

	// ����֮ǰ�����ɫ������
	glClear(GL_COLOR_BUFFER_BIT);

	// ����������
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);

	// ������ͼģʽ
	glBegin(GL_TRIANGLES);

	// ������;��淴��ͷ��߶��й�ϵ
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