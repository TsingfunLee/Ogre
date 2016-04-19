#include "ExampleFrameListener.h"

ExampleFrameListener1::ExampleFrameListener1(Ogre::SceneNode* node,RenderWindow* win,Ogre::Camera* cam,Ogre::Entity* ent)
{
	_node = node;
	_Cam= cam;
	_PolyMode = Ogre::PolygonMode::PM_SOLID;
	translate = Ogre::Vector3(0,0,0);
	SinbadTranslate = Ogre::Vector3(0,0,0);
	_movementspeed = 1;
	_WalkingSpeed = 50;
	_rotation = 0;
	size_t windowHnd = 0; 
	std::stringstream windowHndStr;
	win->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	OIS::ParamList pl; 
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	_man = OIS::InputManager::createInputSystem( pl );
	_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false ));
	_mouse = static_cast<OIS::Mouse*>(_man->createInputObject( OIS::OISMouse, false ));
	_timer.reset();

	_ent = ent;
	_aniState = _ent->getAnimationState("RunBase");
	//_aniState->setEnabled(true);
	_aniState->setLoop(false);
	_aniState->setTimePosition(0.0);
	_aniStateTop = _ent->getAnimationState("RunTop");
	_aniStateTop->setLoop(false);
}

ExampleFrameListener1::~ExampleFrameListener1()
{
	_man->destroyInputObject(_key);
	_man->destroyInputObject(_mouse);
	OIS::InputManager::destroyInputSystem(_man);
}

bool ExampleFrameListener1::frameStarted(const Ogre::FrameEvent &evt)
{
	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);

	bool walked = false; 
	Ogre::Vector3 SinbadTranslate(0,0,0);

	_key->capture();
	_mouse->capture();

	float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1; 
	float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;

	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));
	//_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);

	if(_key->isKeyDown(OIS::KC_ESCAPE)) 
	{ 
		return false; 
	}
	else if(_key->isKeyDown(OIS::KC_W)) 
	{ 
		translate += Ogre::Vector3(0,0,-10); 
		//_node->translate(translate * evt.timeSinceLastFrame);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	} 
	else if(_key->isKeyDown(OIS::KC_S)) 
	{ 
		translate += Ogre::Vector3(0,0,10); 
		//_node->translate(translate * evt.timeSinceLastFrame);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	}
	else if(_key->isKeyDown(OIS::KC_A)) 
	{ 
		translate += Ogre::Vector3(-10,0,0); 
		//_node->translate(translate * evt.timeSinceLastFrame);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	} 
	else if(_key->isKeyDown(OIS::KC_D)) 
	{ 
		translate += Ogre::Vector3(10,0,0); 
		//_node->translate(translate * evt.timeSinceLastFrame);
		_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	}
	else if(_key->isKeyDown(OIS::KC_R) && _timer.getMilliseconds() > 250) 
	{
		if(_PolyMode == PM_SOLID) 
		{ 
			_PolyMode = Ogre::PolygonMode::PM_WIREFRAME; 
		}
		else if(_PolyMode == PM_WIREFRAME) 
		{ 
			_PolyMode = Ogre::PolygonMode::PM_POINTS; 
		}
		else if(_PolyMode == PM_POINTS) 
		{ 
			_PolyMode = Ogre::PolygonMode::PM_SOLID; 
		}
		_Cam->setPolygonMode(_PolyMode);
		_timer.reset();
	}




	if(_key->isKeyDown(OIS::KC_UP)) 
	{ 
		SinbadTranslate +=Ogre::Vector3(0,0,-1); 
		_rotation =3.14f; 
		walked =true; 

		_node->translate(SinbadTranslate *evt.timeSinceLastFrame* _WalkingSpeed);
		_node->resetOrientation(); 
		_node->yaw(Ogre::Radian(_rotation));
	}
	if(_key->isKeyDown(OIS::KC_DOWN)) 
	{ 
		SinbadTranslate +=Ogre::Vector3(0,0,1); 
		_rotation =0.0f; 
		walked =true; 

		_node->translate(SinbadTranslate *evt.timeSinceLastFrame* _WalkingSpeed);
		_node->resetOrientation(); 
		_node->yaw(Ogre::Radian(_rotation));
	} 
	if(_key->isKeyDown(OIS::KC_LEFT)) 
	{ 
		SinbadTranslate +=Ogre::Vector3(-1,0,0); 
		_rotation =-1.57f; 
		walked =true; 

		_node->translate(SinbadTranslate *evt.timeSinceLastFrame* _WalkingSpeed);
		_node->resetOrientation(); 
		_node->yaw(Ogre::Radian(_rotation));
	} 
	if(_key->isKeyDown(OIS::KC_RIGHT)) 
	{ 
		SinbadTranslate +=Ogre::Vector3(1,0,0); 
		_rotation =1.57f; 
		walked =true; 

		_node->translate(SinbadTranslate *evt.timeSinceLastFrame* _WalkingSpeed);
		_node->resetOrientation(); 
		_node->yaw(Ogre::Radian(_rotation));
	}
	if(walked) 
	{ 
		_aniState->setEnabled(true); 
		_aniStateTop->setEnabled(true); 
		if(_aniState->hasEnded()) 
		{ 
			_aniState->setTimePosition(0.0f); 
		} 
		if(_aniStateTop->hasEnded()) 
		{ 
			_aniStateTop->setTimePosition(0.0f); 
		} 
	}
	else 
	{
		_aniState->setTimePosition(0.0f); 
		_aniState->setEnabled(false); 
		_aniStateTop->setTimePosition(0.0f); 
		_aniStateTop->setEnabled(false);
	}


	return true;
}