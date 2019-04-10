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

#define MIN_STEP 2.0f
#define PI 3.14159265358979323f
#define FOV (PI / 2.0f)

float4 rotateX(float angle, float4 vec) {
	float4 r;
	r.x = vec.x; // Stays in place
	r.y = cos(angle) * vec.y + sin(angle) * vec.z;
	r.z = -sin(angle) * vec.y + cos(angle) * vec.z;
	r.w = vec.w;
	return r;
}

float4 rotateY(float angle, float4 vec) {
	float4 r;
	r.x = cos(angle) * vec.x + sin(angle) * vec.z;
	r.y = vec.y;
	r.z = -sin(angle) * vec.x + cos(angle) * vec.z;
	r.w = vec.w;
	return r;
}

float minDist(float4 position) {
	float min = 1000;

	// For each sphere, triangle etc, calculate min distance

	float d1 = distance(position, (float4)(0, 0, 3, 1));
	if (d1 < min) min = d1;

	return min;
}

bool rayWalk(float4 direction, float4 position) {
	float distWalked = 0;
	while (distWalked < 1000) {
		float stepSize = minDist(position);
		if (stepSize < MIN_STEP) return true;
		distWalked += stepSize;
		position += direction * stepSize;
	}
	return false;
}

kernel void getOutput(float4 cameraPos, float2 cameraAngle, float2 screenSize, global float4 *colorOut) {
	size_t x = get_global_id(0); // The coordinates on screen...
	size_t y = get_global_id(1);
	
	float4 rayDir;
	float4 viewDir = (float4) (0, 0, -1, 0);
	
	float phi = ((float) x / screenSize.x - 0.5f) * FOV + cameraAngle.x;
	float theta = ((float) y / screenSize.y - 0.5f) * FOV + cameraAngle.y;

	float4 rotated = rotateX(theta, rotateY(phi, cameraPos));

	bool wasHit = rayWalk(rotated, cameraPos);
	
	if (wasHit) colorOut[x + y * (int) screenSize.x] = (float4) (1, 1, 1, 1);
	else colorOut[x + y * (int) screenSize.x] = (float4) (0, 0, 0, 1);
}