#pragma once

#include <GL/glew.h>
#include <vector>

class Swb_Model
{
public:
	Swb_Model();
	std::vector<std::vector<GLfloat>>vSets;//��Ŷ���(x,y,z)����
	std::vector<std::vector<GLint>>fSets;//������������������
};


