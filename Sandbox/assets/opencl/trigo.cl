#include "assets/opencl/definitions.cl"

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

float calculateIntersectionWithPlane(float3 normal, float3 pointOnPlane, float4 p, float4 v) {
    // Calculate point at which (p+t*v) * normal == 0
    if(normal.x * v.x + normal.y * v.y + normal.z * v.z == 0) return MAX_DIST; // Same direction?
    float t = -dot(normal, p.xyz - pointOnPlane) / dot(normal, v.xyz);
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

float calculateIntersectionWithCameraPlane(float3 cameraPos, float2 cameraRectSize, float3 normal, float4 p, float4 v) {
    if(normal.x * v.x + normal.y * v.y + normal.z * v.z == 0) return MAX_DIST; // Same direction?
    float t = -dot(normal, p.xyz - cameraPos) / dot(normal, v.xyz);
    if(t < 0) return MAX_DIST;
    // Check if in bounds...
    float4 intersectionPoint = t * v + p;
    
    float y = intersectionPoint.y - cameraPos.y;
    float x = sqrt(sq(intersectionPoint.x - cameraPos.x) + sq(intersectionPoint.z - cameraPos.z));
    
    if(x < cameraRectSize.x && y > 0 && y < cameraRectSize.y) { // But what about x > 0?
        return t;
    }

    return MAX_DIST;
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
