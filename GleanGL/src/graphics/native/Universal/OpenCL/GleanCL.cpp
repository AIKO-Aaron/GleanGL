#include "GleanCL.h"
#include <vector>

#define DEBUG_CL

// #define TEST_A1
// #define TEST_B1

#define NUM_ELEMENTS 10

static void RET_TYPE onError(const char *errinfo, const void *privateInfo, size_t cb, void *userInfo) {
    
}

void testCL() {
    cl_platform_id selectedPlatform;
    clGetPlatformIDs(1, &selectedPlatform, NULL);
    cl_device_id selectedDevice;
    clGetDeviceIDs(selectedPlatform, CL_DEVICE_TYPE_GPU, 1, &selectedDevice, NULL);
    
    cl_context_properties *props = new cl_context_properties[3] {
        CL_CONTEXT_PLATFORM, (cl_context_properties) selectedPlatform, // only config: Which platform...
        (cl_context_properties) 0 // Terminator
    };
    
    cl_context context = clCreateContext(props, 1, &selectedDevice, onError, NULL, NULL);
    
    
    Glean::util::FileData d = Glean::util::readWithProcessing("assets/opencl/test.cl");
    printf("[GLEAN][DEBUG] Compiling CL-Source: \n%s\n", d.data);
    cl_program program = clCreateProgramWithSource(context, 1, (const char**) &d.data, NULL, NULL);
    cl_int buildErr = clBuildProgram(program, 1, &selectedDevice, "", NULL, NULL);
    
	if (buildErr != CL_SUCCESS) {
		printf("[GLEAN][ERROR] Couldn't compile OpenCL program: \n");
		size_t len = 0;
		clGetProgramBuildInfo(program, selectedDevice, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		char *errorLog = new char[len + 1];
		errorLog[len] = 0;
		clGetProgramBuildInfo(program, selectedDevice, CL_PROGRAM_BUILD_LOG, len, errorLog, NULL);
		printf("[GLEAN][ERROR] %s\n", errorLog);
		delete[] errorLog;
	}

    cl_command_queue queue = clCreateCommandQueue(context, selectedDevice, 0, NULL);
    
#ifdef TEST_A1
	// Start first function...

	cl_mem buffer_cl_in  = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * NUM_ELEMENTS, NULL, NULL);
    cl_mem buffer_cl_out = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * NUM_ELEMENTS, NULL, NULL);

    float *elmnts = new float[NUM_ELEMENTS];
    for(int i = 0; i < NUM_ELEMENTS; i++) elmnts[i] = i+1.0f;
    clEnqueueWriteBuffer(queue, buffer_cl_in, CL_TRUE, 0, sizeof(float) * NUM_ELEMENTS, elmnts, NULL, NULL, NULL);
    delete[] elmnts;
    

    cl_kernel function = clCreateKernel(program, "test", NULL);
    clSetKernelArg(function, 0, sizeof(buffer_cl_in), &buffer_cl_in);
    clSetKernelArg(function, 1, sizeof(buffer_cl_out), &buffer_cl_out);
    
    cl_event evt = NULL;
    clEnqueueNDRangeKernel(queue, function, 1, NULL, new size_t[1] { NUM_ELEMENTS }, NULL, NULL, NULL, &evt);
    clWaitForEvents(1, &evt); // Wait for function to finish
    
    float *outputData = new float[NUM_ELEMENTS];
    clEnqueueReadBuffer(queue, buffer_cl_out, CL_TRUE, 0, sizeof(float) * NUM_ELEMENTS, outputData, 0, NULL, NULL);
    
    for(int i = 0; i < NUM_ELEMENTS; i++) {
        printf("Cubes of %3d: %f\n", i+1, outputData[i]);
    }

	clReleaseMemObject(buffer_cl_in);
	clReleaseMemObject(buffer_cl_out);
#endif
	// Start second function...
