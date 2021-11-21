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
		void Add(glm::vec3 e);
		//Position of the vertex to be removed
		void Remove(int i);
	};

	template<typename Shape_a, typename Shape_b>
	class GJK
	{
		Simplex simplex;
		glm::vec3 d;
		Shape_a a;
		Shape_b b;
		bool HandleSimplex();

	public:
		GJK(Shape_a, Shape_b);
		~GJK();
		//Use with only convex shapes
		bool GJKIntersection();
	};

	static glm::vec3 VectorTripleProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c);

};

#endif


