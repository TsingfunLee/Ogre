#include "ExampleFrameListener.h"


ExampleFrameListener1::ExampleFrameListener1(Ogre::SceneNode* node,RenderWindow* win,Ogre::Camera* cam)
{ 
	_node = node; 
	translate = Ogre::Vector3(0,0,0);
	_Cam= cam;
	_movementspeed = 1;

	size_t windowHnd = 0;
	std::stringstream windowHndStr;
	win->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	OIS::ParamList pl; 
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	_man = OIS::InputManager::createInputSystem( pl );
	_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false ));
	_mouse = static_cast<OIS::Mouse*>(_man->createInputObject( OIS::OISMouse, false ));
}

ExampleFrameListener1::~ExampleFrameListener1() 
{ 
	_man->destroyInputObject(_key);
	_man->destroyInputObject(_mouse);

	OIS::InputManager::destroyInputSystem(_man); 
}


bool ExampleFrameListener1::frameStarted(const Ogre::FrameEvent &evt)
{ 
	

	_key->capture(); 
	_mouse->capture();

	float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1; 
	float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;

	//float anl = 30*evt.timeSinceLastFrame;

	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));
	
	if(_key->isKeyDown(OIS::KC_ESCAPE)) 
	{ 
		return false; 
	}
	if(_key->isKeyDown(OIS::KC_W)) 
	{ 
		translate = Ogre::Vector3(0,0,10); 
		//_node->translate(translate*evt.timeSinceLastFrame*_movementspeed);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	}
	if(_key->isKeyDown(OIS::KC_S)) 
	{ 
		translate = Ogre::Vector3(0,0,-10); 
		_node->translate(translate*evt.timeSinceLastFrame*_movementspeed);
		//_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	} 
	if(_key->isKeyDown(OIS::KC_A)) 
	{ 
		translate = Ogre::Vector3(10,0,0);
		//_node->yaw(Ogre::Degree(anl));
		_node->translate(translate*evt.timeSinceLastFrame*_movementspeed);
		//_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	} 
	if(_key->isKeyDown(OIS::KC_D)) 
	{ 
		translate = Ogre::Vector3(-10,0,0); 
		_node->translate(translate*evt.timeSinceLastFrame*_movementspeed);
		//_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	}

	return true;
}
