#include "Example1FrameListener.h"


Example1FrameListener::Example1FrameListener(Ogre::SceneManager* sceneMgr,RenderWindow* win,Ogre::Camera* cam)
	:ExampleFrameListener(win,cam,true,true)
{
	mSceneMgr = sceneMgr;
	mCam = mSceneMgr->getCamera("defaultCamera");
	mRotate = 1.5f;
	mContinue = true;

	vp = 1;
	isvp = false;
	mvp = NULL;
	//p = NULL;

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);
}


Example1FrameListener::~Example1FrameListener(void)
{
}

bool Example1FrameListener::frameStarted(const Ogre::FrameEvent &evt)
{       
	if(mKeyboard)             
		mKeyboard->capture(); 
	if(mMouse)
		mMouse->capture();

	return mContinue; 
}

bool Example1FrameListener::keyPressed(const OIS::KeyEvent &e)
{
	switch(e.key)
	{
	case OIS::KC_ESCAPE:
		mContinue = false;
		break;
	case OIS::KC_TAB:
		if(vp == 1)
		{
			mCam = mSceneMgr->getCamera("topCamera");
			vp++;
		}
		else if(vp == 2)
		{
			mCam = mSceneMgr->getCamera("leftCamera");
			vp++;
		}
		else if(vp == 3)
		{
			mCam = mSceneMgr->getCamera("frontCamera");
			vp++;
		}
		else if(vp == 4)
		{
			mCam = mSceneMgr->getCamera("defaultCamera");
			vp=1;
		}
		break;
	case OIS::KC_SPACE:
		if(!isvp)
		{
			mvp = mWindow->addViewport(mCam,4,0,0,1,1);
			isvp = true;
		}
		else
		{
			mWindow->removeViewport(4);
			isvp = false;
		}
		break;
	}
	return true;
}

bool Example1FrameListener::keyReleased(const OIS::KeyEvent &e)
{
	return true;
}

bool Example1FrameListener::mouseMoved(const OIS::MouseEvent &e)
{
	if (e.state.buttonDown(OIS::MB_Right))      
	{          
		mCam->yaw(Degree(-mRotate * e.state.X.rel));          
		mCam->pitch(Degree(-mRotate * e.state.Y.rel));      
	}
	return true;
}

bool Example1FrameListener::mousePressed(const OIS::MouseEvent &e,OIS::MouseButtonID id)
{
	//Viewport* vp;
	//if(e.state.buttonDown(OIS::MB_Left))
	//{
	//	/*mCam = mSceneMgr->getCamera("leftCamera");*/
	//	vp = mWindow->addViewport(mCam,4,0,0,1,1);
	//}
	//else if(e.state.buttonDown(OIS::MB_Right))
	//{
	//	vp->clear();
	//}
	return true;
}

bool Example1FrameListener::mouseReleased(const OIS::MouseEvent &e,OIS::MouseButtonID id)
{
	return true;
}