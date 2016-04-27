#include "lesson1.h"
//#include "New2Listner.h"



void Exampl1::createScene()
{
	/*Ogre::Plane plane(Vector3::UNIT_Y, -10);
	Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");*/

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-1,0));

	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
	mSceneMgr->getRootSceneNode()->addChild(node);
	Ogre::Entity* Sinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
	_SinbadNode = node->createChildSceneNode("SinbadNode");
	_SinbadNode->setScale(3.0f,3.0f,3.0f);
	_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
	_SinbadNode->attachObject(Sinbad);


	Ogre::Entity* Sinbad2 = mSceneMgr->createEntity("Sinbad2", "Sinbad.mesh");
	_SinbadNode2 = node->createChildSceneNode("SinbadNode2");
	_SinbadNode2->setScale(3.0f,3.0f,3.0f);
	_SinbadNode2->setPosition(Ogre::Vector3(40.0f,4.0f,0.0f));
	_SinbadNode2->attachObject(Sinbad2);


	Ogre::Entity* Robot = mSceneMgr->createEntity("Robot", "Robot.mesh");
	_Robot = node->createChildSceneNode("Robot1");
	_Robot->setScale(0.3f,0.3f,0.3f);
	_Robot->setPosition(Ogre::Vector3(-40.0f,-10.0f,0.0f));
	_Robot->attachObject(Robot);


	Ogre::Vector3 src=_SinbadNode2->getOrientation()*Ogre::Vector3::UNIT_X;
	Ogre::Vector3 direct=Ogre::Vector3(0,0,1);
	Ogre::Quaternion quat=src.getRotationTo(direct);
	_Robot->rotate(quat);


	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	Ogre::SceneNode* camNode0= mSceneMgr->getRootSceneNode()->createChildSceneNode("camNode0");
	camNode0->attachObject(_camVec[0]);
	Ogre::SceneNode* camNode1= mSceneMgr->getRootSceneNode()->createChildSceneNode("camNode1");
	camNode1->attachObject(_camVec[1]);
	Ogre::SceneNode* camNode2= mSceneMgr->getRootSceneNode()->createChildSceneNode("camNode2");
	camNode2->attachObject(_camVec[2]);
	Ogre::SceneNode* camNode3= mSceneMgr->getRootSceneNode()->createChildSceneNode("camNode3");
	camNode3->attachObject(_camVec[3]);

	//create skybox
	mSceneMgr->setSkyBox(true,"Examples/SpaceSkyBox",5000,false);

	//create terrain
	mSceneMgr->setWorldGeometry("terrain.cfg");

	//scene2
	ColourValue fadeColour(0.9, 0.9, 0.9); 
	mSceneMgr2->setSkyBox(true,"Examples/SpaceSkyBox",5000,false);
    mSceneMgr2->setFog(FOG_LINEAR, fadeColour, 0.0, 50, 500);
	mSceneMgr2->setWorldGeometry("terrain.cfg");
	      
	mWindow->getViewport(2)->setBackgroundColour(fadeColour);
	

	/*Ogre::Plane plane(Vector3::UNIT_Y, -10);
	Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr2->createEntity("LightPlaneEntity", "plane");
	mSceneMgr2->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");

	Ogre::Light* light = mSceneMgr2->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-1,0));

	Ogre::SceneNode* node = mSceneMgr2->createSceneNode("Node1");
	mSceneMgr2->getRootSceneNode()->addChild(node);
	Ogre::Entity* Sinbad = mSceneMgr2->createEntity("Sinbad", "Sinbad.mesh");
	_SinbadNode = node->createChildSceneNode("SinbadNode");
	_SinbadNode->setScale(3.0f,3.0f,3.0f);
	_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
	_SinbadNode->attachObject(Sinbad);


	Ogre::Entity* Sinbad2 = mSceneMgr2->createEntity("Sinbad2", "Sinbad.mesh");
	_SinbadNode2 = node->createChildSceneNode("SinbadNode2");
	_SinbadNode2->setScale(3.0f,3.0f,3.0f);
	_SinbadNode2->setPosition(Ogre::Vector3(40.0f,4.0f,0.0f));
	_SinbadNode2->attachObject(Sinbad2);


	Ogre::Entity* Robot = mSceneMgr2->createEntity("Robot", "Robot.mesh");
	_Robot = node->createChildSceneNode("Robot1");
	_Robot->setScale(0.3f,0.3f,0.3f);
	_Robot->setPosition(Ogre::Vector3(-40.0f,-10.0f,0.0f));
	_Robot->attachObject(Robot);


	Ogre::Vector3 src=_SinbadNode2->getOrientation()*Ogre::Vector3::UNIT_X;
	Ogre::Vector3 direct=Ogre::Vector3(0,0,1);
	Ogre::Quaternion quat=src.getRotationTo(direct);
	_Robot->rotate(quat);


	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	Ogre::SceneNode* camNode0= mSceneMgr2->getRootSceneNode()->createChildSceneNode("camNode0");
	camNode0->attachObject(_camVec[0]);
	Ogre::SceneNode* camNode1= mSceneMgr2->getRootSceneNode()->createChildSceneNode("camNode1");
	camNode1->attachObject(_camVec[1]);
	Ogre::SceneNode* camNode2= mSceneMgr2->getRootSceneNode()->createChildSceneNode("camNode2");
	camNode2->attachObject(_camVec[2]);
	Ogre::SceneNode* camNode3= mSceneMgr2->getRootSceneNode()->createChildSceneNode("camNode3");
	camNode3->attachObject(_camVec[3]);*/
}


