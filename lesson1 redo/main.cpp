#include "Ogre\ExampleApplication.h"

class Example1:public ExampleApplication
{
public:
	void createScene()
	{
		/*Ogre::Entity* ent = mSceneMgr->createEntity("MyEntity","Sinbad.mesh");
		Ogre::Entity* ent2 = mSceneMgr->createEntity("MyEntity2","Sinbad.mesh");
		Ogre::Entity* ent3 = mSceneMgr->createEntity("MyEntity3","Sinbad.mesh");
		Ogre::Entity* ent4 = mSceneMgr->createEntity("MyEntity4","Sinbad.mesh");*/
		/*Ogre::SceneNode* node1 = mSceneMgr->createSceneNode("Node1");
		Ogre::SceneNode* node2 = mSceneMgr->createSceneNode("Node2");
		Ogre::SceneNode* node3 = mSceneMgr->createSceneNode("Node3");
		Ogre::SceneNode* node4 = mSceneMgr->createSceneNode("Node4");*/
		
       /* node1->setPosition(10,10,0);
		mSceneMgr->getRootSceneNode()->addChild(node1);

		node2->setPosition(10,0,0);
		node2->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
		node1->addChild(node2);
        node2->attachObject(ent2);

		node3->translate(20,0,0); 
		node3->yaw(Ogre::Degree(90.0f)); 
		node1->addChild(node3);
        node3->attachObject(ent3);

		node4->setPosition(30,0,0); 
		node4->roll(Ogre::Radian(Ogre::Math::HALF_PI)); 
		node1->addChild(node4);
		node1->attachObject(ent);
		
		node4->attachObject(ent4);*/

		/*mSceneMgr->getRootSceneNode()->addChild(node1);
		node1->setPosition(0,0,0);
		node1->attachObject(ent);

		node1->addChild(node2);
		node2->translate(10,0,0);
		node2->pitch(Ogre::Degree(90.0f));
		node2->attachObject(ent2);

		node2->addChild(node3);
		node3->translate(10,0,0);
		node3->pitch(Ogre::Degree(-90.0f));
		node3->yaw(Ogre::Radian(Math::HALF_PI));
		node3->attachObject(ent3);

		node3->addChild(node4);
		node4->translate(0,0,10);
		node4->yaw(Ogre::Degree(-90.0f));
		node4->roll(Ogre::Degree(90.0f));
		node4->attachObject(ent4);*/
		
	/*	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1"); 
		node->setPosition(10,10,0); 
		mSceneMgr->getRootSceneNode()->addChild(node); 
		node->attachObject(ent);

		Ogre::SceneNode* node2 = node->createChildSceneNode("node2"); 
		node2->setPosition(10,0,0); 
		node2->attachObject(ent2);
		node2->scale(2.0f,2.0f,2.0f);

		Ogre::SceneNode* node3 = node->createChildSceneNode("node3",Ogre::Vector3(20,0,0));
		node3->scale(0.2f,0.2f,0.2f);
		node3->attachObject(ent3);*/

		Ogre::Entity* ent = mSceneMgr->createEntity("MyEntity","Sinbad.mesh");
        Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
        node->setPosition(0,0,400);
        node->yaw(Ogre::Degree(180.0f));
        mSceneMgr->getRootSceneNode()->addChild(node);
        node->attachObject(ent);

		Ogre::Entity* ent2 = mSceneMgr->createEntity("MyEntity2","Sinbad.mesh");
        Ogre::SceneNode* node2 = node->createChildSceneNode("node2");
        node2->yaw(Ogre::Degree(45.0f));
        node2->translate(0,0,20);
        node2->attachObject(ent2);

		Ogre::Entity* ent3 = mSceneMgr->createEntity("MyEntity3","Sinbad.mesh");
        Ogre::SceneNode* node3 = node->createChildSceneNode("node3");
        node3->yaw(Ogre::Degree(45.0f));
        node3->translate(0,0,20,Ogre::Node::TS_LOCAL);
        node3->attachObject(ent3);
	}
};

int main(void){
	Example1 app;
	app.go();

	return 0;
}