#include "scene.h"
#include "texture.h"
#include "objmodel.h"
#include "camera.h"

Texture *texture;
ObjModel model;
Camera camera;

POINT originalPos;
bool bRotateView = false;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_RBUTTONDOWN:

		originalPos.x = LOWORD(lParam);
		originalPos.y = HIWORD(lParam);
		ClientToScreen(hwnd, &originalPos);
		SetCapture(hwnd);
		ShowCursor(false);
		bRotateView = true;
		break;
	case WM_RBUTTONUP:
		bRotateView = false;
		SetCursorPos(originalPos.x, originalPos.y);
		ReleaseCapture();
		ShowCursor(true);
		break;
	case WM_MOUSEMOVE:
		if (bRotateView)
		{
			POINT currentPos;
			currentPos.x = LOWORD(lParam);
			currentPos.y = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
			float angleRotatedByRight = (float)deltaY / 1000.0f;
			float angleRotatedByUp = (float)deltaX / 1000.0f;
			camera.Yaw(-angleRotatedByUp);
			camera.Pitch(-angleRotatedByRight);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			camera.mbMoveLeft = true;
			break;
		case 'D':
			camera.mbMoveRight = true;
			break;
		case 'W':
			camera.mbMoveForward = true;
			break;
		case 'S':
			camera.mbMoveBackward = true;
			break;
		}
		break;
	case WM_KEYUP:

		switch (wParam)
		{
		case 'A':
			camera.mbMoveLeft = false;
			break;
		case 'D':
			camera.mbMoveRight = false;
			break;
		case 'W':
			camera.mbMoveForward = false;
			break;
		case 'S':
			camera.mbMoveBackward = false;
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void Init(int width, int height) {
	glViewport(0, 0, width, height);

	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);

	// ���Լ������׶��ķ�Χ��
	// Zplan�ķ�Χ��[zNear, zFar]��zNear > 0, zFar > 0
	//		clipHalfHeight = Zplan * tan((fov/2)*PI/180.0f);  
	//		clipHalfWidth  = clipHalfHeight * aspect;
	//		aspect = w / h; // eg: 800.0f / 600.0f
	float fovy = 50.0f;
	float aspect = (float)width / (float)height;
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

	// ����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ���ò���������ɫ
	glClearColor(0.1, 0.4, 0.6, 1.0);

	// �������޳�����
	glEnable(GL_CULL_FACE);

	// ������Ȳ��Թ���
	glEnable(GL_DEPTH_TEST);

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
	float diffuseMaterial[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specularMaterial[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f); // ���淴�䣬���

	///![0]

	texture = Texture::LoadTexture("../Assets/earth.bmp");
	model.Init("../Assets/Sphere.obj"); // Sphere.obj Quad.obj
}

void Draw() {
	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;

	// ����ģ����ͼ����
	glLoadIdentity();

	float currentTime = timeGetTime() / 1000.0f;
	float timeElapse = currentTime - sTimeSinceStartUp;
	sTimeSinceStartUp = currentTime;
	//set up camera
	camera.Update(timeElapse);

	// ����֮ǰ�����ɫ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureID);
	model.Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
}