#include "Ogre\ExampleApplication.h"

class ExampleFrameListener1:public ExampleFrameListener,public OIS::MouseListener,public OIS::KeyListener
{
public:
	ExampleFrameListener1(Ogre::SceneManager* sceneMgr,RenderWindow* win,Ogre::Camera* cam);
	~ExampleFrameListener1();
	bool frameStarted(const Ogre::FrameEvent &evt);
	// MouseListener    
	bool mouseMoved(const OIS::MouseEvent &e);    
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);    
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);     
	// KeyListener    
	bool keyPressed(const OIS::KeyEvent &e); 
	bool keyReleased(const OIS::KeyEvent &e); 
private:
protected:   
	SceneNode* mNode;
	Camera* mCam;
	SceneManager* mSceneMgr;

	//camera rotate
	Real mRotate;          
	//camera movement
	Real mMove;            
	// Whether to continue rendering or not          
	bool mContinue;        
    // Value to move in the correct direction
	//camera
	Vector3 mDirection;

	//control node move
	Real mPace;
	Vector3 mTranslate;

	//animation
	AnimationState* mAniStateTop;
	AnimationState* mAniStateBase;
	Entity* mEnt;
	Real mRotation;
	Real mWalkSpeed;
	bool mWalked; 
};