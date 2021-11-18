#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDetection
{
public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection* operator=(const CollisionDetection&) = delete;
	CollisionDetection* operator=(CollisionDetection&&) = delete;

	CollisionDetection() = delete;
	~CollisionDetection();

	static Ray MousePosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);
	static bool RayAABBIntersection(Ray* ray_, BoundingBox* box_);

	
	struct Simplex
	{
		glm::vec3 a, b, c, d;
		int length = 0;
		void Add(glm::vec3 e)
		{
			switch (length)
			{
				case 0:
					a = e;
					length = 1;
					break;
				case 1:
					b = e;
					length = 2;
					break;
				case 2:
					c = e;
					length = 3;
					break;
				case 3:
					d = e;
					length = 4;
					break;
				case 4:
					a = b;
					b = c;
					c = d;
					d = e;
					break;
			}
		}
	};
	//Use with only convex shapes
	template<typename Shape_a, typename SupportMapping_a, typename Shape_b, typename SupportMapping_b>
	static bool GJKIntersection(Shape_a a, SupportMapping_a, Shape_b b, SupportMapping_b); 
	
	static bool HandleSimplex(Simplex s, glm::vec3 d);


};

#endif
