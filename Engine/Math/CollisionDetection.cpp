#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection() 
{

}

Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_) 
{
	glm::vec4 rayStartNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEndNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_) 
{
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->direction;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;

	float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();

	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(delta, xAxis);
	float dotDir = glm::dot(rayDirection, xAxis);
	if (fabs(dotDir) > 0.001f)
	{
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if(t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else 
	{
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f)
		{
			return false;
		}
	}

	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	dotDelta = glm::dot(delta, yAxis);
	dotDir = glm::dot(rayDirection, yAxis);
	if (fabs(dotDir) > 0.001f)
	{
		float t1 = (dotDelta + boxMin.y) / dotDir;
		float t2 = (dotDelta + boxMax.y) / dotDir;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else
	{
		if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f)
		{
			return false;
		}
	}

	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	dotDelta = glm::dot(delta, zAxis);
	dotDir = glm::dot(rayDirection, zAxis);
	if (fabs(dotDir) > 0.001f)
	{
		float t1 = (dotDelta + boxMin.z) / dotDir;
		float t2 = (dotDelta + boxMax.z) / dotDir;

		if (t1 > t2)
		{
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax)
		{
			tMax = t2;
		}

		if (t1 > tMin)
		{
			tMin = t1;
		}

		if (tMax < tMin)
		{
			return false;
		}
	}
	else
	{
		if (-dotDelta + boxMin.z > 0.0f || -dotDelta + boxMax.z < 0.0f)
		{
			return false;
		}
	}


	ray_->intersectionDist = tMin;
	return true;
}

bool CollisionDetection::RayAABBIntersection(Ray* ray_, BoundingBox* box_)
{
	float tMin = (box_->minVert.x - ray_->origin.x) / ray_->direction.x;
	float tMax = (box_->maxVert.x - ray_->origin.x) / ray_->direction.x;

	if (tMin > tMax) std::swap(tMin, tMax);

	float tyMin = (box_->minVert.y - ray_->origin.y) / ray_->direction.y;
	float tyMax = (box_->maxVert.y - ray_->origin.y) / ray_->direction.y;

	if (tyMin > tyMax) std::swap(tyMin, tyMax);

	if ((tMin > tyMax) || (tyMin > tMax))
		return false;

	if (tyMin > tMin)
		tMin = tyMin;

	if (tyMax < tMax)
		tMax = tyMax;

	float tzMin = (box_->minVert.z - ray_->origin.z) / ray_->direction.z;
	float tzMax = (box_->maxVert.z - ray_->origin.z) / ray_->direction.z;

	if (tzMin > tzMax) std::swap(tzMin, tzMax);

	if ((tMin > tzMax) || (tzMin > tMax))
		return false;

	if (tzMin > tMin)
		tMin = tzMin;

	if (tzMax < tMax)
		tMax = tzMax;

	return true;
}

glm::vec3 CollisionDetection::VectorTripleProduct(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	return glm::cross(a, glm::cross(b, c));
	return (glm::dot(a, c) * b) - (glm::dot(a, b) * c);
}

/*
#define ORIGIN glm::vec3(0.0f,0.0f,0.0f)
template<typename Shape_a, typename SupportMapping_a, typename Shape_b, typename SupportMapping_b>
bool CollisionDetection::GJKIntersection(Shape_a a, SupportMapping_a aS, Shape_b b, SupportMapping_b bS)
{
	glm::vec3 d = glm::normalize(b.center - a.center);
	glm::vec3 A;
	Simplex s;
	s.Add(aS.support(a, d) - bS.support(b, -d));

	d = ORIGIN - s.a;
	while (true)
	{
		A = support(a, b, d);
		if (glm::dot(A, d) < 0)
		{
			return false;
		}
		s.Add(A);
		//if (handleSimplex(s, d))
		//{
		//	return true;
		//}
	}

	
	return false;
}
#undef ORIGIN
*/

void CollisionDetection::Simplex::Add(glm::vec3 e)
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

void CollisionDetection::Simplex::Remove(int i)
{
	switch (i)
	{
	case 0:
		a = b;
		b = c;
		c = d;
		d = glm::vec3(NULL, NULL, NULL);
		length--;
		break;
	case 1:
		b = c;
		c = d;
		d = glm::vec3(NULL, NULL, NULL);
		length--;
		break;
	case 2:
		c = d;
		d = glm::vec3(NULL, NULL, NULL);
		length--;
		break;
	case 3:
		d = glm::vec3(NULL, NULL, NULL);
		length--;
	}
}

template<typename Shape_a, typename Shape_b>
bool CollisionDetection::GJK<Shape_a, Shape_b>::HandleSimplex()
{
	switch (simplex.length) {
	case 0:
		d = b.centre - a.centre;
		break;
	case 1:
		// flip the direction
		d *= -1;
		break;
	case 2:
		// line ab is the line formed by the first two vertices
		glm::vec3 ab = simplex.b - simplex.a;
		// line a0 is the line from the first vertex to the origin
		glm::vec3 a0 = simplex.a * -1;

		// use the triple-cross-product to calculate a direction perpendicular
		// to line ab in the direction of the origin
		glm::vec3 tmp = VectorTripleProduct(ab, a0, glm::vec3());
		d = VectorTripleProduct(tmp, ab, d);
		break;
	case 3:
		glm::vec3 ac = simplex.c - simplex.a;
		glm::vec3 ab = simplex.b - simplex.a;
		d = VectorTripleProduct(ac, ab, glm::vec3());

		// ensure it points toward the origin
		glm::vec3 a0 = simplex.a * -1;
		if (glm::dot(d, a0) < 0) d *= -1;
		break;
	case 4:
		// calculate the three edges of interest
		glm::vec3 da = simplex.d - simplex.a;
		glm::vec3 db = simplex.d - simplex.b;
		glm::vec3 dc = simplex.d - simplex.c;

		// and the direction to the origin
		glm::vec3 d0 = simplex.d * -1;

		// check triangles a-b-d, b-c-d, and c-a-d
		glm::vec3 abdNorm = VectorTripleProduct(da, db, glm::vec3());
		glm::vec3 bcdNorm = VectorTripleProduct(db, dc, glm::vec3());
		glm::vec3 cadNorm = VectorTripleProduct(dc, da, glm::vec3());

		if (glm::dot(abdNorm, d0) > 0) {
			// the origin is on the outside of triangle a-b-d
			// eliminate c!
			simplex.Remove(2);
			d = abdNorm;
		}
		else if (glm::dot(bcdNorm,d0) > 0) {
			// the origin is on the outside of triangle bcd
			// eliminate a!
			simplex.Remove(0);
			d = bcdNorm;
		}
		else if (glm::dot(cadNorm,d0) > 0) {
			// the origin is on the outside of triangle cad
			// eliminate b!
			simplex.Remove(1);
			d = cadNorm;
		}
		else {
			// the origin is inside all of the triangles!
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
		glm::vec3 newVertex = a.support(d) - b.support(-d);
		vertices.push(newVertex);
		if (!(Vec3.dot(d, newVertex) >= 0)
		{
			return false;
		}
	}
}
