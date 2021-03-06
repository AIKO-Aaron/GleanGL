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

#define MIN_STEP (0.02f)
#define PI (3.14159265358979323f)
#define FOV (PI / 4.0f)
#define MAX_DIST (200.0f)

#define MAX_REFL_DIST (8.0f)
#define REFLECT_FACTOR (0.4f)

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>=0?(a):-(a))

typedef enum {
    SPHERE,
    PLANE,
	CUBE,
	LIGHT_SPHERE
} objectType;

typedef struct {
  // TODO
    objectType type;
    float4 color;
} object;

typedef struct {
    float4 position; // Position of intersection
    float4 normal;
    float distance;
    bool wasHit;
    object obj;
    
} objectIntersection;

float calculateIntersectionWithSphere(float3 m, float r, float4 p, float4 v) {
    float3 dist = p.xyz - m;
    
    float a = v.x * v.x + v.y * v.y + v.z * v.z;
    float b = 2.0f * (v.x * dist.x + v.y * dist.y + v.z * dist.z);
    float c = m.x * m.x + m.y * m.y + m.z * m.z + p.x * p.x + p.y * p.y + p.z * p.z - 2.0f * (m.x * p.x + m.y * p.y + m.z * p.z) - r * r;
    
    float diskriminante = b * b - 4.0 * a * c;
    if(diskriminante < 0) return MAX_DIST; // Not hit... Ray will never hit this sphere
    
    float t1 = (-b + sqrt(diskriminante)) / (2.0f * a);
    float t2 = (-b - sqrt(diskriminante)) / (2.0f * a);

    if(t1 < 0 && t2 < 0) return MAX_DIST; // Behind us... ignore

    return min(t1, t2); //(float4)(0, 0, 0, 0);
}

float calculateIntersectionWithPlane(float3 normal, float3 pointOnSphere, float4 p, float4 v) {
    // Calculate point at which (p+t*v) * normal == 0
    if(normal.x * v.x + normal.y * v.y + normal.z * v.z == 0) return MAX_DIST; // Same direction?
    float t = -dot(normal, p.xyz - pointOnSphere) / dot(normal, v.xyz);
    if(t < 0) return MAX_DIST;
    return min(t, MAX_DIST);
}


#define IN_RANGE(a) ((a)>0?(min(a, MAX_DIST)):MAX_DIST)

#define HITS(p, cp, cs) ((p).x >= (cp).x && (p).x <= (cp).x + (cs).x && (p).y >= (cp).y && (p).y <= (cp).y + (cs).y && (p).z >= (cp).z && (p).z <= (cp).z + (cs).z)

float4 calculateIntersectionWithCube(float3 cubePos, float3 cubeSize, float4 p, float4 v) {
	float t1 = IN_RANGE((cubePos.x - p.x) / v.x);
	float t2 = IN_RANGE((cubePos.x + cubeSize.x - p.x) / v.x);
	float t3 = IN_RANGE((cubePos.y - p.y) / v.y);
	float t4 = IN_RANGE((cubePos.y + cubeSize.y - p.y) / v.y);
	float t5 = IN_RANGE((cubePos.z - p.z) / v.z);
	float t6 = IN_RANGE((cubePos.z + cubeSize.z - p.z) / v.z);

	if(!HITS(p + (t1+0.01f) * v, cubePos, cubeSize)) t1 = MAX_DIST;
	if(!HITS(p + (t2+0.01f) * v, cubePos, cubeSize)) t2 = MAX_DIST;
	if(!HITS(p + (t3+0.01f) * v, cubePos, cubeSize)) t3 = MAX_DIST;
	if(!HITS(p + (t4+0.01f) * v, cubePos, cubeSize)) t4 = MAX_DIST;
	if(!HITS(p + (t5+0.01f) * v, cubePos, cubeSize)) t5 = MAX_DIST;
	if(!HITS(p + (t6+0.01f) * v, cubePos, cubeSize)) t6 = MAX_DIST;

	float minVal = t1;
	float3 normalVec = (float3)(-1, 0, 0);

	if(t2 < minVal) {
		minVal = t2;
		normalVec = (float3)(1, 0, 0);
	}
	if(t3 < minVal) {
		minVal = t3;
		normalVec = (float3)(0, -1, 0);
	}
	if(t4 < minVal) {
		minVal = t4;
		normalVec = (float3)(0, 1, 0);
	}
	if(t5 < minVal) {
		minVal = t5;
		normalVec = (float3)(0, 0, -1);
	}
	if(t6 < minVal) {
		minVal = t6;
		normalVec = (float3)(0, 0, 1);
	}

	return (float4)(minVal, normalVec);
}

