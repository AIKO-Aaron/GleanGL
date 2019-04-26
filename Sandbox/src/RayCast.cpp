#include "RayCast.h"

SandBox::RayCaster::RayCaster(SandBox::scene s) {
	cameraOut_color = Glean::OpenCL::KernelFunction<cl_float4, cl_float2, cl_float2, cl_mem, cl_int, cl_mem>("assets/opencl/raycast_out.cl", "getColors", 2, new size_t[2]{ SCREEN_WIDTH * PIXEL_ACCURACY, SCREEN_HEIGHT * PIXEL_ACCURACY });

	sceneBuffer = clCreateBuffer(Glean::OpenCL::context, CL_MEM_READ_WRITE, sizeof(SandBox::scene_object) * s.numObjects, NULL, NULL);
	clEnqueueWriteBuffer(cameraOut_color.getQueue(), sceneBuffer, CL_TRUE, 0, sizeof(SandBox::scene_object) * s.numObjects, s.sceneObjects, NULL, NULL, NULL);

	scene = s;
}

void SandBox::RayCaster::render() {
	cameraOut_color(cameraPos, cameraAngle, screenSize, buffer, scene.numObjects, sceneBuffer);
	clEnqueueReadBuffer(cameraOut_color.getQueue(), buffer, CL_TRUE, 0, sizeof(cl_uchar4) * (size_t)(SCREEN_WIDTH * SCREEN_HEIGHT * PIXEL_ACCURACY * PIXEL_ACCURACY), img, NULL, NULL, NULL);
}
