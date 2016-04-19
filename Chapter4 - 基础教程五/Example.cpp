#include "Example.h"

Example::Example()
{
	FrameListener = NULL;
}

Example::~Example()
{
	if(FrameListener)
	{ 
		delete FrameListener; 
	}
}

void Example::createScene()
{
	//create plane
	Ogre::Plane plane(Vector3::UNIT_Y,-10); 
	Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z); 
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane"); 
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent); 
	ent->setMaterialName("Examples/BeachStones");

	//create light
	Ogre::Light* light = mSceneMgr->createLight("Light1"); 
	light->setType(Ogre::Light::LT_DIRECTIONAL); 
	light->setDirection(Ogre::Vector3(1,-1,0));

	//create sinbad
	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1"); 
	mSceneMgr->getRootSceneNode()->addChild(node); 
	Ogre::Entity* Sinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh"); 
	_SinbadNode = node->createChildSceneNode("SinbadNode"); 
	_SinbadNode->setScale(3.0f,3.0f,3.0f); 
	_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f)); 
	_SinbadNode->attachObject(Sinbad);

	//set shadow
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
}

void Example::createCamera()
{
	mCamera =mSceneMgr->createCamera("MyCamera1");
	mCamera->setPosition(0,100,200); 
	mCamera->lookAt(0,0,0); 
	mCamera->setNearClipDistance(5);
}

void Example::createFrameListener()
{
	FrameListener = new ExampleFrameListener1(_SinbadNode,mWindow,mCamera); 
	mRoot->addFrameListener(FrameListener);
}