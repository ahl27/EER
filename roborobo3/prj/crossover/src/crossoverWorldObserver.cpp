/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "crossover/include/crossoverWorldObserver.h"
#include "crossover/include/crossoverController.h"
#include "crossover/include/crossoverSharedData.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"


crossoverWorldObserver::crossoverWorldObserver( World* world ) : TemplateEEWorldObserver( world )
{
    // superclass constructor called before
}

crossoverWorldObserver::~crossoverWorldObserver()
{
    // superclass destructor called before
}

void crossoverWorldObserver::initPre()
{
    // nothing to do.
}

void crossoverWorldObserver::initPost()
{
    // nothing to do.
}

void crossoverWorldObserver::stepPre()
{
    TemplateEEWorldObserver::stepPre();
}

void crossoverWorldObserver::stepPost()
{
    TemplateEEWorldObserver::stepPost();
}

void crossoverWorldObserver::monitorPopulation( bool localVerbose )
{
    TemplateEEWorldObserver::monitorPopulation(localVerbose);
}
