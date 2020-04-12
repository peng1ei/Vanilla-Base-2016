#include "utils.h"
#include <stdio.h>

unsigned char* LoadFileContent(const char *file) {
	unsigned char *fileContext = nullptr;
	FILE *pFile = fopen(file, "rb");
	if (pFile) {
		// read
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0) {
			rewind(0);
			fileContext = new unsigned char[nLen + 1];
			fread(fileContext, sizeof(unsigned char), nLen, pFile);
			fileContext[nLen] = '\0';
		}
		fclose(pFile);
	}

	return fileContext;
}
