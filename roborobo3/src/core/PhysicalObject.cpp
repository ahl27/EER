/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "World/PhysicalObject.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/Misc.h"
#include "World/World.h"
#include <iostream>
#include "TemplateEE/include/TemplateEESharedData.h"

PhysicalObject::PhysicalObject( int __id ) // a unique and consistent __id should be given as argument
{
    _id = __id;
    _initXmax = gPhysicalObjectsInitAreaWidth;
    _initXmin = 0;
    _initYmax = gPhysicalObjectsInitAreaHeight; 
    _initYmin = 0;
    _customInit = false;
    init();
}

void PhysicalObject::init()
{
    double x = 0.0, y = 0.0;
    
	std::string s = "";
	std::stringstream out;
	out << getId();
    
    regrowTime = 0;
    
    s = "physicalObject[";
	s += out.str();
	s += "].regrowTimeMax";
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<int>(regrowTimeMax, gProperties.getProperty( s ), std::dec);
	}
    else
    {
        regrowTimeMax = gPhysicalObjectDefaultRegrowTimeMax;
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].overwrite";
	if ( gProperties.hasProperty( s ) )
        gProperties.checkAndGetPropertyValue(s,&overwrite,true);
    else
    {
        overwrite = gPhysicalObjectDefaultOverwrite;
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].relocate";
	if ( gProperties.hasProperty( s ) )
        gProperties.checkAndGetPropertyValue(s,&relocate,true);
    else
    {
        relocate = gPhysicalObjectDefaultRelocate;
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].visible";
	if ( gProperties.hasProperty( s ) )
        gProperties.checkAndGetPropertyValue(s,&_visible,true);
	else
        gProperties.checkAndGetPropertyValue("gPhysicalObjectsVisible", &_visible, true);
    
    Uint32 colorValue;
    
    s = "physicalObject[";
	s += out.str();
	s += "].displayColorRed";
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<Uint32>(colorValue, gProperties.getProperty( s ), std::dec);
        _displayColorRed = (colorValue & 0x000000FF);
	}
    else
    {
        _displayColorRed = gPhysicalObjectDefaultDisplayColorRed; // default
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].displayColorGreen";
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<Uint32>(colorValue, gProperties.getProperty( s ), std::dec);
        _displayColorGreen = (colorValue & 0x000000FF);
	}
    else
    {
        _displayColorGreen = gPhysicalObjectDefaultDisplayColorGreen; // default
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].displayColorBlue";
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<Uint32>(colorValue, gProperties.getProperty( s ), std::dec);
        _displayColorBlue = (colorValue & 0x000000FF);
	}
    else
    {
        _displayColorBlue = gPhysicalObjectDefaultDisplayColorBlue; // default
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].x";
    
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<double>(x, gProperties.getProperty( s ), std::dec);
	}
	else
	{
        x = -1.0;
	}
    
	s = "physicalObject[";
	s += out.str();
	s += "].y";
	if ( gProperties.hasProperty( s ) )
	{
		convertFromString<double>(y, gProperties.getProperty( s ), std::dec);
	}
	else
	{
        y = -1.0;
	}

    /*
    Additional arguments to set initArea for each object
    */
    s = "physicalObject[";
    s += out.str();
    s +=  "].ixmax";
    if ( gProperties.hasProperty( s ) )
    {
        convertFromString<double>(_initXmax, gProperties.getProperty( s ), std::dec);
        _customInit = true;
    }

    s = "physicalObject[";
    s += out.str();
    s +=  "].ixmin";
    if ( gProperties.hasProperty( s ) )
    {
        convertFromString<double>(_initXmin, gProperties.getProperty( s ), std::dec);
        _customInit = true;
    }

    s = "physicalObject[";
    s += out.str();
    s +=  "].iymax";
    if ( gProperties.hasProperty( s ) )
    {
        convertFromString<double>(_initYmax, gProperties.getProperty( s ), std::dec);
        _customInit = true;
    }


    s = "physicalObject[";
    s += out.str();
    s +=  "].iymin";
    if ( gProperties.hasProperty( s ) )
    {
        convertFromString<double>(_initYmin, gProperties.getProperty( s ), std::dec);
        _customInit = true;
    }


    if ( gProperties.hasProperty("gPhysicalObjectSwitchGen") )
    {
        s = gProperties.hasProperty("gPhysicalObjectSwitchGen");
        convertFromString<int>(_switchGen, gProperties.getProperty("gPhysicalObjectSwitchGen"), std::dec);
    }
    else
    {
        _switchGen = 100000;
    }    
    
    setCoordinates( x, y );
}

