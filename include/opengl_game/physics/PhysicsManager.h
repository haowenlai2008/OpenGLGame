#pragma once
#include "opengl_game/core/Singleton.h"
#include "opengl_game/core/func.h"
#include "opengl_game/physics/bulletHead.h"
#include "opengl_game/physics/BoxCollider.h"
#include "opengl_game/physics/SphereCollider.h"
#include "opengl_game/physics/Rigidbody.h"
class Node;
class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	friend class Singleton<PhysicsManager>;
	bool init();
	void prePhysicUpdate(Node* node, float delta);
	void physicUpdate(float delta);
	void latePhysicUpdate(Node* node, float delta);
	btRigidBody* addRigidBody(const BoxCollider& bc, const Rigidbody& rd);
	btRigidBody* addRigidBody(BoxCollider&& bc, Rigidbody&& rd);
	btRigidBody* addRigidBody(const SphereCollider& sc, const Rigidbody& rd);
	btRigidBody* addRigidBody(SphereCollider&& sc, Rigidbody&& rd);

	~PhysicsManager();
private:
	std::unique_ptr<btAxisSweep3> m_broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
};

