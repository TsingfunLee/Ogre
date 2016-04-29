#include "Ogre\ExampleApplication.h"
#include "ogre\SdkTrays.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace OgreBites;

class TutorialFrameListener : public Ogre::FrameListener, public OIS::MouseListener, public
	OIS::KeyListener,public SdkTrayListener 
{
public:
	TutorialFrameListener(RenderWindow* win, std::vector<Ogre::Camera*>& camVec, std::vector<Ogre::Viewport*>& vpVec,SceneManager *sceneMgr)
	{
		// Populate the camera and scene manager containers

		size_t windowHnd = 0;
		std::stringstream windowHndStr;
		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		_man = OIS::InputManager::createInputSystem( pl );
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard,
			true ));
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject( OIS::OISMouse,
			true ));

		mCamNode = camVec[0]->getParentSceneNode();
		mSceneMgr = sceneMgr;
		// 设置旋转和移动速度
		mRotate = 0.13;
		mMove = 250;
		// 继续渲染
		mContinue = true;
		_currentCam=camVec[0];

		_node=sceneMgr->getSceneNode("SinbadNode");

		_mouse->setEventCallback(this);
		_key->setEventCallback(this);

		mDirection = Vector3::ZERO;
		const OIS::MouseState &ms =_mouse->getMouseState();
		ms.height = win->getHeight();
		ms.width = win->getWidth();
		_entity=sceneMgr->getEntity("Sinbad");

		_aniState = _entity->getAnimationState("RunBase");
		_aniState->setLoop(false);
		_aniStateTop = _entity->getAnimationState("RunTop");
		_aniStateTop->setLoop(false);

		_walked=false;
		_WalkingSpeed = 100.0f;
		_rotation = 0.0f;


		_WalkingSpeed = 50.0f;
		_rotation = 0.0f;
		_SinbadTranslate=Ogre::Vector3(0,0,0);
		_camVec=camVec;
		_vpVec=vpVec;


		vpVec[3]->setDimensions(0,0,1,1);
		vpVec[3]->setCamera(_currentCam);
		bOneViewport=true;

		mWalkMode = true;

		//add
		//rayquery
		mRaySceneQuery = mSceneMgr->createRayQuery(Ray());
		//add

		//sdktray
		mTrayMgr = new SdkTrayManager("SampleControls", win, _mouse,this);
		//mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
		//mTrayMgr->showLogo(TL_BOTTOMRIGHT);

		mDestination = Ogre::Vector3::ZERO;
		mDir = Ogre::Vector3::ZERO;
		Real mDistance = 0;

		_meshName = "robot.mesh";

		CreateUI();
	}

	~TutorialFrameListener()
	{
		mSceneMgr->destroyQuery(mRaySceneQuery);
	}

	bool nextLocation()
	{
		if (mWalkList.empty())
			return false;
		//cout<<"asdfa"<<endl;
		mDestination = mWalkList.back(); // this gets the front of the deque
		mWalkList.pop_back(); // this removes the front of the deque
		mDir = mDestination - _node->getPosition();
		mDir.y = 0;
		mDistance = mDir.normalise();
		Vector3 src = _node->getOrientation() * Vector3::UNIT_Z;
		if ((1.0f + src.dotProduct(mDir)) < 0.0001f)
		{
			_node->yaw(Degree(180));
		}
		else
		{
			Ogre::Quaternion quat = src.getRotationTo(mDir);
			_node->rotate(quat);
			//cout<<quat<<endl;
		} // else
		return true;
	}

	void addModel()
	{
		Ray mouseRay = mTrayMgr->getCursorRay(_camVec[0]);
		mRaySceneQuery->setRay(mouseRay);
		RaySceneQueryResult &result3 = mRaySceneQuery->execute();        
		RaySceneQueryResult::iterator itr3 = result3.begin();
	
		if (itr3 != result3.end() && itr3->worldFragment)       
		{           
			char name[16];
			static int count = 0;
			sprintf(name,"robot%d",count++);
			Entity* ent = mSceneMgr->createEntity(name,_meshName);
			currentNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(String(name)+"Node",itr3->worldFragment->singleIntersection);
			currentNode->attachObject(ent);
			currentNode->setScale(0.1f,0.1f,0.1f);
		} 
	}

	void MoveByMouse()
	{
		Ray mouseRay = mTrayMgr->getCursorRay(_camVec[0]);
		mRaySceneQuery->setRay(mouseRay);
		RaySceneQueryResult &result = mRaySceneQuery->execute();        
		RaySceneQueryResult::iterator itr = result.begin();
		if (itr != result.end() && itr->worldFragment)       
		{           
			//_node->translate(itr->worldFragment->singleIntersection);
			Vector3 walkList(itr->worldFragment->singleIntersection);
			mWalkList.push_back(walkList);
		} 
		mWalkMode = true;
		
	}

	void move(const FrameEvent &evt)
	{
		if (mDir == Vector3::ZERO)
		{
			if (nextLocation())
			{
				// Set walking animation
				/*mAnimationState = mEntity->getAnimationState("Walk");
				mAnimationState->setLoop(true);
				mAnimationState->setEnabled(true);*/
				_walked = true;
			}
		}
		else
		{
			Real move = _WalkingSpeed * evt.timeSinceLastFrame;
			mDistance -= move;
			if (mDistance <= 0.0f)
			{
				_node->setPosition(mDestination);
				mDir = Vector3::ZERO;
				// Set animation based on if the robot has another point to walk to.
				if (! nextLocation())
				{
					// Set Idle animation
					/*_aniState = _entity->getAnimationState("Idle");
					_aniState->setLoop(true);
					_aniState->setEnabled(true);*/
					_walked = false;
				}
				else
				{
					// Rotation Code will go here later
				}
			}
			else
			{
				_node->translate(mDir * move);
			} // else
		} // if
	}

	bool frameStarted(const FrameEvent &evt)
	{
		//sdktrays
		mTrayMgr->refreshCursor();
		mTrayMgr->frameRenderingQueued(evt);
		//sdktrays

		//add
		Vector3 camPos = _camVec[0]->getPosition();       
		Ray cameraRay(Vector3(camPos.x, 5000.0f, camPos.z), Vector3::NEGATIVE_UNIT_Y);        
		mRaySceneQuery->setRay(cameraRay); 

		// Perform the scene query        
		RaySceneQueryResult &result = mRaySceneQuery->execute();        
		RaySceneQueryResult::iterator itr = result.begin(); 
		// Get the results, set the camera height       
		if (itr != result.end() && itr->worldFragment)       
		{           
			Real terrainHeight = itr->worldFragment->singleIntersection.y;            
			if ((terrainHeight + 10.0f) > camPos.y)                
				_camVec[0]->setPosition( camPos.x, terrainHeight + 10.0f, camPos.z );        
		} 
		//add
		//add
		Vector3 sinbadPos = _node->getPosition();
		Ray sinbadRay(Vector3(sinbadPos.x, 5000.0f, sinbadPos.z), Vector3::NEGATIVE_UNIT_Y);
		mRaySceneQuery->setRay(sinbadRay);
		//perform the scene query
		RaySceneQueryResult &result2 = mRaySceneQuery->execute();
		RaySceneQueryResult::iterator itr2 = result2.begin();
		//get the results, set the sinbad height
		if(itr2!=result2.end()&&itr2->worldFragment)
		{
			Real terrainHeight = itr2->worldFragment->singleIntersection.y;
			cout<<terrainHeight<<endl;
			if(terrainHeight>sinbadPos.y)
			{
				_node->setPosition(sinbadPos.x,terrainHeight,sinbadPos.z);
			}
		}
		//add
		_aniState->addTime(evt.timeSinceLastFrame);
		_aniStateTop->addTime(evt.timeSinceLastFrame);

		if(_mouse)
			_mouse->capture();
		if(_key)
			_key->capture();

		if(_walked)
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

		if(!mWalkMode)
		{
			_node->translate(_SinbadTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
			_node->resetOrientation();
			_node->yaw(Ogre::Radian(_rotation));
		}	

		mCamNode->translate(mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL);
		/*	_SinbadTranslate=Ogre::Vector3(0,0,0);*/

		//moveCamera();

		//move
		move(evt);
		//move

		return mContinue;
	}

	bool mouseMoved(const OIS::MouseEvent &e)
	{
		//sdktrays
		mTrayMgr->injectMouseMove(e);

		if (e.state.buttonDown(OIS::MB_Right))
		{
			mCamNode->yaw(Degree(-mRotate * e.state.X.rel), Node::TS_WORLD);
			mCamNode->pitch(Degree(-mRotate * e.state.Y.rel), Node::TS_LOCAL);
		}

		return true;
	}


	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {

		mTrayMgr->injectMouseDown(e,id);

		if(e.state.buttonDown(OIS::MB_Left))
		{
			addModel();
			MoveByMouse();
		}

		return true;	

	}


	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) 
	{ 
		mTrayMgr-> injectMouseUp (e,id);

		return true; 
	}

	// KeyListener
	bool keyPressed(const OIS::KeyEvent &e) { 

		if(e.key==OIS::KC_SPACE)
		{
			if(bOneViewport)
			{
				setOneOrFourViewport(false);
				bOneViewport=false;
			}
			else
			{
				setOneOrFourViewport(true);
				bOneViewport=true;
			}
		}

		if(e.key==OIS::KC_TAB)
		{
			if(!bOneViewport)
			{			
				if(_currentCam==_camVec[0])
				{
					_currentCam=_camVec[1];
					mCamNode = _currentCam->getParentSceneNode();
				}
				else if(_currentCam==_camVec[1])
				{
					_currentCam=_camVec[2];
					mCamNode = _currentCam->getParentSceneNode();
				}
				else if(_currentCam==_camVec[2])
				{
					_currentCam=_camVec[3];
					mCamNode = _currentCam->getParentSceneNode();
				}
				else if(_currentCam==_camVec[3])
				{
					_currentCam=_camVec[0];
					mCamNode = _currentCam->getParentSceneNode();
				}
			}
		}

		_SinbadTranslate=Ogre::Vector3(0,0,0);
		ControlRole(e);
		ControlCam(e);

		return true;

	}

	void ControlRole(const OIS::KeyEvent &eRole)
	{
		mWalkMode = false;

		switch (eRole.key)
		{

		case OIS::KC_UP:
			//case OIS::KC_W:
			_SinbadTranslate += Ogre::Vector3(0,0,-1);
			_rotation = 3.14f;
			_walked = true;
			break;

		case OIS::KC_DOWN:
			//case OIS::KC_S:
			_SinbadTranslate += Ogre::Vector3(0,0,1);
			_rotation = 0.0f;
			_walked = true;
			break;

		case OIS::KC_LEFT:
			//case OIS::KC_A:
			_SinbadTranslate += Ogre::Vector3(-1,0,0);
			_rotation = -1.57f;
			_walked = true;
			break;

		case OIS::KC_RIGHT:
			//case OIS::KC_D:
			_SinbadTranslate += Ogre::Vector3(1,0,0);
			_rotation = 1.57f;
			_walked = true;
			break;

		}

	}

	void ReleaseRole(const OIS::KeyEvent &eRole)
	{
		switch (eRole.key)
		{

		case OIS::KC_UP:
			ResetAnim();

			break;

		case OIS::KC_DOWN:
			ResetAnim();

			break;

		case OIS::KC_LEFT:
			ResetAnim();

			break;

		case OIS::KC_RIGHT:
			ResetAnim();

			break;

		}


	}

	void ControlCam(const OIS::KeyEvent &eCam)
	{
		switch (eCam.key)
		{
		case OIS::KC_ESCAPE:
			mContinue = false;
			break;

			//case OIS::KC_UP:
		case OIS::KC_W:
			mDirection.z += mMove;
			break;

			//case OIS::KC_DOWN:
		case OIS::KC_S:
			mDirection.z -= mMove;
			break;

			//case OIS::KC_LEFT:
		case OIS::KC_A:
			mDirection.x += mMove;
			break;

			//case OIS::KC_RIGHT:
		case OIS::KC_D:
			mDirection.x -= mMove;
			break;

		}

	}

	void ResetAnim()
	{
		if(_walked)
		{
			_aniState->setEnabled(false);
			_aniStateTop->setEnabled(false);
			if(_aniState->hasEnded())
			{
				_aniState->setTimePosition(0.0f);
			}
			if(_aniStateTop->hasEnded())
			{
				_aniStateTop->setTimePosition(0.0f);
			}

			_walked=false;
			_SinbadTranslate=Ogre::Vector3(0,0,0);

		}

	}

	void ReleaseCam(const OIS::KeyEvent &eCam)
	{
		switch (eCam.key)
		{

			//case OIS::KC_UP:
		case OIS::KC_W:
			mDirection.z -= mMove;
			break;

			//case OIS::KC_DOWN:
		case OIS::KC_S:
			mDirection.z += mMove;
			break;

			//case OIS::KC_LEFT:
		case OIS::KC_A:
			mDirection.x -= mMove;
			break;

			//case OIS::KC_RIGHT:
		case OIS::KC_D:
			mDirection.x += mMove;
			break;

		}

	}
	bool keyReleased(const OIS::KeyEvent &e) { 
		ReleaseCam(e);
		ReleaseRole(e);

		return true; 

	}

	void setOneOrFourViewport(bool one)
	{
		if(one)
		{
			_vpVec[3]->setDimensions(0,0,1,1);
			_vpVec[3]->setCamera(_currentCam);

		}
		else
		{
			_vpVec[3]->setDimensions(0.5,0.5,0.5,0.5);
			_vpVec[3]->setCamera(_camVec[3]);

		}
	}

	void CreateUI()
	{
		Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
		Ogre::FontManager::getSingleton().getByName("SdkTrays/Value")->load();

		//selectMenu
		selectMenu=mTrayMgr->createThickSelectMenu(OgreBites::TL_TOP, "selectMenu", "MySelectMenu", 200, 200 );
		//selectMenu->setCaption(Ogre::DisplayString(L"SelectModel"));
		selectMenu->addItem( "Robot" );
		selectMenu->addItem( "Ninja" );
		selectMenu->addItem( "Sinbad" );
		//button
		button      = mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT,"button","MyButton",200);
		//textbox
		textBox		= mTrayMgr->createTextBox( OgreBites::TL_NONE, "textBox", "MyTextBox", 200, 100 );
		//separator
		separator	= mTrayMgr->createSeparator( OgreBites::TL_TOPRIGHT, "MySeparator", 200 );
		//paramsPanel
		Ogre::StringVector paramsPanelItems;
		paramsPanelItems.push_back("Life");
		paramsPanelItems.push_back("Speed");
		paramsPanelItems.push_back("Magic");
		paramsPanel	= mTrayMgr->createParamsPanel(OgreBites::TL_LEFT, "paramsPanel", 200 ,paramsPanelItems);
		//label
		label		= mTrayMgr->createLabel( OgreBites::TL_CENTER, "label", "Welcome to Ogre!", 500 );
		//slider
		slider		= mTrayMgr->createThickSlider( OgreBites::TL_RIGHT, "slider", "MySlider", 200, 80, 0, 100, 100);
		//checkbox
		checkbox	= mTrayMgr->createCheckBox(OgreBites::TL_BOTTOMLEFT, "checkbox",  "MyCheckBox", 200 );
		//progressBar
		progressBar	= mTrayMgr->createProgressBar( OgreBites::TL_BOTTOM, "progressBar", "MyProgressBar", 200, 100);
		progressBar->setProgress(0.5);
	}

	void buttonHit(Button* button) 
	{
		label->setCaption("You click botton!");
	}
	void itemSelected(SelectMenu* pmenu) 
	{
		pmenu = selectMenu;
		_meshName = pmenu->getSelectedItem()+".mesh";
	}
	void labelHit(Label* plabel) 
	{
		plabel = label;
		String message("You click label!");
		label->setCaption(message);
	}
	void sliderMoved(Slider* pslider) 
	{
		pslider = slider;
		String massage("");
		massage.append(Ogre::StringConverter::toString(pslider->getValue()));
		label->setCaption(massage);
	}
    void checkBoxToggled(CheckBox* pbox) 
	{
		pbox = checkbox;
		if(pbox->isChecked())
		{
			pbox->setCaption("You checked!");
		}
		else {
			pbox->setCaption("MyCheckBox");
		}
	}

