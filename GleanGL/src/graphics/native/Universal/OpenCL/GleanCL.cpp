#include "GleanCL.h"
#include <vector>

#define DEBUG_CL

#define NUM_ELEMENTS 100

static void onError(const char *errinfo, const void *privateInfo, size_t cb, void *userInfo) {
    
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
    clBuildProgram(program, 1, &selectedDevice, "", NULL, NULL);
    
    cl_command_queue queue = clCreateCommandQueue(context, selectedDevice, 0, NULL);
    
    cl_mem buffer_cl_in  = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * NUM_ELEMENTS, NULL, NULL);
    cl_mem buffer_cl_out = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * NUM_ELEMENTS, NULL, NULL);

    float *elmnts = new float[NUM_ELEMENTS];
    for(int i = 0; i < NUM_ELEMENTS; i++) elmnts[i] = i+1.0;
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
}
