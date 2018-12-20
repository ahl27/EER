/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#ifndef PUCKS_VANILLAAGENTOBSERVER_H
#define PUCKS_VANILLAAGENTOBSERVER_H

#include "TemplateEE/include/TemplateEEAgentObserver.h"

class RobotWorldModel;

class pucks_vanillaAgentObserver : public TemplateEEAgentObserver
{
	public:
		pucks_vanillaAgentObserver(RobotWorldModel *wm);
		~pucks_vanillaAgentObserver();

    
        virtual void step();
};

#endif

