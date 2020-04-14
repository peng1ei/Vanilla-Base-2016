#include "skybox.h"

void SkyBox::Init(const char *path) {
	char temp[128] = { 0 };
	strcpy(temp, path);
	strcat(temp, "/front.bmp");
	front = Texture::LoadTexture(temp);

	strcpy(temp, path);
	strcat(temp, "/back.bmp");
	back = Texture::LoadTexture(temp);

	strcpy(temp, path);
	strcat(temp, "/right.bmp");
	right = Texture::LoadTexture(temp);

	strcpy(temp, path);
	strcat(temp, "/left.bmp");
	left = Texture::LoadTexture(temp);

	strcpy(temp, path);
	strcat(temp, "/top.bmp");
	top = Texture::LoadTexture(temp);

	strcpy(temp, path);
	strcat(temp, "/bottom.bmp");
	bottom = Texture::LoadTexture(temp);

	mSkyBox.Init([&]()->void {
		// 只需执行一次
		glColor4ub(255, 255, 255, 255);

		// front
		glBindTexture(GL_TEXTURE_2D, front->mTextureID);
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

		// left
		glBindTexture(GL_TEXTURE_2D, left->mTextureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();

		//right
		glBindTexture(GL_TEXTURE_2D, right->mTextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();

		//top
		glBindTexture(GL_TEXTURE_2D, top->mTextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();

		//bottom
		glBindTexture(GL_TEXTURE_2D, bottom->mTextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glEnd();

		//back
		glBindTexture(GL_TEXTURE_2D, back->mTextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glEnd();

	});
}

void SkyBox::Draw(float cameraX, float cameraY, float cameraZ) {
	glDisable(GL_LIGHTING);

	// 此时天空盒的Depth Buffer中的值全为 1.0，为最远处
	// 后续绘制的物体都会覆盖当前天空盒的像素，即天空盒永远
	// 在最远处
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	// 使天空盒跟着摄像机走
	glTranslatef(cameraX, cameraY, cameraZ);
	mSkyBox.Draw();
	glPopMatrix();
}
