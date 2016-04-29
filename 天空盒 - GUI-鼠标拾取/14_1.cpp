// lesson.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "ogre/ExampleApplication.h"
#include <iostream>
#include <deque>
#include "ogre\SdkTrays.h"
using namespace  OgreBites;
using namespace std;


void getHeightfromTerrain(Ogre::SceneNode* node,RaySceneQuery* raySceneQuery,Real delta)
{
	Vector3 camPos = node->getPosition();
	Ray cameraRay(Vector3(camPos.x, 5000.0f, camPos.z), Vector3::NEGATIVE_UNIT_Y);
	raySceneQuery->setRay(cameraRay);
	//raySceneQuery->setQueryMask()

	RaySceneQueryResult &result = raySceneQuery->execute();
	//_RaySceneQuery
	RaySceneQueryResult::iterator itr = result.begin();
	//itr->movable
	if (itr != result.end() && itr->worldFragment)
	{
		Real terrainHeight = itr->worldFragment->singleIntersection.y;		
		node->setPosition( camPos.x, terrainHeight +delta, camPos.z );
	}

}



void getHeightfromTerrain(Ogre::Camera* cam,RaySceneQuery* raySceneQuery,Real delta)
{
	Vector3 camPos = cam->getPosition();
	Ray cameraRay(Vector3(camPos.x, 5000.0f, camPos.z), Vector3::NEGATIVE_UNIT_Y);
	raySceneQuery->clearResults();
	raySceneQuery->setRay(cameraRay);
	raySceneQuery->setQueryMask(0);

	RaySceneQueryResult &result = raySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();
	if (itr != result.end() && itr->worldFragment)
	{
		Real terrainHeight = itr->worldFragment->singleIntersection.y;
		if ((terrainHeight +delta) > camPos.y)
			cam->setPosition( camPos.x, terrainHeight + delta, camPos.z );
	}
}

void createNodeAndModel(Ogre::SceneManager* pSceneManager,char* nodeName,char* meshName,char* mesh,float scale)
{
	Entity *ent = pSceneManager->createEntity(meshName, mesh);
	Ogre::SceneNode *pNode=pSceneManager->createSceneNode(nodeName);
	pNode->attachObject(ent);
	pNode->setScale(scale,scale,scale);
}

class BufferFrameListener:public Ogre::FrameListener,public OIS::MouseListener,public OIS::KeyListener,public SdkTrayListener
{

private:
	enum QueryFlags
	{
		NINJA_MASK = 1<<0,
		ROBOT_MASK = 1<<1
	};

	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::SceneNode* _Node;

	Ogre::Camera* _cam;
	Ogre::Entity* _Ent;

	SceneManager* _sceneManager;
	RaySceneQuery* _RaySceneQuery;
	SdkTrayManager* mTrayMgr;
	SceneNode *mCurrentObject; // 新创建的物体

	int mCount;
	bool mLMouseDown;
	bool mRMouseDown;
	bool mRobotMode; // The current state
	uint32 mDefailtFlag;
	OgreBites::SelectMenu *selectMenu;
	Ogre::String _ModelName;

	bool Continue;
public:
	void CreateUI()
	{
		//mTrayMgr->showLogo(TL_LEFT);
		Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
		Ogre::FontManager::getSingleton().getByName("SdkTrays/Value")->load();
		//mTrayMgr->showAll();

		//mTrayMgr->showFrameStats(TL_TOPLEFT);
		
		selectMenu=mTrayMgr->createThickSelectMenu(OgreBites::TL_TOP, "selectMenu", "", 200, 200 );
		selectMenu->setCaption(Ogre::DisplayString(L"SelectModel"));
		selectMenu->addItem("Robot");
		selectMenu->addItem( "Ninja" );
		selectMenu->addItem( "Sinbad" );
	}

