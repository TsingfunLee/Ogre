#include "ExampleFrameListener.h"

ExampleFrameListener1::ExampleFrameListener1(Ogre::SceneManager* sceneMgr,RenderWindow* win,Ogre::Camera* cam)
	:ExampleFrameListener(win,cam,true,true)
{
	mSceneMgr = sceneMgr;
	mNode = mSceneMgr->getSceneNode("SinbadNode"); 
	mCam = cam;

	mEnt = mSceneMgr->getEntity("Sinbad");
	mAniStateTop = mEnt->getAnimationState("RunTop");
	mAniStateBase = mEnt->getAnimationState("RunBase");

	// 设置旋转和移动速度       
	mRotate = 0.13;       
	mMove = 250;
	mDirection = Vector3::ZERO;
	mPace = 50;
	mTranslate = Vector3::ZERO;

	mRotation = 0;
	mWalkSpeed = 1;
	mWalked = false;

	// 继续渲染      
	mContinue = true;

	mMouse->setEventCallback(this);       
	mKeyboard->setEventCallback(this);

}

ExampleFrameListener1::~ExampleFrameListener1()
{

}

bool ExampleFrameListener1::frameStarted(const Ogre::FrameEvent &evt)
{

	if(mMouse)           
		mMouse->capture();        
	if(mKeyboard)             
		mKeyboard->capture(); 

	//mCam->moveRelative(mDirection*evt.timeSinceLastFrame);

	mAniStateTop->addTime(evt.timeSinceLastFrame);
	mAniStateBase->addTime(evt.timeSinceLastFrame);
	
	if(mWalked)
	{
		mAniStateTop->setEnabled(true);
		mAniStateTop->setLoop(true);
		mAniStateBase->setEnabled(true);
		mAniStateBase->setLoop(true);

		if(mAniStateTop->hasEnded())
		{
			mAniStateTop->setTimePosition(0);
		}
		if(mAniStateBase->hasEnded())
		{
			mAniStateBase->setTimePosition(0);
		}
	}
	else 
	{
		mAniStateTop->setEnabled(false);
		mAniStateTop->setTimePosition(0);
		mAniStateBase->setEnabled(false);
		mAniStateBase->setTimePosition(0);
	}
	

	mNode->translate(mTranslate*evt.timeSinceLastFrame*mWalkSpeed);
	mNode->resetOrientation();
	mNode->yaw(Ogre::Radian(mRotation));

	return mContinue; 

}

bool ExampleFrameListener1::keyPressed(const OIS::KeyEvent &e) 
{
	switch (e.key)      
	{          
	case OIS::KC_ESCAPE:               
		mContinue = false; 
		break; 
	case OIS::KC_UP:
		mTranslate.z -= mPace;
		mRotation = 3.14;
		mWalked = true;
		break;
	case OIS::KC_W:                  
		break;      
	case OIS::KC_DOWN: 
		mTranslate.z += mPace;
		mRotation = 0;
		mWalked = true;
		break;
	case OIS::KC_S:                  
		break;      
	case OIS::KC_LEFT: 
		mTranslate.x -= mPace;
		mRotation = -1.57f;
		mWalked = true;
		break;
	case OIS::KC_A:                  
		break;      
	case OIS::KC_RIGHT: 
	    mTranslate.x += mPace;
		mRotation = 1.57;
		mWalked = true;
		break;
	case OIS::KC_D:                  
		break;      
	case OIS::KC_PGDOWN:      
	case OIS::KC_E:     
		break;      
	case OIS::KC_PGUP:      
	case OIS::KC_Q:                 
		break;
	} 

	

	return true;
}

bool ExampleFrameListener1::keyReleased(const OIS::KeyEvent &e) 
{
	switch (e.key)      
	{          
	case OIS::KC_ESCAPE:               
		mContinue = false;              
		break; 
	case OIS::KC_UP:
		mTranslate.z += mPace;
		mRotation = 3.14;
		mWalked = false;
		break;
	case OIS::KC_W:                 
		break;      
	case OIS::KC_DOWN:
		mTranslate.z -= mPace;
		mRotation = 0;
		mWalked = false;
		break;
	case OIS::KC_S:                   
		break;      
	case OIS::KC_LEFT:
		mTranslate.x += mPace;
		mRotation = -1.57;
		mWalked = false;
		break;
	case OIS::KC_A:                
		break;      
	case OIS::KC_RIGHT:
		mTranslate.x -= mPace;
		mRotation = 1.57;
		mWalked = false;
		break;
	case OIS::KC_D:                   
		break;      
	case OIS::KC_PGDOWN:      
	case OIS::KC_E:         
		break;      
	case OIS::KC_PGUP:      
	case OIS::KC_Q:                 
		break;
	} 
	return true;
}

bool ExampleFrameListener1::mouseMoved(const OIS::MouseEvent &e)
{
	if (e.state.buttonDown(OIS::MB_Right))      
	{          
		mCam->yaw(Degree(-mRotate * e.state.X.rel));          
		mCam->pitch(Degree(-mRotate * e.state.Y.rel));      
	}
	else if(e.state.buttonDown(OIS::MB_Left))
	{
		mCam->moveRelative(Vector3(e.state.X.rel,e.state.Y.rel,0)); 
	}
	return true;
}

bool ExampleFrameListener1::mousePressed(const OIS::MouseEvent &e,OIS::MouseButtonID id)
{
	return true;
}

bool ExampleFrameListener1::mouseReleased(const OIS::MouseEvent &e,OIS::MouseButtonID id)
{
	return true;
}


