/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "crossover/include/crossoverController.h"

using namespace Neural;

crossoverController::crossoverController( RobotWorldModel *wm ) : TemplateEEController( wm )
{
    // superclass constructor called before this baseclass constructor.
    resetFitness(); // not used
}

crossoverController::~crossoverController()
{
    // superclass destructor automatically called after this baseclass destructor.
}

void crossoverController::stepController()
{
    TemplateEEController::stepController();
}

void crossoverController::initController()
{
    TemplateEEController::initController();
}

void crossoverController::performSelection()
{
    TemplateEEController::performSelection();
}

void crossoverController::performVariation()
{
    TemplateEEController::performVariation();
}

void crossoverController::broadcastGenome()
{
    TemplateEEController::broadcastGenome();
}

double crossoverController::getFitness()
{
    // mEDEA uses no fitness. Set to zero by default.
    return 0;
}

void crossoverController::resetFitness()
{
    // nothing to do
}

void crossoverController::updateFitness()
{
    // nothing to do
}

void crossoverController::logCurrentState()
{
    TemplateEEController::logCurrentState();
}
