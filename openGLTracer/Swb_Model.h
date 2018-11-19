#pragma once

#include <GL/glew.h>
#include <vector>

class Swb_Model
{
public:
	Swb_Model();
	std::vector<std::vector<GLfloat>>vSets;//存放顶点(x,y,z)坐标
	std::vector<std::vector<GLint>>fSets;//存放面的三个顶点索引
};


