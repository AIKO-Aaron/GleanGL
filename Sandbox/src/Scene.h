#pragma once

#include <vector>
#include "graphics/native/Universal/OpenCL/GleanCL.h"

namespace SandBox {

	enum objectType {
		SPHERE = 0,
		PLANE,
		CUBE,
		LIGHT_SPHERE
	};

#pragma pack(push, 1)
	typedef struct {
		cl_int type;
		cl_float4 color;
		cl_float4 position;
		cl_float4 meta1, meta2;
	} scene_object;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct {
		cl_float4 position;
		cl_float4 color;
	} scene_light;
#pragma pack(pop)

	typedef struct {
		scene_object* sceneObjects;
		int numObjects;
		scene_light* lights;
		int numLights;
	} scene;

	extern scene createScene();
}
