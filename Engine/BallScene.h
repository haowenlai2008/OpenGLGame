#pragma once
#include "Node.h"
class Car;
class BallScene : public Node
{
public:
	CREATE_FUNC(BallScene);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void lateUpdate(float delta) override;
protected:
	Node* m_focus;
};
