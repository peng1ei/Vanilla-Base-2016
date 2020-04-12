#include "texture.h"
#include "utils.h"

void Texture::Init(const char *file) {
	// 1. load image file from disk to memory
	unsigned char *imageFileContext = LoadFileContent(file);
	
	// 2. decode image


	// 3. generate an opengl texture


}