	BufferFrameListener(Ogre::SceneNode* node,RenderWindow* win,Ogre::Camera* cam,Ogre::Entity* ent,SceneManager* sceneManager){

		size_t windowHnd=0;
		std::stringstream windowHndStr;
		win->getCustomAttribute("WINDOW",&windowHnd);
		windowHndStr<<windowHnd;
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"),windowHndStr.str()));
		_man=OIS::InputManager::createInputSystem(pl);

		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard,true ));

		_mouse=static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse,true));
		_key->setEventCallback(this);
		_mouse->setEventCallback(this);	
		mTrayMgr = new SdkTrayManager("SampleControls", win, _mouse,this);

		const OIS::MouseState &ms=_mouse->getMouseState();
		ms.height=win->getHeight();
		ms.width=win->getWidth();

		_Ent=ent;

		_sceneManager=sceneManager;
		_RaySceneQuery=_sceneManager->createRayQuery(Ray());

		mDefailtFlag=_RaySceneQuery->getQueryMask();

		_Node=node;
		_cam=cam;

		Continue=true;

		mCount = 0;
		mCurrentObject = NULL;
		mLMouseDown = false;
		mRMouseDown = false;
		_ModelName="robot.mesh";

		 CreateUI();
	}

	virtual bool mouseMoved( const OIS::MouseEvent &arg )
	{

		Ogre::Vector3 translate3(0.0f,0.0f,0.0f);
		translate3.z+=-0.02f * arg.state.Z.rel;

		float rotX=arg.state.X.rel*-0.001;
		float rotY=arg.state.Y.rel*-0.001;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(translate3);
		mTrayMgr->injectMouseMove(arg);

		return 0;	

	}

	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		if(id==OIS::MB_Left)
		{
			if (mCurrentObject)
				mCurrentObject->showBoundingBox(false);

			mLMouseDown = true;

			Ray mouseRay=mTrayMgr->getCursorRay(_cam);
			_RaySceneQuery->setRay(mouseRay);
			_RaySceneQuery->setSortByDistance(true);

			_RaySceneQuery->setQueryMask(ROBOT_MASK|NINJA_MASK);
			//_RaySceneQuery->setQueryMask(mRobotMode ? ROBOT_MASK : NINJA_MASK);
			// Execute query
			RaySceneQueryResult &result = _RaySceneQuery->execute();
			RaySceneQueryResult::iterator itr ;

			// Get results, create a node/entity on the position
			for (itr = result.begin(); itr != result.end(); itr++)
			{
				if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[")
				{
					mCurrentObject = itr->movable->getParentSceneNode();
					break;
				} // if
				else if (itr->worldFragment)
				{
					Entity *ent;
					char name[16];
					Ogre::Vector3 pos;
					if (mRobotMode)
					{
						sprintf(name, "Robot%d", mCount++);
						ent = _sceneManager->createEntity(name, _ModelName);
						ent->setQueryFlags(ROBOT_MASK);
					} // if
					else
					{
						sprintf(name, "Ninja%d", mCount++);
						ent = _sceneManager->createEntity(name, "ninja.mesh");
						ent->setQueryFlags(NINJA_MASK);
					} // else


					mCurrentObject = _sceneManager->getRootSceneNode()->createChildSceneNode(String(name) + "Node");
					mCurrentObject->attachObject(ent);

					if(_ModelName=="Sinbad")
					{
						pos=itr->worldFragment->singleIntersection;
						pos.y+=15;
						mCurrentObject->setScale(10.0f, 10.0f, 10.0f);
						mCurrentObject->setPosition(pos);
					}
					else if(_ModelName=="Ninja")
					{
						pos=itr->worldFragment->singleIntersection;
						mCurrentObject->setScale(0.05f, 0.05f, 0.05f);
						mCurrentObject->setPosition(pos);

					}
					else if(_ModelName=="Robot")
					{
						pos=itr->worldFragment->singleIntersection;
						mCurrentObject->setScale(0.1f, 0.1f, 0.1f);
						mCurrentObject->setPosition(pos);
					}
					else
					{
						pos=itr->worldFragment->singleIntersection;
						//mCurrentObject->setScale(0.2f, 0.2f, 0.2f);
						mCurrentObject->setPosition(pos);
					}
					
					break;
				} // else if
			} // for
			if (mCurrentObject)
				mCurrentObject->showBoundingBox(true);
			//mLMouseDown = true;			
		}

		if(id==OIS::MB_Right)
		{

			mRMouseDown = true;

		}
		mTrayMgr->injectMouseDown(arg,id);

		return 0;	

	}
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
	{
		if (id == OIS::MB_Left)
		{
			mLMouseDown = false;
		} // if
		// Right mouse button up
		else if (id == OIS::MB_Right)
		{
			mRMouseDown = false;
		} 
		mTrayMgr-> injectMouseUp (arg,id);


		return 0;		
	}

	virtual bool keyPressed(const OIS::KeyEvent &arg)
	{
		//Ogre::Vector3 translate(0,0,0);

		switch(arg.key)
		{
		case OIS::KC_ESCAPE:
			Continue=false;
			return false;
			break;
		case OIS::KC_SPACE:
			mRobotMode = !mRobotMode;
			//mTimeUntilNextToggle = 1;

			break;

		}


		return true;		
	}
	virtual bool keyReleased(const OIS::KeyEvent &arg)
	{

		if(arg.key==OIS::KC_P)
		{
			if(_cam->getPolygonMode()==PM_WIREFRAME)
			{
				_cam->setPolygonMode(PM_POINTS);

			}
			else if(_cam->getPolygonMode()==PM_POINTS)
			{
				_cam->setPolygonMode(PM_SOLID);
			}
			else
			{
				_cam->setPolygonMode(PM_WIREFRAME);

			}
		}


		return 0;	

	}
	bool frameStarted(const Ogre::FrameEvent &evt)
	{

		bool walked=false;
		Ogre::Vector3 SinbadTranslate(0,0,0);


		Ogre::Vector3 translate2(0.0f,0.0f,0.0f);
		Ogre::Vector3 translate(0.0f,0.0f,0.0f);
		_key->capture();
		_mouse->capture();
		mTrayMgr->refreshCursor();
		mTrayMgr->frameRenderingQueued(evt);
		//_key

		if(_key->isKeyDown(OIS::KC_UP))
		{
			translate+=Ogre::Vector3(0,0,-20);
		}
		if(_key->isKeyDown(OIS::KC_DOWN))
		{
			translate+=Ogre::Vector3(0,0,20);		
		}
		if(_key->isKeyDown(OIS::KC_LEFT))
		{
			translate+=Ogre::Vector3(-20,0,0);		
		}
		if(_key->isKeyDown(OIS::KC_RIGHT))
		{
			translate+=Ogre::Vector3(20,0,0);		
		}		

		_cam->moveRelative(translate* evt.timeSinceLastFrame);		

		getHeightfromTerrain(_cam,_RaySceneQuery,10);
		getHeightfromTerrain(_Node,_RaySceneQuery,15);

		if (mLMouseDown)
		{

			Ray mouseRay = mTrayMgr->getCursorRay(_cam);
			_RaySceneQuery->setRay(mouseRay);
			_RaySceneQuery->setQueryMask(0);
			RaySceneQueryResult &result = _RaySceneQuery->execute();
			RaySceneQueryResult::iterator itr = result.begin();
			if (itr != result.end() && itr->worldFragment)
			{
				if(_ModelName=="Sinbad")
				{
					Ogre::Vector3 pos=itr->worldFragment->singleIntersection;
					pos.y+=15;

					mCurrentObject->setPosition(pos);
					
				}
				else
					mCurrentObject->setPosition(itr->worldFragment->singleIntersection);
			}

		} 

		return Continue;	

	}

	void itemSelected(OgreBites::SelectMenu* menu) {
		 Ogre::String SelectItem=menu->getSelectedItem();

		if(SelectItem=="Robot")
		{
			_ModelName="Robot.mesh";
		}
		else if(SelectItem=="Sinbad")
		{
			_ModelName="Sinbad.mesh";
		}
		else if(SelectItem=="Ninja")
		{
			_ModelName="Ninja.mesh";
		}
	}

};


