#include "objmodel.h"
#include "utils.h"
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <GL/GL.h>

void ObjModel::Init(const char*objModel)
{
	struct FloatData
	{
		float v[3];
	};

	struct VerticeDefine
	{
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};
	std::vector<FloatData> positions,texcoords,normals;
	std::vector<VerticeDefine> vertexes;//unique vertex, ȥ��
	std::vector<int> indexes;//

	unsigned char*fileContent = LoadFileContent(objModel);
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine)>0)
		{
			if (szOneLine[0]=='v')
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1]=='t')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					//printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
					texcoords.push_back(floatData);
				}
				else if (szOneLine[1]=='n')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					//printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					//printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);

				}
			}
			else if (szOneLine[0]=='f')
			{
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;//
				std::string vertexStr;// 1/1/1
				for (int i=0;i<3;i++)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VerticeDefine vd; // 1/1/1
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					//printf("%d,%d,%d\n",vd.posIndex,vd.texcoordIndex,vd.normalIndex);
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j=0;j<nCurrentVertexCount;++j)
					{
						// ȥ�ع��ܣ�������ʾ��2/2/2 ���ظ���3/3/3 Ҳ���ظ��������ܹ������ĵ㹲�� 4 ����
						// 1/1/1 2/2/2 3/3/3 4/4/4 
						//f 1/1/1 2/2/2 3/3/3
						//f 3/3/3 2/2/2 4/4/4
						if (vertexes[j].posIndex==vd.posIndex&&
							vertexes[j].normalIndex==vd.normalIndex&&
							vertexes[j].texcoordIndex==vd.texcoordIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex==-1)
					{
						// �� 6 ���㣬������Щ�������ظ�
						//f 1/1/1 2/2/2 3/3/3
						//f 3/3/3 2/2/2 4/4/4

						// ʵ����ֻ��洢 1/1/1 2/2/2 3/3/3 4/4/4 ���ĸ���
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}

					// �� 6 ���㣬������Щ�������ظ�
					//f 1/1/1 2/2/2 3/3/3
					//f 3/3/3 2/2/2 4/4/4
					indexes.push_back(nCurrentVertexIndex);
				}
				//printf("face : %s\n",szOneLine);
			}
		}
	}
	printf("unique vertex count %u index count %u\n",vertexes.size(),indexes.size());

	// ��ʶ�ܹ��ж��ٸ��������
	mIndexCount = (int)indexes.size();
	mIndices = new int[mIndexCount];
	for (int i = 0; i < mIndexCount; ++i) {
		mIndices[i] = indexes[i];
		printf("%d ", mIndices[i]); // 1 2 3 3 2 4 <-> 0 1 2 2 1 3
	}

	int vertexCount = (int)vertexes.size(); // vertexes -- 1/1/1, vertexes ��ȥ�غ�Ķ�һ�޶���3Ԫ��
	mVertexes = new VertexData[vertexCount];

	// �� 6 ���㣬������Щ�������ظ�
	//f 1/1/1 2/2/2 3/3/3
	//f 3/3/3 2/2/2 4/4/4

	// ʵ����ֻ��洢 1/1/1 2/2/2 3/3/3 4/4/4 ���ĸ��������
	for (int i = 0; i < vertexCount; ++i) {
		memcpy(mVertexes[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].texcoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}

	delete fileContent;
}

void ObjModel::Draw()
{
	glDisable(GL_CULL_FACE); 

	// �߿�ģʽ
	glPolygonMode(GL_FRONT_AND_BACK /*GL_FRONT*/, GL_LINE);

	// ������ʹ�� push �� pop Matrix ��Ϊ�˲�Ӱ������ľ���
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mIndexCount; ++i) {
		//glVertex3f(mVertexes[mIndices[i]].position[0],
		//	mVertexes[mIndices[i]].position[1],
		//	mVertexes[mIndices[i]].position[2]);

		// ����ʹ��������ʽ
		glTexCoord2fv(mVertexes[mIndices[i]].texcoord);
		glNormal3fv(mVertexes[mIndices[i]].normal);
		glVertex3fv(mVertexes[mIndices[i]].position);
	}
	glEnd();
	glPopMatrix();
}