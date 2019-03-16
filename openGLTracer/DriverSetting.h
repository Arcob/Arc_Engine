#pragma once

#include "common.h"
#include "BoxMoverApplication.h"
#define Application BoxMoverApplication

const bool ENABLE_TEST = true;
const bool ENABLE_SHADOW = true;
const bool ENABLE_POST_EFFECT = true;

const GLuint WIDTH = 1024, HEIGHT = 1024;
const GLuint ANTI_AILASING_MULTY_TIME = 1;

const std::string shader_path = "\\shaders";