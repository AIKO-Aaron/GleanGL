#include "graphics/native/Universal/OpenCL/KernelLoader.h"
#include "Scene.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define PIXEL_ACCURACY 2 // Like resolution
#define LIGHT_ACCURACY 1 // Affects how many rays for each light

namespace SandBox {
    
	class RayCaster {
	private:
		Glean::OpenCL::KernelFunction<cl_float4, cl_float2, cl_float2, cl_mem, cl_int, cl_mem> cameraOut_color;

		SandBox::scene scene;

		// Out stuff --> color
		cl_float4 cameraPos = { 1, 2, 3, 4 };
		cl_float2 cameraAngle = { 0, 0 };
		cl_float2 screenSize = { SCREEN_WIDTH * PIXEL_ACCURACY, SCREEN_HEIGHT * PIXEL_ACCURACY };
		cl_mem buffer = clCreateBuffer(Glean::OpenCL::context, CL_MEM_READ_WRITE, (size_t)(screenSize.x * screenSize.y) * sizeof(cl_uchar4), NULL, NULL);
		cl_mem sceneBuffer;

	public:
		unsigned char* img = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * 4 * PIXEL_ACCURACY * PIXEL_ACCURACY];
		
		inline void setPosition(Glean::math::Vector<4> pos) { 
			cameraPos.x = pos[0];
			cameraPos.y = pos[1];
			cameraPos.z = pos[2];
			cameraPos.w = pos[3];
		}

		inline void setRotation(Glean::math::Vector<2> ang) {
			cameraAngle.x = ang[0];
			cameraAngle.y = ang[1];
		}

		RayCaster(SandBox::scene s);

		void render();
	};
}