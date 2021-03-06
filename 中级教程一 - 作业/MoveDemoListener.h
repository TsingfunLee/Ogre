#include "Ogre\ExampleApplication.h"

class MoveDemoListener:public ExampleFrameListener
{
public:
	MoveDemoListener(RenderWindow* win, Camera* cam, SceneNode *sn,
		Entity *ent, std::deque<Vector3> &walk);
	bool nextLocation();
	bool frameStarted(const FrameEvent &evt);
protected:
	Real mDistance; // The distance the object has left to travel
	Vector3 mDirection; // The direction the object is moving
	Vector3 mDestination; // The destination the object is moving towards
	AnimationState *mAnimationState; // The current animation state of the object
	Entity *mEntity; // The Entity we are animating
	SceneNode *mNode; // The SceneNode that the Entity is attached to
	std::deque<Vector3> mWalkList; // The list of points we are walking to
	Real mWalkSpeed; // The speed at which the object is moving
};