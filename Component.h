#ifndef COMPONENT_H
#define COMPONENT_H


class GameObject;
class Component {
public:
	inline Component() : parent(nullptr) {}
	virtual ~Component() { parent = nullptr; }
	virtual bool OnCreate(GameObject* parent_) = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render(Camera* camera_)const = 0;
protected:
	GameObject* parent;

}; 
#endif // !COMPONENT_H