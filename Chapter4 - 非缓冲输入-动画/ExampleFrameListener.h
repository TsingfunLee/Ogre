#include "Ogre\ExampleApplication.h"

class ExampleFrameListener1:public Ogre::FrameListener
{
public:
	ExampleFrameListener1(Ogre::SceneNode* node,RenderWindow* win,Ogre::Camera* cam,Ogre::Entity* ent);
	~ExampleFrameListener1();
	bool frameStarted(const Ogre::FrameEvent &evt);
private:
	Ogre::SceneNode* _node;
    Ogre::Camera* _Cam;
	Ogre::PolygonMode _PolyMode;
	OIS::InputManager* _man; 
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Vector3 translate;
	float _movementspeed;
	Ogre::Timer _timer;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;
	Ogre::Entity* _ent;
	Real _rotation;
	Ogre::Vector3 SinbadTranslate;
	Real _WalkingSpeed;
};