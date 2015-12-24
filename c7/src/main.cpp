/*
Commands
T: Terminate the app
G: Clear, or Win the game
B: Faill, or Lose the game
*/

#include "GameLib/Framework.h"
#include "App.h"

// global value
App* gApp = 0;

namespace GameLib
{
	void Framework::update()
	{
		if (!gApp)
		{
			gApp = new App();
		}

		gApp->update();

		if (isKeyOn('T'))
		{
			requestEnd();
		}

		if (isEndRequested())
		{
			SAFE_DELETE(gApp);
			return;
		}		
	}
} // namespace GameLib
