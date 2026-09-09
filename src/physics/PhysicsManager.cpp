#include "PhysicsManager.h"
#include "Node.h"
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
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());

	//创建求解器
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	//使用以上创建的设置来创建物理世界
	m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
		m_dispatcher.get(), 
		m_broadphase.get(), 
		m_solver.get(), 
		m_collisionConfiguration.get());
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

	//更新物理世界每一个物体
	auto& objectArray = m_dynamicsWorld->getCollisionObjectArray();
	for (int i = 0; i < objectArray.size(); ++i)
	{
		bool isAcive = objectArray[i]->isActive();
		bool isStatic = objectArray[i]->isStaticObject();
		//处于不活动状态或者是静态刚体的话，则不处理
		if (!isAcive || isStatic)continue;
		//Transform* object = reinterpret_cast<Transform*>(objectArray[i]->getUserPointer());
		//没有用户指针的话，则不处理
		//if (!object)continue;
		//更新目标物体的位置
		const auto& pos = objectArray[i]->getWorldTransform().getOrigin();
		//DEBUG_BTVEC3(pos);
		//object->setPosition(pos.x(), pos.y(), pos.z());
		//更新目标物体的旋转角度
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
	//创建 物体的初始位置旋转角度信息：旋转角度0，位置在Y轴10距离的高空
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//创建立方体
	btBoxShape* boxShape = new btBoxShape(btVector3(bc.getLength(), bc.getHeight(), bc.getWidth()));

	//惯性    　　　
	btVector3 inertia;
	//根据密度自动计算并设置惯性     
	boxShape->calculateLocalInertia(rd.getMass(), inertia);

	//生成设置信息
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, boxShape, inertia);

	//根据设置信息 创建刚体
	btRigidBody* boxBody = new btRigidBody(sphereRigidBodyCI);
	//设置摩擦系数0.5
	boxBody->setFriction(rd.getFrict());

	//将该刚体添加到物理世界里
	m_dynamicsWorld->addRigidBody(boxBody);
	return boxBody;
}

btRigidBody* PhysicsManager::addRigidBody(BoxCollider&& bc, Rigidbody&& rd)
{
	//创建 物体的初始位置旋转角度信息：旋转角度0，位置在Y轴10距离的高空
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//创建立方体
	btBoxShape* boxShape = new btBoxShape(btVector3(bc.getLength(), bc.getHeight(), bc.getWidth()));

	//惯性    　　　
	btVector3 inertia;
	//根据密度自动计算并设置惯性     
	boxShape->calculateLocalInertia(rd.getMass(), inertia);

	//生成设置信息
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, boxShape, inertia);

	//根据设置信息 创建刚体
	btRigidBody* boxBody = new btRigidBody(sphereRigidBodyCI);
	//设置摩擦系数0.5
	boxBody->setFriction(rd.getFrict());

	//将该刚体添加到物理世界里
	m_dynamicsWorld->addRigidBody(boxBody);
	return boxBody;
}

btRigidBody* PhysicsManager::addRigidBody(const SphereCollider& sc, const Rigidbody& rd)
{
	//创建 物体的初始位置旋转角度信息：旋转角度0，位置在Y轴10距离的高空
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//创建 半径0.5的球体形状
	btCollisionShape* ballShape = new btSphereShape(sc.getRaius());

	//惯性    　　　
	btVector3 inertia;
	//根据密度自动计算并设置惯性     
	ballShape->calculateLocalInertia(rd.getMass(), inertia);

	//生成设置信息
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, ballShape, inertia);

	//根据设置信息 创建刚体
	btRigidBody* ballBody = new btRigidBody(sphereRigidBodyCI);
	//设置摩擦系数0.5
	ballBody->setFriction(rd.getFrict());

	//将该刚体添加到物理世界里
	m_dynamicsWorld->addRigidBody(ballBody);
	return ballBody;
}

btRigidBody* PhysicsManager::addRigidBody(SphereCollider&& sc, Rigidbody&& rd)
{
	//创建 物体的初始位置旋转角度信息：旋转角度0，位置在Y轴10距离的高空
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//创建 半径0.5的球体形状
	btCollisionShape* ballShape = new btSphereShape(sc.getRaius());

	//惯性    　　　
	btVector3 inertia;
	//根据密度自动计算并设置惯性     
	ballShape->calculateLocalInertia(rd.getMass(), inertia);

	//生成设置信息
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(rd.getMass(), ballMotionState, ballShape, inertia);
	
	//根据设置信息 创建刚体
	btRigidBody* ballBody = new btRigidBody(sphereRigidBodyCI);
	//设置摩擦系数0.5
	ballBody->setFriction(rd.getFrict());

	//将该刚体添加到物理世界里
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
