#pragma once

#include "Ogre\ExampleApplication.h"

class Example1 :
	public ExampleApplication
{
public:
	void createScene();
	void createCamera();
	void createViewports();
private:
	Ogre::Camera* mCamTop;
	Ogre::Camera* mCamFront;
	Ogre::Camera* mCamLeft;
};

