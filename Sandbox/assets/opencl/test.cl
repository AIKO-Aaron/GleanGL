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
#define FOV (PI / 4.0f)
#define MAX_DIST 200.0f

#define MAX_REFL_DIST 8.0f
#define MAX_REFL_REFL_DIST 4.0f

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>=0?(a):-(a))

typedef enum {
    SPHERE,
    PLANE
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

float3 reflect(float3 direction, float3 normal) { // Reflect a ray off a (tangent-) plane with normal
    float3 d = normalize(direction);
    float3 n = normalize(normal);
    
    float3 projectionOnNormal = n * dot(d, n);
    float3 newPoint = d - 2.0f * projectionOnNormal;
    return newPoint;
}

objectIntersection castRay(float4 position, float4 dir) {
	float mindist = MAX_DIST + 1.0f;

    objectIntersection intersection;
    intersection.wasHit = false;
    
#define NUM_SPHERES 4
	// For each sphere, triangle etc, calculate min distance
    float4 spheres[NUM_SPHERES];
    spheres[0] = (float4)(0, 0, 0, 1);
    spheres[1] = (float4)(4, 0, 0, 1);
    spheres[2] = (float4)(4, -4, 0, 1);
    spheres[3] = (float4)(4, 0, 5, 2);

    for(int i = 0; i < NUM_SPHERES; i++) {
        float d1 = calculateIntersectionWithSphere(spheres[i].xyz, spheres[i].w, position, dir);
        if(d1 < mindist) {
            mindist = d1;
            intersection.obj.type = SPHERE;
            intersection.obj.color = i == 0 ? (float4)(1, 0, 1, 1) : i == 1 ? (float4)(1, 0, 0, 1) : i == 2 ? (float4)(0, 0, 1, 1) : (float4)(1, 1, 1, 1);
            intersection.wasHit = true;
            intersection.normal = (float4)((d1 * dir + position - spheres[i]).xyz, 0);
        }
    }
    
    float3 planeNormal = (float3)(0, 1, 0);
    float3 planePoint = (float3)(0, 2, 0);
    float d1 = calculateIntersectionWithPlane(planeNormal, planePoint, position, dir);
    if(d1 < mindist) {
        mindist = d1;
        intersection.obj.type = PLANE;
        intersection.obj.color = (float4) (0.8, 0.5, 0.5, 1); // Color of plane
        intersection.wasHit = true;
        intersection.normal = (float4)(planeNormal, 0);
    }

    float t = max(0.0f, mindist);
    intersection.distance = t;
    intersection.position = t * dir + position;
    
	return intersection;
}

objectIntersection castRayWithReflections(float4 position, float4 dir) {
    objectIntersection intersection = castRay(position, dir); // normal ray
    
    float4 reflected = (float4)(reflect(dir.xyz, intersection.normal.xyz), 0);
    objectIntersection reflection = castRay(intersection.position + reflected, reflected); // reflection
    
    if(reflection.wasHit && reflection.distance < MAX_REFL_DIST) {
        float4 reflected2 = (float4)(reflect(reflected.xyz, reflection.normal.xyz), 0);
        objectIntersection reflection2 = castRay(reflection.position + reflected2, reflected2); // reflection
        reflection2.wasHit = false; // Disable this line to enable reflections in reflections
        if(reflection2.wasHit && reflection2.distance < MAX_REFL_REFL_DIST) {
            float amountOfReflCol = 1.0f - reflection.distance / MAX_REFL_DIST;
            float amountOfReflCol2 = 1.0f - reflection2.distance / MAX_REFL_DIST;
            intersection.obj.color = (1.0f - amountOfReflCol - amountOfReflCol2) * intersection.obj.color + amountOfReflCol2 * reflection2.obj.color + amountOfReflCol * reflection.obj.color;
        } else {
            float amountOfReflCol = 1.0f - reflection.distance / MAX_REFL_DIST;
            intersection.obj.color = (1.0f - amountOfReflCol) * intersection.obj.color + amountOfReflCol * reflection.obj.color;
        }
    }
    
    return intersection;
}

#define ANTI_ALIAS_SAMPLES 3

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
            
            
            objectIntersection intersection = castRayWithReflections(cameraPos, rotated);
            
            float brightness = intersection.wasHit ? (1.0f - intersection.distance / MAX_DIST) : 0.0f;
            totalBrightness += brightness;
            
            r += (intersection.obj.color.x * brightness);
            g += (intersection.obj.color.y * brightness);
            b += (intersection.obj.color.z * brightness);
        }
    }
    
    if(totalBrightness == 0) colorOut[x + y * (int) screenSize.x] = (uchar4) (255, 0, 0, 0);
    else colorOut[x + y * (int) screenSize.x] = (uchar4) (255, (uchar) (255.0f * r / totalBrightness), (uchar) (255.0f * g / totalBrightness), (uchar) (255.0f * b / totalBrightness));
}
