__kernel void test(__global float *in, __global float *out) {
    size_t i = get_global_id(0);
    out[i] = in[i] * in[i] * in[i];
}

kernel void traceTest(float4 position, global float *dataIn, global float4 *colorOut) {
	size_t i = get_global_id(0);
	size_t j = get_global_id(1);

	colorOut[i + j * 50] = (float4)(i + j * 50, 0, 0, 0);
}

// #####################################
// Adapted from ProjectRaycasting...
// #####################################

#define MIN_STEP 0.02f
#define PI 3.14159265358979323f
#define FOV (PI / 2.0f)
#define MAX_DIST 100.0f

#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>=0?(a):-(a))

float minDist(float4 position) {
	float mindist = MAX_DIST;

	// For each sphere, triangle etc, calculate min distance
    float4 spheres[3];
    spheres[0] = (float4)(0, 0, 3, 1);
    spheres[1] = (float4)(4, 0, 3, 1);
    spheres[2] = (float4)(4, 4, 3, 2);
    
    for(int i = 0; i < 3; i++) {
        float d1 = distance(position, (float4)(spheres[i].x, spheres[i].y, spheres[i].z, 1)) - spheres[i].w;
        if(d1 < mindist) mindist = d1;
    }

	return max(0.0, mindist);
}

float rayWalk(float4 direction, float4 position) {
	float distWalked = 0;
    float4 curPos = position;
	while (distWalked < MAX_DIST) {
		float stepSize = minDist(curPos);
        distWalked += stepSize;
        if (stepSize <= MIN_STEP) return min(distWalked, MAX_DIST);
		curPos += direction * stepSize;
	}
	return MAX_DIST;
}

kernel void getOutput(float4 cameraPos, float2 cameraAngle, float2 screenSize, global uchar4 *colorOut) {
	size_t x = get_global_id(0); // The coordinates on screen...
	size_t y = get_global_id(1);
		
	float phi = ((float) x / screenSize.x - 0.5f) * FOV + cameraAngle.x;
    float theta = ((float) y / screenSize.y - 0.5f) * FOV + cameraAngle.y;
    theta *= screenSize.y / screenSize.x;

	float4 rotated = (float4)(
                              cos(theta) * sin(phi),
                              sin(theta),
                              cos(theta) * cos(phi), 0);

    cameraPos.y *= screenSize.y / screenSize.x;
	float wasHit = rayWalk(rotated, cameraPos);

    uchar brightness = 255 - (uchar) (wasHit / MAX_DIST * 255.0f);
	if (wasHit) colorOut[x + y * (int) screenSize.x] = (uchar4) (255, brightness, brightness, brightness);
	else colorOut[x + y * (int) screenSize.x] = (uchar4) (255, 0, 0, 0);
}
