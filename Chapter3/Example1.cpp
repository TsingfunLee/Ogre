#include "Example1.h"

void Example1::createScene()
{
	//create plane
	Ogre::Plane plane(Vector3::UNIT_Y,0);
	Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
		1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* planeEntity = mSceneMgr->createEntity("PlaneEntity","plane");
	planeEntity->setMaterialName("Examples/BeachStones");
	Ogre::SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node1");
	node1->attachObject(planeEntity);

	//create sinbad
	Ogre::Entity* sinbadEntity = mSceneMgr->createEntity("SinbadEntity","Sinbad.mesh");
	Ogre::SceneNode* node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node2");
	node2->setPosition(0,15,0);
	node2->scale(3.0f,3.0f,3.0f);
	node2->attachObject(sinbadEntity);

	//create light
	Ogre::Light* directLight = mSceneMgr->createLight("DirectLight");
	directLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directLight->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f)); 
    directLight->setDirection(Ogre::Vector3(1,-1,0));
}

void Example1::createCamera()
{
	//create camera
	mCamera = mSceneMgr->createCamera("defaultCamera");
	mCamera->setPosition(100,50,200);
	mCamera->lookAt(0,0,0);
	mCamera->setNearClipDistance(5);

	mCamTop = mSceneMgr->createCamera("topCamera");
    mCamTop->setPosition(0,100,0);
	mCamTop->lookAt(0,0,0);
	mCamTop->setNearClipDistance(5);

    mCamLeft = mSceneMgr->createCamera("leftCamera");
	mCamLeft->setPosition(-100,50,0);
	mCamLeft->lookAt(0,0,0);
	mCamLeft->setNearClipDistance(5);

	mCamFront = mSceneMgr->createCamera("frontCamera");
	mCamFront->setPosition(0,50,100);
	mCamFront->lookAt(0,0,0);
	mCamFront->setNearClipDistance(5);

	//set shadow
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void Example1::createViewports()
{
	 // Create viewport
     Viewport* vp1 = mWindow->addViewport(mCamera,0,0,0,0.5,0.5);
     vp1->setBackgroundColour(ColourValue(0,0,0));

	 Viewport* vp2 = mWindow->addViewport(mCamTop,1,0.5,0,0.5,0.5);
	 vp2->setBackgroundColour(ColourValue(1,0,0));

	 Viewport* vp3 = mWindow->addViewport(mCamLeft,2,0,0.5,0.5,0.5);
	 vp3->setBackgroundColour(ColourValue(0,1,0));

	 Viewport* vp4 = mWindow->addViewport(mCamFront,3,0.5,0.5,0.5,0.5);
	 vp4->setBackgroundColour(ColourValue(0,0,1));

	 //set camera aspect
     mCamera->setAspectRatio(Real(vp1->getActualWidth()) / Real(vp1->getActualHeight()));
	 mCamera->setAspectRatio(Real(vp2->getActualWidth()) / Real(vp2->getActualHeight()));
	 mCamera->setAspectRatio(Real(vp3->getActualWidth()) / Real(vp3->getActualHeight()));
	 mCamera->setAspectRatio(Real(vp4->getActualWidth()) / Real(vp4->getActualHeight()));
}

