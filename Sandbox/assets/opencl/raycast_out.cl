#include "assets/opencl/light.cl"

kernel void getColors(float4 cameraPos, float2 cameraAngle, float2 screenSize, global uchar4 *colorOut, int objectsInScene, global object *scene, int lightsInScene, global light *lights) {
    size_t x = get_global_id(0); // The coordinates on screen... team.
	size_t y = get_global_id(1);

    size_t index = x + y * (size_t) screenSize.x;

    float phi = atan(((float) x / screenSize.x - 0.5f) * FOV) + cameraAngle.x;
    float theta = (((float) y / screenSize.y - 0.5f) * FOV) + cameraAngle.y;
    theta *= screenSize.y / screenSize.x;

    float4 rotated = (float4)(cos(theta) * sin(phi),
                              sin(theta),
                              cos(theta) * cos(phi), 0);

    //objectIntersection intersection = castRayWithMultipleReflections(cameraPos, rotated, 2, objectsInScene, scene);
    objectIntersection intersection = castRayWithLight(cameraPos, rotated, 2, objectsInScene, scene, lightsInScene, lights);

    float r = intersection.obj.color.x;
    float g = intersection.obj.color.y;
    float b = intersection.obj.color.z;

    if(intersection.wasHit) colorOut[index] = (uchar4)(255, (uchar)(255.0f * r), (uchar)(255.0f * g), (uchar)(255.0f * b));
    else colorOut[index] = (uchar4)(255, 0, 0, 0);
}
