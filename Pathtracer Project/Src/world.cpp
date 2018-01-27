#include "world.h"
#include <random>


float World::firstIntersection(Ray& ray)
{
	for(int i=0; i<objectList.size(); i++)
		objectList[i]->intersect(ray);
	return ray.getParameter();
}


Color World::shade_ray(Ray& ray)
{
	const float eps = 1e-5;
	firstIntersection(ray);
	if(ray.didHit()) {
		Color diffuse = Color();
		Material *m = (ray.intersected())->getMaterial();

		if(m->getEmit().b > 0 || m->getEmit().g > 0 || m->getEmit().r > 0)	{
			//cout<<"LIGHT HIT\n";
			return m->getEmit();
		}

		if(ray.getLevel() < 10) {
			Ray reflected = m->getNextRay(ray);
			diffuse = shade_ray(reflected);//*dotProduct(ray.getNormal(), dir);
		}
		//return m->getColor()*diffuse;
		return (ray.intersected()->getColor(ray.getPosition()))*diffuse;


	}
	return background;
}

