#include "PhysicsManager.h"

bool PhysicsManager::init()
{
	//设置世界的空间大小，限定刚体运动的空间范围
	btVector3 worldAabbMin(-10000, -10000, -10000);
	btVector3 worldAabbMax(10000, 10000, 10000);
	//设置最大刚体数
	int maxProxies = 1024;
	//利用以上配置创建粗测阶段所需参数
	m_broadphase = std::make_unique<btAxisSweep3>(worldAabbMin, worldAabbMax, maxProxies);

	//创建好碰撞配置
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration);

	//创建求解器
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	//使用以上创建的设置来创建物理世界
	m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	//设置物理世界重力(这里在y轴上的重力设为10N/kg)
	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
	

	btDefaultMotionState* groundMotionState = new  btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	//创建 静态平面形状
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	//生成设置信息
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	//根据设置信息 创建刚体
	btRigidBody* groundbody = new btRigidBody(groundRigidBodyCI);
	//设置摩擦系数0.5
	groundbody->setFriction(0.5f);
	//将地面刚体添加到 物理世界
	m_dynamicsWorld->addRigidBody(groundbody);
	return true;
}

void PhysicsManager::update(float delta)
{

}

PhysicsManager::~PhysicsManager()
{
	m_dynamicsWorld.reset();
	m_broadphase.reset();
	m_collisionConfiguration.reset();
	m_dispatcher.reset();
	m_solver.reset();
}
