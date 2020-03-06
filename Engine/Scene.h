#pragma once
#include "Node.h"
class Car;
class Scene : public Node
{
public:
	CREATE_FUNC(Scene);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void lateUpdate(float delta) override;
protected:
	Car* m_pCar;
};
