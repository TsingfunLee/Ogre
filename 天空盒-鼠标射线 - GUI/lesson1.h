#include "Ogre\ExampleApplication.h"
#include "New2Listner.h"

class Exampl1:public ExampleApplication
{
public:

	Exampl1()
	{
		cam1=NULL;
		cam2=NULL;

		mNewFrameListener=NULL;


		//cam3=NULL;

	}

	~Exampl1()
	{
		if(mNewFrameListener!=NULL)
		{
			delete mNewFrameListener;

		}
	}
	void createScene();

	void createCamera();

	void createViewports();

	void createFrameListener();

	Ogre::Viewport* createViewport(Ogre::Camera* cam,int zorder);
	void createFourViewport();

	void chooseSceneManager();


private:
	Ogre::Camera* cam1;
	Ogre::Camera* cam2;

	std::vector<Ogre::Camera*> _camVec;

	std::vector<Ogre::Viewport*> _vpVec;

	Ogre::SceneNode* _SinbadNode;
	Ogre::SceneNode* _SinbadNode2;

	Ogre::SceneNode* _Robot;

	Ogre::FrameListener* mNewFrameListener;

	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneManager* mSceneMgr2;

	//std::vector<Vector3> walkList;

};

//void Exampl1::createScene()
//{
//
//}