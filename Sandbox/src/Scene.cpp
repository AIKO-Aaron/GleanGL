#include "Scene.h"

SandBox::scene SandBox::createScene() {
	SandBox::scene_object* scene = new SandBox::scene_object[3];

	scene[0].type = SPHERE;
	scene[0].position = {0, 0, 0, 1};
	scene[0].color = { 0, 0, 1, 1 };

	scene[1].type = SPHERE;
	scene[1].position = {4, -4, 0, 1};
	scene[1].color = { 1, 0, 1, 1 };

	scene[2].type = PLANE;
	scene[2].position = { 0, 2, 0, 0 }; // Point on plane
	scene[2].meta1 = { 0, 1, 0, 0 }; // Normal to plane
	scene[2].color = { 0.8, 0.5, 0.5, 0 };

	return { scene, 3 };
}