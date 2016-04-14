#include "ExampleFrameListener.h"

class Example:public ExampleApplication
{
public:
	Example();
	~Example();
	void createScene();
	void createCamera();
	void createFrameListener();
private:
	Ogre::SceneNode* _SinbadNode;
	Ogre::FrameListener* FrameListener;
};