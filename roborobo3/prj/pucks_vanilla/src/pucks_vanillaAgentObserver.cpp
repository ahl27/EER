/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "pucks_vanilla/include/pucks_vanillaAgentObserver.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/PhysicalObject.h"
#include <iostream>

pucks_vanillaAgentObserver::pucks_vanillaAgentObserver( RobotWorldModel *wm ) : TemplateEEAgentObserver ( wm )
{
    // superclass constructor called before
}

pucks_vanillaAgentObserver::~pucks_vanillaAgentObserver()
{
    // superclass destructor called before
}

/*
 * Manage foraging of energy items.
 * If walked on, the item disappear (callback to item object) and agent's fitness function is updated.
 * Assume that *only* energy point's footprint can be walked upon. That means that for this code to correctly run you should avoid placing any objects detectable through the robot's ground sensor.
 *
 */
void pucks_vanillaAgentObserver::step()
{
    //if (_wm->_specialization != 0.5 && _wm->_specialization != 1)
    //    std::cout << _wm->_specialization << std::endl;

    double specialization = gSpecialization;
    double redMod, greenMod;
    double var = std::pow(_wm->_specialization, 2);
    double PICKUP_COST = 30;

    //maybe set the max value of specialization to 0.9 or something

    //IMPORTANT: Track total number of pucks collected in addition to the weighted average
    //currently histogram is biased by reweighting (introduce new variables)
    if (_wm->_redPucks >= _wm->_greenPucks){
        redMod = var;
        greenMod = 1 - var;

        if (redMod > 0.9){
            greenMod = 0.1;
            redMod *= 0.9;
        }
    }
    else {
        redMod = 1 - var;
        greenMod = var;

        if (greenMod > 0.9){
            redMod = 0.1;
            greenMod = 0.9;
        }
    }
    //if (_wm->_greenPucks > 1 || _wm->_redPucks > 1)
    //    std::cout << _wm->_greenPucks << "," << _wm->_redPucks << "," << _wm->_specialization << std::endl;

    // * update fitness (if needed)
    if ( _wm->isAlive() && PhysicalObject::isInstanceOf(_wm->getGroundSensorValue()) )
    {
        //_wm->getGroundSensorValue returns the id of the puck collected
        _wm->substractEnergy(PICKUP_COST);
        //red pucks
        if( _wm->getGroundSensorValue() <= (gNbOfRedPucks) ) { 
            //_wm->_fitnessValue = _wm->_fitnessValue + 1; 
            if (gSpecAffectsCollection){
                _wm->_redPucks += redMod;
                _wm->_fitnessValue += redMod;
            }
            else{
                _wm->_redPucks += 1;
                _wm->_fitnessValue += 1;
            }

            _wm->_absRed += 1;
        }
        

        //green pucks
        else { 
            //_wm->_fitnessValue = _wm->_fitnessValue - 1; 
            
            if (gSpecAffectsCollection){
                _wm->_greenPucks += greenMod;
                _wm->_fitnessValue -= greenMod;
            }
            else{
                _wm->_greenPucks += 1;
                _wm->_fitnessValue -= 1;
            }

            _wm->_absGreen += 1;
        }
     
    }

    double speedPenalty = 1.0;
    double max = (double) (std::max(_wm->_greenPucks, _wm->_redPucks));
    double sum = (double) (_wm->_greenPucks + _wm->_redPucks);
    double x;
    //double x = (sum == 0.0) ? 0.75 : (max/sum); // x is the specialisation level
    if (sum == 0.0){
        x = 0.5;
    }
    else{
        x = max / sum;
    }

    _wm->_specialization = x;

    speedPenalty = std::pow(x, specialization);

    _wm->_desiredTranslationalValue = gMaxTranslationalSpeed * speedPenalty;
    _wm->_desiredRotationalVelocity = gMaxRotationalSpeed * speedPenalty;


    TemplateEEAgentObserver::step();

    //update color based on specialization
    if( !_wm->isAlive() ) {
        _wm->setRobotLED_colorValues(0, 0, 255);
    }
    else {
        if ( _wm->_greenPucks > _wm->_redPucks )
            _wm->setRobotLED_colorValues(0, 255, 0);
        else if ( _wm->_greenPucks == _wm->_redPucks )
            _wm->setRobotLED_colorValues(255, 255, 0);
        else
            _wm->setRobotLED_colorValues(255, 0, 0);
    }
}



