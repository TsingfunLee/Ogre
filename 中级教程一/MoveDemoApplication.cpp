#include "MoveDemoApplication.h"

MoveDemoApplication::MoveDemoApplication()
{
}

MoveDemoApplication::~MoveDemoApplication()
{
}

void MoveDemoApplication::createScene()
{
	// Set the default lighting.
	mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
	// Create the entity
	mEntity = mSceneMgr->createEntity("Robot", "robot.mesh");
	// Create the scene node
	mNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("RobotNode", Vector3(0.0f, 0.0f, 25.0f));
	mNode->attachObject(mEntity);
	// Create the walking list
	mWalkList.push_back(Vector3(550.0f, 0.0f, 50.0f));
	mWalkList.push_back(Vector3(-100.0f, 0.0f, -200.0f));

	// Create objects so we can see movement
	Entity *ent;
	SceneNode *node;
	ent = mSceneMgr->createEntity("Knot1", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node",
		Vector3(0.0f, -10.0f, 25.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
	ent = mSceneMgr->createEntity("Knot2", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node",
		Vector3(550.0f, -10.0f, 50.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
	ent = mSceneMgr->createEntity("Knot3", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node",
		Vector3(-100.0f, -10.0f,-200.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);

	// Set the camera to look at our handiwork
	mCamera->setPosition(90.0f, 280.0f, 535.0f);
	mCamera->pitch(Degree(-30.0f));
	mCamera->yaw(Degree(-15.0f));
}

void MoveDemoApplication::createFrameListener(void)
{
	mFrameListener= new MoveDemoListener(mWindow, mCamera, mNode, mEntity, mWalkList);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}