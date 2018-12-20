/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */


#ifndef CROSSOVERAGENTOBSERVER_H
#define CROSSOVERAGENTOBSERVER_H

#include "TemplateEE/include/TemplateEEAgentObserver.h"

class RobotWorldModel;

class crossoverAgentObserver : public TemplateEEAgentObserver
{
	public:
        crossoverAgentObserver( RobotWorldModel *wm );
		~crossoverAgentObserver();

        virtual void step();
};

#endif

