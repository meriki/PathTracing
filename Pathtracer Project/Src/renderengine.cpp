#include "renderengine.h"
#include <cstdlib>
const Color RenderEngine::trace(const int i, const int j, float epsx, float epsy)
{
	Vector3D ray_dir = camera->get_ray_direction(i, j, epsx, epsy);
	Ray ray(camera->get_position(), ray_dir);
	return world->shade_ray(ray);
}
int nSamples = 1000;
int s = 1;


bool RenderEngine::renderLoop()
{
	static int i = 0;
	const int aa = 4;
	//std::cout<<camera->getHeight()<<std::endl;
	for(int j = 0; j<camera->getHeight(); j++)
	{
		Color color = Color(0);
		if(jittered_supersampling) {
			for (int k = 0; k < aa; k++) {
				for (int l = 0; l < aa; l++) {
					float epsx = (k + 1.0f*rand()/RAND_MAX)/aa;
					float epsy = (l + 1.0f*rand()/RAND_MAX)/aa;
					color = color + trace(i, j, epsx, epsy);
				}
			}
			color = color / (1.0*aa*aa);
			//color.clamp();
		}
		else {
			color = trace(i, j);
			//color.clamp();
		}
        //color.clamp();
		camera->drawPixel(i, j, color, s);
	}

	if(++i == camera->getWidth())
	{
		//scanf("%d", &i);
		i = 0;
		nSamples--;
		s++;
		return nSamples == 0;
	}
	return false;
}
