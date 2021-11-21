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





template<typename Shape_a, typename Shape_b>
bool CollisionDetection::GJK<Shape_a, Shape_b>::HandleSimplex()
{
	glm::vec3 ab;
	glm::vec3 a0;
	//glm::vec3 tmp;
	glm::vec3 ac;
	glm::vec3 da;
	glm::vec3 db;
	glm::vec3 dc;
	glm::vec3 d0;

	switch (simplex.length) {
	case 0:
		d = b.centre - a.centre;
		break;
	case 1:
		// flip the direction to get a different arbitary second point
		d *= -1.0f;
		break;
	case 2:
		//vector between a and b
		ab = simplex.b - simplex.a;
		//vector from ab to origin
		a0 = simplex.a * -1.0f;

		// use the triple cross product to get a direction perpendicular to line ab in the direction of the origin
		//tmp = glm::cross(ab, a0);
		//d = glm::cross(tmp, ab);
		d = VectorTripleProduct(ab, a0, ab);
		break;
	case 3:
		ac = simplex.c - simplex.a;
		ab = simplex.b - simplex.a;
		d = glm::cross(ac, ab);

		// ensure it points toward the origin
		a0 = simplex.a * -1.0f;
		if (glm::dot(d, a0) < 0) d *= -1.0f;
		break;
	case 4:
		// calculate edges of interest and the direction to the origin
		da = simplex.d - simplex.a;
		db = simplex.d - simplex.b;
		dc = simplex.d - simplex.c;
		d0 = simplex.d * -1.0f;

		// check triangles abd, bcd, and cad
		glm::vec3 abdNorm = glm::cross(da, db);
		glm::vec3 bcdNorm = glm::cross(db, dc);
		glm::vec3 cadNorm = glm::cross(dc, da);

		if (glm::dot(abdNorm, d0) > 0.0f) {
			// the origin is on the outside of triangle abd
			// removes c
			simplex.Remove(2);
			d = abdNorm;
		}
		else if (glm::dot(bcdNorm, d0) > 0.0f) {
			// the origin is on the outside of triangle bcd
			// removes a
			simplex.Remove(0);
			d = bcdNorm;
		}
		else if (glm::dot(cadNorm, d0) > 0.0f) {
			// the origin is on the outside of triangle cad
			// removes b
			simplex.Remove(1);
			d = cadNorm;
		}
		else {
			// origin is in the simplex
			return true;
		}
		break;
	}
	return false;
}

template<typename Shape_a, typename Shape_b>
CollisionDetection::GJK<Shape_a, Shape_b>::GJK(Shape_a a_, Shape_b b_)
{
	a = a_;
	b = b_;
}

template<typename Shape_a, typename Shape_b>
CollisionDetection::GJK<Shape_a, Shape_b>::~GJK()
{
}

template<typename Shape_a, typename Shape_b>
bool CollisionDetection::GJK<Shape_a, Shape_b>::GJKIntersection()
{
	while (true)
	{
		if (HandleSimplex())
		{
			return true;
		}
		glm::vec3 newVertex = a.Support(d) - b.Support(-d);
		simplex.Add(newVertex);
		if (!(glm::dot(d, newVertex) >= 0))
		{
			return false;
		}
	}
}
#endif