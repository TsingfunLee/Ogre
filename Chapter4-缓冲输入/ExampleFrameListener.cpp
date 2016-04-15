#include "ExampleFrameListener.h"

ExampleFrameListener1::ExampleFrameListener1(Ogre::SceneManager* sceneMgr,RenderWindow* win,Ogre::Camera* cam)
	:ExampleFrameListener(win,cam,true,true)
{
	mSceneMgr = sceneMgr;
	mNode = mSceneMgr->getSceneNode("SinbadNode"); 
	mCam = cam;
	// 设置旋转和移动速度       
	mRotate = 0.13;       
	mMove = 250;
	mDirection = Vector3::ZERO;

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

	mCam->moveRelative(mDirection*evt.timeSinceLastFrame);

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
	case OIS::KC_W:          
		mDirection.z -= mMove;         
		break;      
	case OIS::KC_DOWN:      
	case OIS::KC_S:          
		mDirection.z += mMove;          
		break;      
	case OIS::KC_LEFT:      
	case OIS::KC_A:          
		mDirection.x -= mMove;          
		break;      
	case OIS::KC_RIGHT:      
	case OIS::KC_D:          
		mDirection.x += mMove;          
		break;      
	case OIS::KC_PGDOWN:      
	case OIS::KC_E:
		mDirection.y -= mMove;          
		break;      
	case OIS::KC_PGUP:      
	case OIS::KC_Q:          
		mDirection.y += mMove;          
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
	case OIS::KC_W:          
		mDirection.z += mMove;         
		break;      
	case OIS::KC_DOWN:      
	case OIS::KC_S:          
		mDirection.z -= mMove;          
		break;      
	case OIS::KC_LEFT:      
	case OIS::KC_A:          
		mDirection.x += mMove;          
		break;      
	case OIS::KC_RIGHT:      
	case OIS::KC_D:          
		mDirection.x -= mMove;          
		break;      
	case OIS::KC_PGDOWN:      
	case OIS::KC_E:
		mDirection.y += mMove;          
		break;      
	case OIS::KC_PGUP:      
	case OIS::KC_Q:          
		mDirection.y -= mMove;          
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


