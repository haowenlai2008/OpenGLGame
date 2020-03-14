#pragma once
#include "Singleton.h"
#include "func.h"
#include "bulletHead.h"
class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	friend class Singleton<PhysicsManager>;
	bool init();
	void update(float delta);
	~PhysicsManager();
private:
	std::unique_ptr<btAxisSweep3> m_broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
};