void Exampl1::chooseSceneManager()
{
	mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
	mSceneMgr2 = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
}


void Exampl1::createCamera()
{
	mCamera = mSceneMgr->createCamera("MyCamera1");
	mCamera->setPosition(0,100,200);
	mCamera->lookAt(0,0,0);
	mCamera->setNearClipDistance(5);


	Ogre::Camera* cam1 = mSceneMgr->createCamera("MyCam1");
	cam1->setPosition(0,100,200);
	cam1->lookAt(0,0,0);
	cam1->setNearClipDistance(5);

	this->_camVec.push_back(cam1);

	cam1 = mSceneMgr->createCamera("MyCam2");
	cam1->setPosition(0,100,-200);
	cam1->lookAt(0,0,0);
	cam1->setNearClipDistance(5);
	this->_camVec.push_back(cam1);

	cam1 = mSceneMgr2->createCamera("MyCam3");
	cam1->setPosition(100,100,200);
	cam1->lookAt(0,0,0);
	cam1->setNearClipDistance(5);
	this->_camVec.push_back(cam1);

	cam1 = mSceneMgr2->createCamera("MyCam4");
	cam1->setPosition(-100,100,200);
	cam1->lookAt(0,0,0);
	cam1->setNearClipDistance(5);
	this->_camVec.push_back(cam1);







}

void Exampl1::createViewports()
{
	//Ogre::Viewport* vp=mWindow->addViewport(mCamera,0,0.0,0.0,1.0,1.0);

	//vp->setBackgroundColour(ColourValue(0.0f,0.0f,1.0f));
	//mCamera->setAspectRatio(Real(vp->getWidth())/Real(vp->getHeight()));

	createFourViewport();

}

void Exampl1::createFourViewport()
{
	Ogre::Viewport* vp1=createViewport(_camVec[0],0);
	vp1->setDimensions(0.0,0.0,0.5,0.5);

	_vpVec.push_back(vp1);

	vp1=createViewport(_camVec[1],1);
	vp1->setDimensions(0.5,0.0,0.5,0.5);
	_vpVec.push_back(vp1);

	vp1=createViewport(_camVec[2],2);
	vp1->setDimensions(0.0,0.5,0.5,0.5);
	_vpVec.push_back(vp1);

	vp1=createViewport(_camVec[3],3);
	vp1->setDimensions(0.5,0.5,0.5,0.5);
	_vpVec.push_back(vp1);

}

Ogre::Viewport* Exampl1::createViewport(Ogre::Camera* cam,int zorder)
{
	Ogre::Viewport* vptemp=mWindow->addViewport(cam,zorder);

	vptemp->setBackgroundColour(ColourValue(0.0f,0.0f,1.0f));

	cam->setAspectRatio(Real(vptemp->getWidth())/Real(vptemp->getHeight()));
	return vptemp;

}

void Exampl1::createFrameListener()
{
	//mNewFrameListener= new NewFrameListener(_SinbadNode);
	//mNewFrameListener= new NewFrameListener(_SinbadNode,mWindow,mCamera);

	mNewFrameListener=new TutorialFrameListener(mWindow,_camVec,_vpVec,mSceneMgr);
	mRoot->addFrameListener(mNewFrameListener);

}