#ifdef TEST_B1
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 50
#define NUM_PIXELS (SCREEN_WIDTH*SCREEN_HEIGHT)

	cl_int allocErr;
	cl_mem buffer_color_out = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_float4) * NUM_PIXELS, NULL, &allocErr);
	if (allocErr != CL_SUCCESS) printf("Couldn't alloc: %d\n", allocErr);

	cl_mem buffer_data_in = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * 50, NULL, &allocErr);

	cl_kernel traceTest = clCreateKernel(program, "traceTest", NULL);
	clSetKernelArg(traceTest, 0, sizeof(cl_float4), new float[4]{0, 0, 0, 0});
	clSetKernelArg(traceTest, 1, sizeof(buffer_data_in), &buffer_data_in);
	clSetKernelArg(traceTest, 2, sizeof(buffer_color_out), &buffer_color_out);

	clEnqueueNDRangeKernel(queue, traceTest, 2, NULL, new size_t[2]{ SCREEN_WIDTH, SCREEN_HEIGHT }, NULL, NULL, NULL, &evt);
	clWaitForEvents(1, &evt);

	float *colorOut = new float[4 * NUM_PIXELS];
	clEnqueueReadBuffer(queue, buffer_color_out, CL_TRUE, 0, sizeof(cl_float4) * NUM_PIXELS, colorOut, 0, NULL, NULL);

	for (int j = 0; j < SCREEN_HEIGHT; j++) {
		for (int i = 0; i < SCREEN_WIDTH; i++) {
			printf("%04.f, ", colorOut[(i + j * SCREEN_WIDTH) * 4]);
		}
		printf("\n");
	}

	delete[] colorOut;

	clReleaseMemObject(buffer_color_out);
#endif
}

static float* screenSize = new float[2]{ 100, 100 };
static size_t* screenSizet = new size_t[2]{ (size_t)screenSize[0], (size_t) screenSize[1] };

static float* colorData = new float[4 * screenSize[0] * screenSize[1]];

cl_device_id device;
cl_context context;
cl_command_queue queue;

cl_program program;
cl_kernel getOutput;

cl_mem colorOut;
cl_event evt;

void initCL() {
	cl_platform_id selectedPlatform;
	clGetPlatformIDs(1, &selectedPlatform, NULL);
	clGetDeviceIDs(selectedPlatform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

	cl_context_properties *props = new cl_context_properties[3]{
		CL_CONTEXT_PLATFORM, (cl_context_properties)selectedPlatform, // only config: Which platform...
		(cl_context_properties)0 // Terminator
	};

	context = clCreateContext(props, 1, &device, onError, NULL, NULL);


	Glean::util::FileData d = Glean::util::readWithProcessing("assets/opencl/test.cl");
	printf("[GLEAN][DEBUG] Compiling CL-Source: \n%s\n", d.data);
	program = clCreateProgramWithSource(context, 1, (const char**)&d.data, NULL, NULL);
	cl_int buildErr = clBuildProgram(program, 1, &device, "", NULL, NULL);

	if (buildErr != CL_SUCCESS) {
		printf("[GLEAN][ERROR] Couldn't compile OpenCL program: \n");
		size_t len = 0;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		char *errorLog = new char[len + 1];
		errorLog[len] = 0;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, len, errorLog, NULL);
		printf("[GLEAN][ERROR] %s\n", errorLog);
		delete[] errorLog;
	}

	queue = clCreateCommandQueue(context, device, 0, NULL);

	colorOut = clCreateBuffer(context, CL_MEM_READ_WRITE, screenSize[0] * screenSize[1] * sizeof(cl_float4), NULL, NULL);
	getOutput = clCreateKernel(program, "getOutput", NULL);

	clSetKernelArg(getOutput, 2, sizeof(cl_float2), screenSize);
	clSetKernelArg(getOutput, 3, sizeof(colorOut), &colorOut);
}

void testRay(Glean::math::Vector<4> cameraPos, Glean::math::Vector<2> cameraAngles) {
	clSetKernelArg(getOutput, 0, sizeof(cl_float4), &cameraPos[0]);
	clSetKernelArg(getOutput, 1, sizeof(cl_float2), &cameraAngles[0]);

	clEnqueueNDRangeKernel(queue, getOutput, 2, NULL, screenSizet, NULL, NULL, NULL, &evt);
	clWaitForEvents(1, &evt);

	clEnqueueReadBuffer(queue, colorOut, CL_TRUE, 0, sizeof(cl_float4) * screenSize[0] * screenSize[1], colorData, NULL, NULL, NULL);

	std::string output;
	bool toPrint = false;
	for (int i = 0; i < screenSize[1]; i++) {
		for (int j = 0; j < screenSize[0]; j++) {
			if (colorData[(i * (int)screenSize[0] + j) * 4]) {
				output.append("1 ");
				toPrint = true;
			}
			else output.append("0 ");
		}
		output.append("\n");
	}
	output.append("\n");
	if(toPrint) printf("%s", output.data());
}