class lesson: public ExampleApplication
{
private:
	Ogre::SceneNode* _SinbadNode;
	Ogre::SceneNode* _SinbadNode2;

	Ogre::Entity* _Sinbad2;
	Ogre::Entity* _Sinbad;

	Ogre::FrameListener* FrameListener;
	Ogre::FrameListener* _MoveFramListener;
	SceneManager* _SceneManage2;

	Camera* _camera2;

	//	OIS::Mouse
public:
	lesson()
	{
		FrameListener=NULL;
		_SinbadNode=NULL;

	}
	~lesson()
	{
		if(FrameListener!=NULL)
		{
			delete FrameListener;

		}
	}

	virtual void createViewports()
	{

		Ogre::Viewport* vp=mWindow->addViewport(mCamera,0,0,0,1,1);
		vp->setBackgroundColour(ColourValue(0,0,1));

		mCamera->setAspectRatio(float(vp->getActualWidth())/float(vp->getActualHeight()));

	}


	virtual void createCamera()
	{

		mCamera=mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,100,200);
		mCamera->lookAt(0,0,0);
		mCamera->setNearClipDistance(5);

	}

	virtual void createScene(void)
	{

		Ogre::Light*light =mSceneMgr->createLight("Light1");
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(Ogre::Vector3(1,-1,0));

		Ogre::SceneNode*node=mSceneMgr->createSceneNode("Node1");
		mSceneMgr->getRootSceneNode()->addChild(node);

		_Sinbad=mSceneMgr->createEntity("Sinbad","Sinbad.mesh");
		_SinbadNode=node->createChildSceneNode("SinbadNode");
		_SinbadNode->setScale(3.0f,3.0f,3.0f);
		_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
		_SinbadNode->attachObject(_Sinbad);


		_Sinbad2=mSceneMgr->createEntity("Sinbad2","robot.mesh");
		_SinbadNode2=node->createChildSceneNode("SinbadNode2");
		_SinbadNode2->setScale(0.2f,0.2f,0.2f);
		_SinbadNode2->setPosition(Ogre::Vector3(200.0f,-10.0f,200.0f));
		_SinbadNode2->attachObject(_Sinbad2);

		Ogre::Entity* sword1=mSceneMgr->createEntity("Sword1","Sword.mesh");
		Ogre::Entity* sword2=mSceneMgr->createEntity("Sword2","Sword.mesh");

		_Sinbad->attachObjectToBone("Handle.L",sword1);
		_Sinbad->attachObjectToBone("Handle.R",sword2);

		mSceneMgr->setSkyDome(true,"Examples/CloudySky",5,8);

		mSceneMgr->setWorldGeometry("terrain.cfg");

		mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	}

	virtual void createFrameListener(void)
	{

		FrameListener=new BufferFrameListener(_SinbadNode,mWindow,mCamera,_Sinbad,mSceneMgr);
		mRoot->addFrameListener(FrameListener);

	}

	virtual void chooseSceneManager(void)
	{
		// Create the SceneManager, in this case a generic one
		mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE, "Example1");

	}

};

//int _tmain(int argc, _TCHAR* argv[])
//{
//	lesson theApp;
//	theApp.go();
//
//	return 0;
//}

int main()
{
	lesson theApp;
	theApp.go();

	return 0;
}

