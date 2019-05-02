#include "RayCast.h"

#define MANDELBROT

SandBox::RayCaster::RayCaster(SandBox::scene s) {
	cameraOut_color = Glean::OpenCL::KernelFunction<cl_float4, cl_float2, cl_float2, cl_mem, cl_int, cl_mem, cl_int, cl_mem>("assets/opencl/raycast_out.cl", "getColors", 2, new size_t[2]{ SCREEN_WIDTH * PIXEL_ACCURACY, SCREEN_HEIGHT * PIXEL_ACCURACY });

    mandelbrot = Glean::OpenCL::KernelFunction<cl_float4, cl_float2, cl_mem>("assets/opencl/mandelbrot.cl", "getColors", 2, new size_t[2] { SCREEN_WIDTH * PIXEL_ACCURACY, SCREEN_HEIGHT * PIXEL_ACCURACY });
    
	sceneBuffer = clCreateBuffer(Glean::OpenCL::context, CL_MEM_READ_WRITE, sizeof(SandBox::scene_object) * s.numObjects, NULL, NULL);
	clEnqueueWriteBuffer(cameraOut_color.getQueue(), sceneBuffer, CL_TRUE, 0, sizeof(SandBox::scene_object) * s.numObjects, s.sceneObjects, NULL, NULL, NULL);

	lightsBuffer = clCreateBuffer(Glean::OpenCL::context, CL_MEM_READ_WRITE, sizeof(SandBox::scene_light) * s.numLights, NULL, NULL);
	clEnqueueWriteBuffer(cameraOut_color.getQueue(), lightsBuffer, CL_TRUE, 0, sizeof(SandBox::scene_light) * s.numLights, s.lights, NULL, NULL, NULL);

	scene = s;
}

cl_float4 bounds = { -2, -2, 2, 2 };

void SandBox::RayCaster::render() {
	cameraOut_color(cameraPos, cameraAngle, screenSize, buffer, scene.numObjects, sceneBuffer, scene.numLights, lightsBuffer);
	clEnqueueReadBuffer(cameraOut_color.getQueue(), buffer, CL_TRUE, 0, sizeof(cl_uchar4) * (size_t)(SCREEN_WIDTH * SCREEN_HEIGHT * PIXEL_ACCURACY * PIXEL_ACCURACY), img, NULL, NULL, NULL);

	/*
    bounds.x += 0.003f * fmin(1.0, abs(bounds.z - bounds.x));
    bounds.y += 0.003f * fmin(1.0, abs(bounds.w - bounds.y));
    bounds.z -= 0.002f * fmin(1.0, abs(bounds.z - bounds.x));
    bounds.w -= 0.0021f * fmin(1.0, abs(bounds.w - bounds.y));
    
    mandelbrot(bounds, screenSize, buffer);
    clEnqueueReadBuffer(mandelbrot.getQueue(), buffer, CL_TRUE, 0, sizeof(cl_uchar4) * (size_t)(SCREEN_WIDTH * SCREEN_HEIGHT * PIXEL_ACCURACY * PIXEL_ACCURACY), img, NULL, NULL, NULL);*/
}
