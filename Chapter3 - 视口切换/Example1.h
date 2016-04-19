#pragma once

#include "Ogre\ExampleApplication.h"
#include "Example1FrameListener.h"

class Example1 :
	public ExampleApplication
{
public:
	void createScene();
	void createCamera();
	void createViewports();
	void createFrameListener();
private:
	Ogre::Camera* mCamTop;
	Ogre::Camera* mCamFront;
	Ogre::Camera* mCamLeft;
	Ogre::FrameListener* mFrameListener;
};

