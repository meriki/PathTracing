#ifndef _RENDERENGINE_H_
#define _RENDERENGINE_H_

#include "world.h"
#include "camera.h"

class RenderEngine
{
private:
	World *world;
	Camera *camera;
	const Color trace(const int i, const int j, float epsx=0, float epsy=0);
	bool jittered_supersampling;

public:
	RenderEngine(World *_world, Camera *_camera):
		world(_world), camera(_camera), jittered_supersampling(false) {}
	bool renderLoop();

	void activate_saa() {
		jittered_supersampling = true;
	}
};
#endif
