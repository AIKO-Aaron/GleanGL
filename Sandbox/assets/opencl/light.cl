#include "assets/opencl/raycast.cl"

#define AMBIENT_LIGHT 0.01f

typedef struct __attribute__ ((packed)) {
    float4 position; // x, y, z; if w == 0 then dir else pos
    float4 color;
} light;


float calculateBrightness(float4 position, float4 normal, int objectsInScene, global object *scene, int lightsInScene, global light *lights) {
    float brightness = 0.0f;
    
    for(int i = 0; i < lightsInScene; i++) {
        light l = lights[i];

        float4 dir;
        if(l.position.w == 0) dir = -l.position;
        else dir = l.position - position;
        dir.w = 0;

        dir = normalize(dir);

        objectIntersection lightBlocker = castRay_scene(position + 0.01f * dir, dir, objectsInScene, scene);
        if(lightBlocker.obj.type != LIGHT_SPHERE) {
            // No light
            brightness += AMBIENT_LIGHT; // ambient light
        } else {
            brightness += max(0, dot(dir, normalize(normal))) * (1.0f-AMBIENT_LIGHT) + AMBIENT_LIGHT;
        }
    }

    return min(brightness, 1);
}


objectIntersection castRayWithLight(float4 position, float4 dir, int numReflections, int objectsInScene, global object *scene, int lightsInScene, global light *lights) {
    objectIntersection intersection = castRay_scene(position, dir, objectsInScene, scene); // normal ray

	if(!intersection.wasHit || intersection.obj.type == LIGHT_SPHERE) return intersection; // Don't do anything if we didn't hit anything or we hit a light sphere (No reflections on light spheres)
	
    float b = calculateBrightness(intersection.position, intersection.normal, objectsInScene, scene, lightsInScene, lights);
    intersection.obj.color *= b;

	float4 lastNormal = intersection.normal;
	float4 lastPos = intersection.position;
	float4 lastDir = dir;

	float factor = REFLECT_FACTOR;
	for(int i = 0; i < numReflections; i++) {
		float4 reflectedRay = (float4)(reflect(lastDir.xyz, lastNormal.xyz), 0);
		objectIntersection reflection = castRay_scene(lastPos + reflectedRay, reflectedRay, objectsInScene, scene); // reflection

		if(reflection.distance >= MAX_REFL_DIST || !reflection.wasHit || reflection.obj.type == LIGHT_SPHERE) break;

		float amountOfNewCol = factor * (1.0f - reflection.distance / MAX_REFL_DIST);

        float b1 = calculateBrightness(reflection.position, reflection.normal, objectsInScene, scene, lightsInScene, lights);
        reflection.obj.color *= b1;

		intersection.obj.color = (1.0f - amountOfNewCol) * intersection.obj.color + amountOfNewCol * reflection.obj.color;

		factor *= REFLECT_FACTOR;
		lastDir = reflectedRay; // This is the new ray
		lastPos = reflection.position; // The new start position is the intersection point
		lastNormal = reflection.normal; // The new Normal is the normal of the reflection point
	}

	return intersection;
}
