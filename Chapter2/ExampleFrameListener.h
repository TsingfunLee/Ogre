#pragma once
#include "OGRE\ExampleApplication.h"

class ExampleFrameListener1 :
	public Ogre::FrameListener
{
public:
	ExampleFrameListener1(Ogre::SceneNode* node,RenderWindow* win,Ogre::Camera* cam);
	~ExampleFrameListener1();

	bool frameStarted(const Ogre::FrameEvent &evt);
	//bool frameRenderingQueued(const FrameEvent& evt);
	//bool frameEnded(const FrameEvent& evt);
private: 
	Ogre::SceneNode* _node;
	OIS::InputManager* _man; 
	OIS::Keyboard* _key;
	Ogre::Vector3 translate;
	Ogre::Camera* _Cam;
	OIS::Mouse* _mouse;
	float _movementspeed;
};

