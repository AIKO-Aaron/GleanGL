#include "assets/opencl/trigo.cl"
#include "assets/opencl/objects.cl"

objectIntersection castRay_scene(float4 position, float4 dir, int objectsInScene, global object *scene) {
	float mindist = MAX_DIST;

    objectIntersection intersection;
    intersection.wasHit = false;
    intersection.obj.color = (float4)(1, 0, 0, 0);

    for(int i = 0; i < objectsInScene; i++) {
        object o = scene[i];
        if(o.type == SPHERE) {
            float d1 = calculateIntersectionWithSphere(o.position.xyz, o.position.w, position, dir);
            if(d1 < mindist) {
                mindist = d1;
                intersection.obj = o;
                intersection.wasHit = true;
                intersection.normal = (float4)((d1 * dir + position - o.position).xyz, 0);
            }
        } else if(o.type == PLANE) {
            float d1 = calculateIntersectionWithPlane(o.meta1.xyz, o.position.xyz, position, dir);
            if(d1 < mindist) {
                mindist = d1;
                intersection.obj = o;
                intersection.wasHit = true;
                intersection.normal = -(float4)(o.meta1.xyz, 0);
            }
        } else if(o.type == CUBE) {
            float4 dPoint = calculateIntersectionWithCube(o.position.xyz, o.meta1.xyz, position, dir);
            if(dPoint.x < mindist) {
                mindist = dPoint.x;
                intersection.obj = o;
                intersection.wasHit = true;
                intersection.normal = (float4)(dPoint.yzw, 0);
            }
        } else if(o.type == LIGHT_SPHERE) {
            float d1 = calculateIntersectionWithSphere(o.position.xyz, o.position.w, position, dir);
            if(d1 < mindist) {
                mindist = d1;
                intersection.obj = o;
                intersection.wasHit = false;
                intersection.normal = (float4)((d1 * dir + position - o.position).xyz, 0);
            }
        }
    }

    float t = max(0.0f, mindist);
    intersection.distance = t;
    intersection.position = t * dir + position;
    
	return intersection;
}

objectIntersection castRayWithMultipleReflections(float4 position, float4 dir, int numReflections, int objectsInScene, global object *scene) {
    objectIntersection intersection = castRay_scene(position, dir, objectsInScene, scene); // normal ray

	float4 lastNormal = intersection.normal;
	float4 lastPos = intersection.position;
	float4 lastDir = dir;

	float factor = REFLECT_FACTOR;
	for(int i = 0; i < numReflections; i++) {
		float4 reflectedRay = (float4)(reflect(lastDir.xyz, lastNormal.xyz), 0);
		objectIntersection reflection = castRay_scene(lastPos + reflectedRay, reflectedRay, objectsInScene, scene); // reflection

		if(reflection.distance >= MAX_REFL_DIST) break;

		float amountOfNewCol = factor * (1.0f - reflection.distance / MAX_REFL_DIST);
		intersection.obj.color = (1.0f - amountOfNewCol) * intersection.obj.color + amountOfNewCol * reflection.obj.color;

		factor *= REFLECT_FACTOR;
		lastDir = reflectedRay; // This is the new ray
		lastPos = reflection.position; // The new start position is the intersection point
		lastNormal = reflection.normal; // The new Normal is the normal of the reflection point
	}

	return intersection;
}