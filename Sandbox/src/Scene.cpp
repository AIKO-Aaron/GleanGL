#include "Scene.h"

SandBox::scene SandBox::createScene() {
	SandBox::scene_object* scene = new SandBox::scene_object[5];

	scene[0].type = SPHERE;
	scene[0].position = {1, -2, 1, 1};
	scene[0].color = { 0, 0, 1, 1 };

	scene[1].type = SPHERE;
	scene[1].position = {4, -4, 0, 1};
	scene[1].color = { 1, 0, 1, 1 };

	scene[2].type = PLANE;
	scene[2].position = { 0, 2, 0, 0 }; // Point on plane
	scene[2].meta1 = { 0, 1, 0, 0 }; // Normal to plane
	scene[2].color = { 0.8f, 0.5f, 0.5f, 0 };

	scene[3].type = CUBE;
	scene[3].position = { 1, -3, 3 };
	scene[3].meta1 = { 1, 1, 1 };
	scene[3].color = { 1, 0, 0, 1 };

	scene[4].type = LIGHT_SPHERE;
	scene[4].position = { 1, -10, 1, 0.5f };

	SandBox::scene_light* lights = new SandBox::scene_light[1];
	lights[0].position = { 1, -10, 1, 1 };

	return { scene, 5, lights, 1 };
}