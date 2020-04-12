#include "texture.h"
#include "utils.h"

// ��ͨ�������������ͼ��
// Simple OpenGL Image Library -- SOIL
unsigned char* DecodeBMP(unsigned char *bmpFileData, int &width, int &height) {
	if (bmpFileData == nullptr) {
		return nullptr;
	}

	if (0x4D42 == *((unsigned short*)bmpFileData)) {
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));

		unsigned char *pixelData = bmpFileData + pixelDataOffset;

		// bgr bgr bgr ...
		// -> rgb rgb rgb ...
		for (int i = 0; i < width*height * 3; i += 3) {
			unsigned char tmp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = tmp;
		}

		return pixelData;
	}
	else {
		return nullptr;
	}
}

void Texture::Init(const char *file) {
	// 1. load image file from disk to memory
	unsigned char *imageFileContext = LoadFileContent(file);
	
	// 2. decode image
	int width = 0, height = 0;
	unsigned char *pixelData = DecodeBMP(imageFileContext, width, height);

	// 3. generate an opengl texture
	// �̶���ϵ�У�OpenGL RC ��ֻ����������
	//	GL_TEXTURE_1D
	//  GL_TEXTURE_2D
	// �� RC �У�ÿ������ֻ��һ����ǰ����

	// Returns n currently unused names for texture objects in the array textureNames. 
	// The names in textureNames are marked as used, but they acquire texture state 
	// and dimensionality (1D or 2D) only when they are first bound.
	glGenTextures(1, &mTextureID);

	// both creates and uses texture objects.
	// When a texture name is initially bound (used with glBindTexture()), a new texture 
	// object is created with default values for the texture image and texture properties.
	// Subsequent calls to glTexImage*(), glTexSubImage*(), glCopyTexImage*(), glCopyTexSubImage*(), 
	// glTexParameter*(), and glPrioritizeTextures() store data in the texture object. 
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	// operation on current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB/*�Դ����ڴ��ʽ*/, width, height, 
		0, GL_RGB/*�ڴ������ݸ�ʽ*/, GL_UNSIGNED_BYTE/*�ڴ�����������*/, pixelData);

	// ��GL_TEXTURE_2D��ǰ��������ΪĬ������
	glBindTexture(GL_TEXTURE_2D, 0);

	delete imageFileContext;
}