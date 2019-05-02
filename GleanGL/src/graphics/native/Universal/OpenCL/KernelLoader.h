#pragma once
#include "GleanCL.h"

namespace Glean {
    namespace OpenCL {

        extern cl_context context;
		extern cl_device_id defaultDevice;
		extern void initContext();

        template<typename ...T>
        class KernelFunction {
            private:
				cl_program program;
				cl_kernel kernelFunction;
				cl_command_queue queue;

				int num_dimensions = 0;
				const size_t* dimensions = nullptr;

            public:
				KernelFunction() { if (!context) initContext(); }

				KernelFunction(const char* filePath, const char* funcName, int n, const size_t *dim) {
					if (context == nullptr) Glean::OpenCL::initContext();

					num_dimensions = n;
					dimensions = dim;

					Glean::util::FileData d = Glean::util::readWithProcessing(filePath);
					
					printf("%s", d.data);

					program = clCreateProgramWithSource(context, 1, (const char**)& d.data, NULL, NULL);
					cl_int buildError = clBuildProgram(program, 1, &defaultDevice, "", NULL, NULL);

					if (buildError != CL_SUCCESS) {
						printf("[GLEAN][ERROR] Couldn't compile OpenCL program: \n");
						size_t len = 0;
						clGetProgramBuildInfo(program, defaultDevice, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
						char* errorLog = new char[len + 1];
						errorLog[len] = 0;
						clGetProgramBuildInfo(program, defaultDevice, CL_PROGRAM_BUILD_LOG, len, errorLog, NULL);
						printf("[GLEAN][ERROR] %s\n", errorLog);
						delete[] errorLog;
					}

					queue = clCreateCommandQueue(context, defaultDevice, 0, NULL);

					kernelFunction = clCreateKernel(program, funcName, &buildError);
					if (buildError != CL_SUCCESS) printf("[GLEAN][ERROR] Error getting kernel function: %d\n", buildError);
				}

				template<int index, typename A, typename...S>
				inline void setArgs(A a, S... args) {
					cl_int err = clSetKernelArg(kernelFunction, index, sizeof(a), &a);
					if (err != CL_SUCCESS) printf("[GLEAN][ERROR] OpenCL encountered the error %d during clSetKernelArg\n", err);

					setArgs<index + 1, S...>(args...);
				}

				template<int index, typename A>
				inline void setArgs(A a) {
					cl_int err = clSetKernelArg(kernelFunction, index, sizeof(a), &a);
					if (err != CL_SUCCESS) printf("[GLEAN][ERROR] OpenCL encountered the error %d during clSetKernelArg\n", err);
				}
            
                inline void operator()(T... args) {
                    setArgs<0, T...>(args...);
                
                    cl_event evt;
                    clEnqueueNDRangeKernel(queue, kernelFunction, num_dimensions, NULL, dimensions, NULL, NULL, NULL, &evt);
                    clWaitForEvents(1, &evt);
                }

				inline cl_command_queue getQueue() { return queue; }
        };

    }
}
