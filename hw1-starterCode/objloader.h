#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class OBJloader
{
	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

public:
	bool readOBJfile(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec3>& outNormals);
};

extern OBJloader myOBJ;

bool OBJloader::readOBJfile(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec3>& outNormals)
{
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Cannot open .OBJ file!\n");
		return false;
	}

	while (1)
	{
		char firstWord[100];
		if ((fscanf(file, "%s", firstWord)) == EOF)
			break;

		if (strcmp(firstWord, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(firstWord, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(firstWord, "f") == 0)
		{
			unsigned int vertexIndex[3], normalIndex[3], nothing[3];
			int correctread = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1],  &vertexIndex[2], &normalIndex[2]);
			if (correctread != 6)
			{
				printf("Cannot read faces!\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);	normalIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);	normalIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);	normalIndices.push_back(vertexIndex[2]);
		}
	}

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		glm::vec3 vertex = vertices[vertexIndices[i] - 1];
		outVertices.push_back(vertex);
	}
	for (int i = 0; i < normalIndices.size(); i++)
	{
		glm::vec3 normal = normals[vertexIndices[i] - 1];
		outNormals.push_back(normal);
	}
	return true;
}

#endif