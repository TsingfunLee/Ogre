#pragma once
#include "ogre\exampleapplication.h"
//#include "ogre\exampleframelistener.h"
class Example1FrameListener :
	public ExampleFrameListener,public OIS::KeyListener,public OIS::MouseListener
{
public:
	Example1FrameListener(Ogre::SceneManager* sceneMgr,RenderWindow* win,Ogre::Camera* cam);
	~Example1FrameListener(void);
	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e,OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e,OIS::MouseButtonID id);
protected:
	Camera* mCam;
	SceneManager* mSceneMgr;
	Viewport* mvp;
	Real mRotate; 
	bool mContinue;

	int vp;         //current viewport
	bool isvp;      //viewport is full
	//Viewport* p;
};

