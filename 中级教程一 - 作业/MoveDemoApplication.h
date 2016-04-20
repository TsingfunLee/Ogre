#include "MoveDemoListener.h"

class MoveDemoApplication : public ExampleApplication
{
protected:
public:
MoveDemoApplication();
~MoveDemoApplication();
protected:
Entity *mEntity; // The entity of the object we are animating
SceneNode *mNode; // The SceneNode of the object we are moving
std::deque<Vector3> mWalkList; // A deque containing the waypoints
void createScene(void);
void createFrameListener(void);
};