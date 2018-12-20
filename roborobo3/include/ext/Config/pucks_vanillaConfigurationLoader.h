/*
 * pucks_vanillaConfigurationLoader.h
 */

#ifndef PUCKS_VANILLACONFIGURATIONLOADER_H
#define PUCKS_VANILLACONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class pucks_vanillaConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		pucks_vanillaConfigurationLoader();
		~pucks_vanillaConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};



#endif
