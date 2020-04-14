#include "skybox.h"

void SkyBox::Init(const char *path) {
	char temp[128] = { 0 };
	strcpy(temp, path);
	strcat(temp, "/front.bmp");
	front = Texture::LoadTexture(temp);
}

void SkyBox::Draw(float cameraX, float cameraY, float cameraZ) {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	// 使天空盒跟着摄像机走
	glTranslatef(cameraX, cameraY, cameraZ);

	glBindTexture(GL_TEXTURE_2D, front->mTextureID);

	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glPopMatrix();
}
