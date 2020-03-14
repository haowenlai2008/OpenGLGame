#include "PhysicsManager.h"

bool PhysicsManager::init()
{
	//��������Ŀռ��С���޶������˶��Ŀռ䷶Χ
	btVector3 worldAabbMin(-10000, -10000, -10000);
	btVector3 worldAabbMax(10000, 10000, 10000);
	//������������
	int maxProxies = 1024;
	//�����������ô����ֲ�׶��������
	m_broadphase = std::make_unique<btAxisSweep3>(worldAabbMin, worldAabbMax, maxProxies);

	//��������ײ����
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration);

	//���������
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	//ʹ�����ϴ�����������������������
	m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	//����������������(������y���ϵ�������Ϊ10N/kg)
	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
	

	btDefaultMotionState* groundMotionState = new  btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	//���� ��̬ƽ����״
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	//����������Ϣ
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	//����������Ϣ ��������
	btRigidBody* groundbody = new btRigidBody(groundRigidBodyCI);
	//����Ħ��ϵ��0.5
	groundbody->setFriction(0.5f);
	//�����������ӵ� ��������
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
