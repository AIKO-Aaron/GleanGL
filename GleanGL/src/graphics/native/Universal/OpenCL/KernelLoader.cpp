#include "KernelLoader.h"

cl_context Glean::OpenCL::context = nullptr;
cl_device_id Glean::OpenCL::defaultDevice = nullptr;

static void __stdcall onError(const char* errInfo, const void* privateInfo, size_t byteCount, void* userInfo) {

}

void Glean::OpenCL::initContext() {
	cl_platform_id platform;
	cl_device_id device = Glean::OpenCL::defaultDevice;
	clGetPlatformIDs(1, &platform, NULL);

	if (device == nullptr) {
		clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
		Glean::OpenCL::defaultDevice = device;
	}

	cl_context_properties* props = new cl_context_properties[3]{
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform, (cl_context_properties)0
	};

	Glean::OpenCL::context = clCreateContext(props, 1, &device, onError, NULL, NULL);
}