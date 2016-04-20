#include "MoveDemoApplication.h"

MoveDemoApplication::MoveDemoApplication()
{
}

MoveDemoApplication::~MoveDemoApplication()
{
}

void MoveDemoApplication::createScene()
{
	//create the plane
	Ogre::Plane plane(Vector3::UNIT_Y,-10);
	Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* planeent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeent);
	planeent->setMaterialName("Examples/BeachStones");
	// Set the default lighting.
	mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
	Light* light = mSceneMgr->createLight();
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(ColourValue(1,1,1));
	light->setDirection(Vector3(1,-1,0));
	// Create the entity
	mEntity = mSceneMgr->createEntity("robot", "robot.mesh");
	// Create the scene node
	mNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("robotNode", Vector3(0.0f, 0.0f, 50.0f));
	mNode->attachObject(mEntity);
	mNode->scale(0.1,0.1,0.1);
	//create the sinbad
	Entity* ent = mSceneMgr->createEntity("Sinbad","Sinbad.mesh");
	SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("sinbadNode");
	node->attachObject(ent);
	node->setPosition(0,0,0);
	node->scale(1,1,1);

	// Create the walking list
	Vector3 destination(0,0,50);     //walking destination
	Vector3 point(0,0,0);      //walking circle center
	for(float angle=1.57;angle<=628;angle+=0.1)   //around circle walking
	{
		mWalkList.push_back(destination);
		destination.x = point.x+50*cos(angle);
		destination.z = point.z+50*sin(angle);
	}

	// Set the camera to look at our handiwork
	mCamera->setPosition(-30, 30, 100);
	mCamera->lookAt(0,0,0);
}

void MoveDemoApplication::createFrameListener(void)
{
	mFrameListener= new MoveDemoListener(mWindow, mCamera, mNode, mEntity, mWalkList);
	mFrameListener->showDebugOverlay(true);
	mRoot->addFrameListener(mFrameListener);
}