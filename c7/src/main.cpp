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