protected:
	Real mRotate; // The rotate constant
	Real mMove; // The movement constant
	SceneManager *mSceneMgr; // The current SceneManager
	SceneNode *mCamNode; // The SceneNode the camera is currently attached to
	bool mContinue; // Whether to continue rendering or not
	Vector3 mDirection; // Value to move in the correct direction

	Ogre::AnimationState* _aniState;

	Ogre::AnimationState* _aniStateTop;
	Ogre::Entity* _entity;

	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;

	float _WalkingSpeed;
	float _rotation;
	Ogre::Vector3 _SinbadTranslate;
	bool _walked;

	Ogre::SceneNode* _node;
	Camera* _currentCam;

	std::vector<Ogre::Camera*> _camVec;
	std::vector<Ogre::Viewport*> _vpVec;

	bool bOneViewport;

	bool mWalkMode;

	//add
	RaySceneQuery* mRaySceneQuery;
	//add

	//cegui
	SdkTrayManager* mTrayMgr;
	//cegui

	//sinbad move
	Ogre::SceneNode* currentNode;
	std::vector<Vector3> mWalkList;
	Vector3 mDestination;
	Vector3 mDir;
    Real mDistance;
	//sinbad move
private:
	//Widgets
	OgreBites::Button *button;
	OgreBites::TextBox *textBox;
	OgreBites::SelectMenu *selectMenu;
	OgreBites::Label *label;
	OgreBites::Separator *separator;
	OgreBites::Slider *slider;
	OgreBites::ParamsPanel *paramsPanel;
	OgreBites::CheckBox *checkbox;
	OgreBites::ProgressBar *progressBar;
	// name of the model creating 
	String _meshName;
};