int PhysicalObject::findRandomLocation( double ix /* =-1 */, double iy /* =-1 */)
{
    /*
    CURRENT: Initialization working sorta correctly, respawning still random
    TODO: Make random spawn after collection work according to smart_xy()
    */
    double x = 0.0, y = 0.0;
    
    int tries = 0;

    int gen = gWorld->getIterations()/TemplateEESharedData::gEvaluationTime;
    //std::cout << gen << std::endl;
    
    do {
        //random and constant initialization
        if (!_customInit || gen > _switchGen)
        {
            x = ( randint() % ( gPhysicalObjectsInitAreaWidth  ) ) + gPhysicalObjectsInitAreaX;
            y = ( randint() % ( gPhysicalObjectsInitAreaHeight ) ) + gPhysicalObjectsInitAreaY;
            
            //x = (randint() % (gAreaWidth-20)) + 10;  // deprecated
            //y = (randint() % (gAreaHeight-20)) + 10; // deprecated

            //place element at the determined spot
            //if full, place it one space right/down
            //9 is the radius of one object
            if (ix != -1)
                x = ix + tries*9;
            if (iy != -1)
                y = iy + tries*9;
        }

        //custom distribution initialization
        else 
        {
            //TODO: find a smart way to do this
            x = ( randint() % (int(_initXmax - _initXmin)) ) + int(_initXmin);
            y = ( randint() % (int(_initYmax - _initYmin)) ) + int(_initYmin);
        }
        
        setCoordinates( x, y );
        
        tries++;
    } while ( canRegister() == false && tries < gLocationFinderMaxNbOfTrials );
    
    if ( tries == gLocationFinderMaxNbOfTrials )
    {
        if ( gLocationFinderExitOnFail == true )
        {
            std::cerr << "[CRITICAL] Random initialization of initial position for physical object #" << getId() << " after trying " << gLocationFinderMaxNbOfTrials << " random picks (all failed). There may be too few (none?) possible locations (you may try to manually set initial positions). EXITING.\n";
            exit(-1);
        }
        else
        {
            std::cerr << "[WARNING] Random initialization of initial position for physical object #" << getId() << " after trying " << gLocationFinderMaxNbOfTrials << " random picks (all failed). Retry later.\n";
            regrowTime = 1;
            setCoordinates( -1, -1 );
        }
    }
    
    return tries;
}

void PhysicalObject::stepPhysicalObject()
{
    if ( registered == false && regrowTime != -1 )
    {
        if ( regrowTime > 0 )
        {
            regrowTime--;
        }
        else
        {
            if ( relocate == true )
            {
                findRandomLocation(); // fail: exit or return (x,y)=(-1,-1)
                if ( getXReal() != -1 ) // check if new location is possible
                {
                    _visible = true;
                    registered = true;
                    registerObject();
                }
            }
            else
            {
                if ( canRegister() == true || overwrite == true )
                {
                    _visible = true;
                    registered = true;
                    registerObject();
                }
            }
        }
    }
    else
    {
        if ( getXReal() != -1 ) // check if (new) location is possible
            if ( _visible )
            {
                if ( gPhysicalObjectsRedraw == true )
                {
                    registerObject();
                }
            }
    }
}

bool PhysicalObject::isInstanceOf ( int index ) // static
{
    if ( index >= gPhysicalObjectIndexStartOffset && index <  gPhysicalObjectIndexStartOffset + (int)gPhysicalObjects.size() )
        return true;
    else
        return false;
}


/*
 Given an object not registered in the environment, tries to re-register at once.
 Return false (and do nothing) if not possible at desired location.
 Exit if function is called when it should not -- calling this function can be critical, including registering multiple instances of the same object, thus breaking consistency.
*/
bool PhysicalObject::triggerRegrow()
{
    if ( registered == true )  // exit if object is already registered in the environment
    {
        std::cerr << "[CRITICAL] physical object #" << getId() << ": attempt to call triggerRegrow() method while object already exists in the environment. EXITING.\n";
        exit(-1);
    }
    
    if ( canRegister() == false ) // check is position is free.
    {
        return false;
    }
    else
    {
        regrowTime = gPhysicalObjectDefaultRegrowTimeMax;
        _visible = true;
        registered = true;
        registerObject();
    }
    
    return true;
}

std::string PhysicalObject::inspect( std::string prefix )
{
    return std::string(prefix + "PhysicalObject::inspect() not implemented.\n");
}
