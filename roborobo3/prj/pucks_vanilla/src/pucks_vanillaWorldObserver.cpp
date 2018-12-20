/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "pucks_vanilla/include/pucks_vanillaWorldObserver.h"
#include "pucks_vanilla/include/pucks_vanillaController.h"
#include "pucks_vanilla/include/pucks_vanillaSharedData.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "RoboroboMain/roborobo.h"

pucks_vanillaWorldObserver::pucks_vanillaWorldObserver( World* world ) : TemplateEEWorldObserver( world )
{
    // superclass constructor called before
}

pucks_vanillaWorldObserver::~pucks_vanillaWorldObserver()
{
    // superclass destructor called before
}

void pucks_vanillaWorldObserver::initPre()
{
    // nothing to do.
}

void pucks_vanillaWorldObserver::initPost()
{
    // nothing to do.
}

void pucks_vanillaWorldObserver::stepPre()
{
    TemplateEEWorldObserver::stepPre();
    /*
    // EXAMPLE
    if( gWorld->getIterations() > 0 && gWorld->getIterations() % TemplateEESharedData::gEvaluationTime == 0 )
    {
        std::cout << "[INFO] new generation.\n";
    }
    */
}

void pucks_vanillaWorldObserver::stepPost( )
{
    TemplateEEWorldObserver::stepPost();
}

void pucks_vanillaWorldObserver::monitorPopulation( bool localVerbose )
{
    TemplateEEWorldObserver::monitorPopulation(localVerbose);
}
