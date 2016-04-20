#include "MoveDemoApplication.h"

int main(int argc, char **argv)
{
	// Create application object
	MoveDemoApplication app;
	try {
		app.go();
	} catch(Exception& e){
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!",
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n",
			e.getFullDescription().c_str());
#endif
	}
	return 0;
}