float3 reflect(float3 direction, float3 normal) { // Reflect a ray off a (tangent-) plane with normal
    float3 d = normalize(direction);
    float3 n = normalize(normal);
    
    float3 projectionOnNormal = n * dot(d, n);
	//if(length(projectionOnNormal) < 1) projectionOnNormal = (d-n) / 2.0f;
	//if(length(projectionOnNormal) < 1) projectionOnNormal = normalize(projectionOnNormal);
    float3 newPoint = d - 2.0f * projectionOnNormal;
    return newPoint;
}

float3 refract(float3 direction, float3 normal) {
	float3 d = normalize(direction);
    float3 n = normalize(normal);
	float3 n2 = cross(cross(d, n), n);

	float3 projectionOnNormal = n2 * dot(d, n2); // length == sin(alpha)
	float sinBeta = length(projectionOnNormal) * 1.5f;
	if(sinBeta < -1 || sinBeta > 1) return (float3)(0, 0, 0);

	float beta = asin(sinBeta);
	float3 v = d + normalize(projectionOnNormal) * sinBeta;

	return v;
}

objectIntersection castRay(float4 position, float4 dir) {
	float mindist = MAX_DIST;

    objectIntersection intersection;
    intersection.wasHit = false;
    intersection.obj.color = (float4)(1, 0, 0, 0);

#define NUM_SPHERES 3
	// For each sphere, triangle etc, calculate min distance
    float4 spheres[NUM_SPHERES];
    spheres[0] = (float4)(0, 0, 0, 1);
    spheres[1] = (float4)(4, 0, 0, 1);
    spheres[2] = (float4)(4, -4, 0, 1);
    //spheres[3] = (float4)(4, 0, 5, 2);

    for(int i = 0; i < NUM_SPHERES; i++) {
        float d1 = calculateIntersectionWithSphere(spheres[i].xyz, spheres[i].w, position, dir);
        if(d1 < mindist) {
            mindist = d1;
            intersection.obj.type = SPHERE;
            intersection.obj.color = i == 0 ? (float4)(1, 0, 1, 0) : i == 1 ? (float4)(1, 0, 0, 0) : i == 2 ? (float4)(0, 0, 1, 0) : (float4)(1, 1, 1, 0);
            intersection.wasHit = true;
            intersection.normal = (float4)((d1 * dir + position - spheres[i]).xyz, 0);
        }
    }
    

	// Planes
    float3 planeNormal = (float3)(0, 1, 0);
    float3 planePoint = (float3)(0, 2, 0);
    float d1 = calculateIntersectionWithPlane(planeNormal, planePoint, position, dir);
    if(d1 < mindist) {
        mindist = d1;
        intersection.obj.type = PLANE;
        intersection.obj.color = (float4) (0.8, 0.5, 0.5, 0); // Color of plane
        intersection.wasHit = true;
        intersection.normal = (float4)(planeNormal, 0);
    }


	// Cubes
	float3 cubePos = (float3)(0, -2, 1);
	float3 cubeSize = (float3)(4, 1, 1);
	float4 dPoint = calculateIntersectionWithCube(cubePos, cubeSize, position, dir);
    if(dPoint.x < mindist) {
        mindist = dPoint.x;
        intersection.obj.type = CUBE;
        intersection.obj.color = (float4) (1, 1, 1, 0); // Color of cube
        intersection.wasHit = true;
        intersection.normal = (float4)(dPoint.yzw, 0);
    }

	// Light sources (spheres)
	float l1 = calculateIntersectionWithSphere((float3)(0, -5, 0), 0.1, position, dir);
	if(l1 < mindist) {
		mindist = l1;
		intersection.obj.type = LIGHT_SPHERE;
		intersection.obj.color = (float4)(0, 0, 0, 1);
		intersection.wasHit = true;
        intersection.normal = (float4)((l1 * dir + position).xyz - (float3)(0, -5, 0), 0);
	}

    float t = max(0.0f, mindist);
    intersection.distance = t;
    intersection.position = t * dir + position;
    
	return intersection;
}

