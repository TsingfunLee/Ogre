#include "OGRE\ExampleApplication.h"
#include "ExampleFrameListener.h"
#include <string>
#include <sstream>
using namespace std;

class SceneExample:public ExampleApplication
{
private:
	Ogre::SceneNode* _SinbadNode;
	Ogre::FrameListener* FrameListener;
public:
	SceneExample() 
	{ 
		FrameListener = NULL; 
	}
	~SceneExample() 
	{ 
		if(FrameListener) 
		{ 
			delete FrameListener; 
		} 
	}
public:
	void createScene()
	{
		////创建场景根节点的4个子节点
		//Ogre::SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node1");
		//Ogre::SceneNode* node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node2");
		//Ogre::SceneNode* node3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node3");
		//SceneNode* node4 = mSceneMgr->getRootSceneNode()->createChildSceneNode("node4");
		////以node1为根节点创建树形节点
		//Ogre::SceneNode* node5 = node1->createChildSceneNode("node5");
		//Ogre::SceneNode* node6 = node5->createChildSceneNode("node6");
		//Ogre::SceneNode* node7 = node6->createChildSceneNode("node7");
		////创建Entity
		//Ogre::Entity* ent[7];
		//for(int i = 0;i < 7;++i)
		//{
		//	std::stringstream s1;
		//	string index;
		//	s1 << i;
		//	index = s1.str();
		//	string entname = "ent"+index;
		//	ent[i] = mSceneMgr->createEntity(entname,"Sinbad.mesh");
		//}
		////将ent添加进场景
		////平行节点
		//node1->setPosition(0,0,0);
		//node1->scale(0.5f,0.5f,0.5f);
		//node1->attachObject(ent[0]);
		////绕X轴旋转90度
		//node2->setPosition(10,0,0);
		//node2->pitch(Ogre::Degree(90.0f));
		//node2->attachObject(ent[1]);
		////绕Y轴旋转90度
		//node3->setPosition(20,0,0);
		//node3->yaw(Ogre::Degree(90.0f));
		//node3->attachObject(ent[2]);
		////绕Z轴旋转90度
		//node4->setPosition(30,0,0);
		//node4->roll(Ogre::Degree(90.0f));
		//node4->attachObject(ent[3]);

		////树形节点
		////绕X轴旋转90度
		//node5->translate(0,-10,0,Ogre::Node::TS_WORLD);
		//node5->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
		//node5->attachObject(ent[4]);
		////绕Y轴旋转90度
		//node6->translate(0,-10,0,Ogre::Node::TS_WORLD);
		//node6->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
		//node6->attachObject(ent[5]);
		////绕Z轴旋转90度
		//node7->translate(0,-10,0,Ogre::Node::TS_WORLD);
		//node7->roll(Ogre::Radian(Ogre::Math::HALF_PI));
		//node7->attachObject(ent[6]);

		//Ogre::Plane plane(Vector3::UNIT_Y,-10);
  //      Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		//	1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
		//Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
		////mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
		//ent->setMaterialName("Examples/BeachStones");

		//Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1"); 
		//mSceneMgr->getRootSceneNode()->addChild(node);
		//node->attachObject(ent);

		/*Ogre::Light*light1 = mSceneMgr->createLight("Light1"); 
		light1->setType(Ogre::Light::LT_POINT);
		light1->setPosition(0,20,0);
		light1->setDiffuseColour(0.5f,0.1f,0.5f);*/

		//Ogre::Entity* LightEnt= mSceneMgr->createEntity("MyEntity","sphere.mesh"); 
		//Ogre::SceneNode* node3 = node->createChildSceneNode("node3"); 
		//node3->setScale(0.1f,0.1f,0.1f); 
		//node3->setPosition(0,100,0); 
		////LightEnt->setMaterialName("Examples/muse");
		//node3->attachObject(LightEnt);

		/*Ogre::SceneNode* node2 =node->createChildSceneNode("node2"); 
		node2->setPosition(0,100,0);

		Ogre::Light* light =mSceneMgr->createLight("Light1"); 
		light->setType(Ogre::Light::LT_SPOTLIGHT);
		light->setDirection(Ogre::Vector3(1,-1,0)); 
		light->setSpotlightInnerAngle(Ogre::Degree(5.0f)); 
		light->setSpotlightOuterAngle(Ogre::Degree(45.0f)); 
		light->setSpotlightFalloff(0.0f);

		light->setDiffuseColour(Ogre::ColourValue(0.0f,1.0f,0.0f)); 
		node2->attachObject(light);*/

		/*Ogre::Light* light = mSceneMgr->createLight("Light1"); 
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f)); 
		light->setDirection(Ogre::Vector3(1,-1,0));

		Ogre::Entity* sinbad = mSceneMgr->createEntity("ent","Sinbad.mesh");
		Ogre::SceneNode* sinbadNode = node->createChildSceneNode("sinbadNode");
		sinbadNode->setScale(3.0f,3.0f,3.0f); 
		sinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
		sinbadNode->attachObject(sinbad);*/
		//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);


Ogre::Plane plane(Vector3::UNIT_Y,-10); 
Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
	1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent); 
ent->setMaterialName("Examples/BeachStones");

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

mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	}

	void createCamera()
	{
		//mCamera = mSceneMgr->createCamera("MyCamera1");
		//mCamera->setPosition(100,50,0); 
		//mCamera->lookAt(0,0,0); 
		//mCamera->setNearClipDistance(5);
		////mCamera->setFarClipDistance(10);
		//mCamera->setPolygonMode(Ogre::PM_WIREFRAME);

		mCamera =mSceneMgr->createCamera("MyCamera1"); 
		mCamera->setPosition(0,100,-200); 
		mCamera->lookAt(0,0,0); 
		mCamera->setNearClipDistance(5);

	}

	/*void createViewports()
	{
		Ogre::Viewport* vp = mWindow->addViewport(mCamera,0,0,0,0.5,0.5);
		vp->setBackgroundColour(ColourValue(0.0f,0.0f,1.0f));
		mCamera->setAspectRatio((Real)(vp->getActualWidth())/(Real)(vp->getActualHeight()));
	}*/

	void createFrameListener() 
	{ 
		FrameListener = new ExampleFrameListener1(_SinbadNode,mWindow,mCamera); 
		mRoot->addFrameListener(FrameListener); 
	}

};

int main()
{
	SceneExample app;
	app.go();

	return 0;
}