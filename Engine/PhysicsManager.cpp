#include "PhysicsManager.h"
#include "Node.h"
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
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());

	//���������
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	//ʹ�����ϴ�����������������������
	m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
		m_dispatcher.get(), 
		m_broadphase.get(), 
		m_solver.get(), 
		m_collisionConfiguration.get());
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

void PhysicsManager::prePhysicUpdate(Node* node, float delta)
{
	if (node == nullptr)
		return;
	for (auto& p : node->childs)
	{
		if (p == nullptr)
		{
			continue;
		}
		if (p->count == 0)
		{
			p = nullptr;
			continue;
		}

		if (p->getVisable())
		{
			p->physicUpdate(delta);
			prePhysicUpdate(p, delta);
		}

	}
}

void PhysicsManager::physicUpdate(float delta)
{
	m_dynamicsWorld->stepSimulation(delta, 10);

	//������������ÿһ������
	auto& objectArray = m_dynamicsWorld->getCollisionObjectArray();
	for (int i = 0; i < objectArray.size(); ++i)
	{
		bool isAcive = objectArray[i]->isActive();
		bool isStatic = objectArray[i]->isStaticObject();
		//���ڲ��״̬�����Ǿ�̬����Ļ����򲻴���
		if (!isAcive || isStatic)continue;
		//Transform* object = reinterpret_cast<Transform*>(objectArray[i]->getUserPointer());
		//û���û�ָ��Ļ����򲻴���
		//if (!object)continue;
		//����Ŀ�������λ��
		const auto& pos = objectArray[i]->getWorldTransform().getOrigin();
		//DEBUG_BTVEC3(pos);
		//object->setPosition(pos.x(), pos.y(), pos.z());
		//����Ŀ���������ת�Ƕ�
		const auto& rotationM = objectArray[i]->getWorldTransform().getRotation();

		//DEBUG_BTVEC3(rotationM);
		//object->setRotation(rotationM.getX(), rotationM.getY(), rotationM.getZ(), rotationM.getW());
	}
}

void PhysicsManager::latePhysicUpdate(Node* node, float delta)
{
	if (node == nullptr)
		return;
	for (auto& p : node->childs)
	{
		if (p == nullptr)
		{
			continue;
		}
		if (p->count == 0)
		{
			p = nullptr;
			continue;
		}

		if (p->getVisable())
		{
			p->physicLateUpdate(delta);
			latePhysicUpdate(p, delta);
		}

	}
}

btRigidBody* PhysicsManager::addRigidBody(const BoxCollider& bc, const Rigidbody& rd)
{
	//���� ����ĳ�ʼλ����ת�Ƕ���Ϣ����ת�Ƕ�0��λ����Y��10����ĸ߿�
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//����������
	btBoxShape* boxShape = new btBoxShape(btVector3(bc.getLength(), bc.getHeight(), bc.getWidth()));

	//����    ������
	btVector3 inertia;
	//�����ܶ��Զ����㲢���ù���     
	boxShape->calculateLocalInertia(rd.getMass(), inertia);

	//����������Ϣ
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, boxShape, inertia);

	//����������Ϣ ��������
	btRigidBody* boxBody = new btRigidBody(sphereRigidBodyCI);
	//����Ħ��ϵ��0.5
	boxBody->setFriction(rd.getFrict());

	//���ø�����ӵ�����������
	m_dynamicsWorld->addRigidBody(boxBody);
	return boxBody;
}

btRigidBody* PhysicsManager::addRigidBody(BoxCollider&& bc, Rigidbody&& rd)
{
	//���� ����ĳ�ʼλ����ת�Ƕ���Ϣ����ת�Ƕ�0��λ����Y��10����ĸ߿�
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//����������
	btBoxShape* boxShape = new btBoxShape(btVector3(bc.getLength(), bc.getHeight(), bc.getWidth()));

	//����    ������
	btVector3 inertia;
	//�����ܶ��Զ����㲢���ù���     
	boxShape->calculateLocalInertia(rd.getMass(), inertia);

	//����������Ϣ
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, boxShape, inertia);

	//����������Ϣ ��������
	btRigidBody* boxBody = new btRigidBody(sphereRigidBodyCI);
	//����Ħ��ϵ��0.5
	boxBody->setFriction(rd.getFrict());

	//���ø�����ӵ�����������
	m_dynamicsWorld->addRigidBody(boxBody);
	return boxBody;
}

btRigidBody* PhysicsManager::addRigidBody(const SphereCollider& sc, const Rigidbody& rd)
{
	//���� ����ĳ�ʼλ����ת�Ƕ���Ϣ����ת�Ƕ�0��λ����Y��10����ĸ߿�
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//���� �뾶0.5��������״
	btCollisionShape* ballShape = new btSphereShape(sc.getRaius());

	//����    ������
	btVector3 inertia;
	//�����ܶ��Զ����㲢���ù���     
	ballShape->calculateLocalInertia(rd.getMass(), inertia);

	//����������Ϣ
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, ballShape, inertia);

	//����������Ϣ ��������
	btRigidBody* ballBody = new btRigidBody(sphereRigidBodyCI);
	//����Ħ��ϵ��0.5
	ballBody->setFriction(rd.getFrict());

	//���ø�����ӵ�����������
	m_dynamicsWorld->addRigidBody(ballBody);
	return ballBody;
}

btRigidBody* PhysicsManager::addRigidBody(SphereCollider&& sc, Rigidbody&& rd)
{
	//���� ����ĳ�ʼλ����ת�Ƕ���Ϣ����ת�Ƕ�0��λ����Y��10����ĸ߿�
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//���� �뾶0.5��������״
	btCollisionShape* ballShape = new btSphereShape(sc.getRaius());

	//����    ������
	btVector3 inertia;
	//�����ܶ��Զ����㲢���ù���     
	ballShape->calculateLocalInertia(rd.getMass(), inertia);

	//����������Ϣ
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, ballShape, inertia);
	
	//����������Ϣ ��������
	btRigidBody* ballBody = new btRigidBody(sphereRigidBodyCI);
	//����Ħ��ϵ��0.5
	ballBody->setFriction(rd.getFrict());

	//���ø�����ӵ�����������
	m_dynamicsWorld->addRigidBody(ballBody);
	return ballBody;
}

PhysicsManager::~PhysicsManager()
{
	m_dynamicsWorld.reset();
	m_broadphase.reset();
	m_collisionConfiguration.reset();
	m_dispatcher.reset();
	m_solver.reset();
}