objectIntersection castRayWithMultipleReflections(float4 position, float4 dir, int numReflections) {
    objectIntersection intersection = castRay(position, dir); // normal ray

	float4 lastNormal = intersection.normal;
	float4 lastPos = intersection.position;
	float4 lastDir = dir;

	float factor = REFLECT_FACTOR;
	for(int i = 0; i < numReflections; i++) {
		float4 reflectedRay = (float4)(reflect(lastDir.xyz, lastNormal.xyz), 0);
		objectIntersection reflection = castRay(lastPos + reflectedRay, reflectedRay); // reflection

		if(reflection.distance >= MAX_REFL_DIST) break;

		float amountOfNewCol = factor * (1.0f - reflection.distance / MAX_REFL_DIST);
		intersection.obj.color = (1.0f - amountOfNewCol) * intersection.obj.color + amountOfNewCol * reflection.obj.color;

		// Set stuff up for next iteration
		factor *= REFLECT_FACTOR;
		lastDir = reflectedRay; // This is the new ray
		lastPos = reflection.position; // The new start position is the intersection point
		lastNormal = reflection.normal; // The new Normal is the normal of the reflection point
	}

	/**
	if(intersection.obj.type == SPHERE) {
		float4 refractedRay = (float4) (refract(lastDir.xyz, lastNormal.xyz), 0);
		objectIntersection outPoint = castRay(lastPos + refractedRay, refractedRay); // refraction

		float4 refractedRay2 = (float4) (refract(refractedRay.xyz, outPoint.normal.xyz), 0);
		objectIntersection refraction = castRay(outPoint.position + refractedRay2, refractedRay2); // refraction
		intersection.obj.color = refraction.obj.color;
	}*/


	return intersection;
}

#define ANTI_ALIAS_SAMPLES 5

kernel void getOutput(float4 cameraPos, float2 cameraAngle, float2 screenSize, global uchar4 *colorOut) {
	size_t x = get_global_id(0); // The coordinates on screen... team.
	size_t y = get_global_id(1);
	
    float totalBrightness = 0;
    float r = 0;
    float g = 0;
    float b = 0;
    
    for(int i = 0; i < ANTI_ALIAS_SAMPLES; i++) {
        for(int j = 0; j < ANTI_ALIAS_SAMPLES; j++) {
            float x_off = (float)(i - ANTI_ALIAS_SAMPLES / 2) / (float) ANTI_ALIAS_SAMPLES;
            float y_off = (float)(j - ANTI_ALIAS_SAMPLES / 2) / (float) ANTI_ALIAS_SAMPLES;
     
            float phi = atan(((float) (x + x_off) / screenSize.x - 0.5f) * FOV) + cameraAngle.x;
            float theta = (((float) (y + y_off) / screenSize.y - 0.5f) * FOV) + cameraAngle.y;
            theta *= screenSize.y / screenSize.x;
            
            float4 rotated = (float4)(
                                      cos(theta) * sin(phi),
                                      sin(theta),
                                      cos(theta) * cos(phi), 0);
            
            
            //objectIntersection intersection = castRayWithReflections(cameraPos, rotated);
            objectIntersection intersection = castRayWithMultipleReflections(cameraPos, rotated, 5);
            
			float brightness = intersection.wasHit ? (1.0f - intersection.distance / MAX_DIST) : 0.0f;
			brightness *= (intersection.obj.color.w + 0.2f);
            totalBrightness += brightness;
            
            r += (intersection.obj.color.x * brightness);
            g += (intersection.obj.color.y * brightness);
            b += (intersection.obj.color.z * brightness);
        }
    }
    
    if(totalBrightness == 0) colorOut[x + y * (int) screenSize.x] = (uchar4) (255, 0, 0, 0);
    else colorOut[x + y * (int) screenSize.x] = (uchar4) (255, (uchar) (255.0f * r / totalBrightness), (uchar) (255.0f * g / totalBrightness), (uchar) (255.0f * b / totalBrightness));
}
