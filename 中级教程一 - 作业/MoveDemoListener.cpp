#include "MoveDemoListener.h"

MoveDemoListener::MoveDemoListener(RenderWindow* win, Camera* cam, SceneNode *sn,
	Entity *ent, std::deque<Vector3> &walk)
	: ExampleFrameListener(win, cam, false, false), mNode(sn), mEntity(ent), mWalkList(walk)
{
	// Set default values for variables
	mWalkSpeed = 35.0f;
	mDirection = Vector3::ZERO;
} // MoveDemoListener

/* This function is called to start the object moving to the next position
in mWalkList.
*/
bool MoveDemoListener::nextLocation()
{
	if (mWalkList.empty())
		return false;
	mDestination = mWalkList.front(); // this gets the front of the deque
	mWalkList.pop_front(); // this removes the front of the deque
	mDirection = mDestination - mNode->getPosition();
	mDistance = mDirection.normalise();
	Vector3 src = mNode->getOrientation() * Vector3::UNIT_X;
	if ((1.0f + src.dotProduct(mDirection)) < 0.0001f)
	{
		mNode->yaw(Degree(180));
	}
	else
	{
		Ogre::Quaternion quat = src.getRotationTo(mDirection);
		mNode->rotate(quat);
		//add
		mNode->yaw(Degree(-90));
		//add
	} // else
	return true;
} // nextLocation()

bool MoveDemoListener::frameStarted(const FrameEvent &evt)
{
	if (mDirection == Vector3::ZERO)
	{
		if (nextLocation())
		{
			// Set walking animation
			mAnimationState = mEntity->getAnimationState("Walk");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
		}
	}
	else
	{
		Real move = mWalkSpeed * evt.timeSinceLastFrame;
		mDistance -= move;
		if (mDistance <= 0.0f)
		{
			mNode->setPosition(mDestination);
			mDirection = Vector3::ZERO;
			// Set animation based on if the robot has another point to walk to.
			if (! nextLocation())
			{
				// Set Idle animation
				mAnimationState = mEntity->getAnimationState("Idle");
				mAnimationState->setLoop(true);
				mAnimationState->setEnabled(true);
			}
			else
			{
				// Rotation Code will go here later
			}
		}
		else
		{
			mNode->translate(mDirection * move);
		} // else
	} // if
	mAnimationState->addTime(evt.timeSinceLastFrame);
	return ExampleFrameListener::frameStarted(evt);
}