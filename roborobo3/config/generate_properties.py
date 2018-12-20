import argparse
import os
import random

cwd = os.getcwd()

#static variables
RADIUS = '8'
FOOTPRINT_RADIUS = '14'
ENERGY = '10'
ENERGY_MODE = '2'

X_VAR = 10
Y_VAR = 10
SCREEN_X = 1380
SCREEN_Y = 780

X_TYPE = 'bands'
X_BANDS = 2
X_CONST = -1

Y_TYPE = 'rand'
Y_BANDS = 4
Y_CONST = -1

'''
These two functions write a red or green puck into the file
There are two separate functions so that red and green pucks can be more easily controlled
Input Variables: 
    -f: file object
    -i: current index of puck being created
    -x: x value of pucks to generate. value of -1 creates a random value.
    -y: same as x, but for y value.
'''

def make_red_puck(f, i, x=[-1,-1], y=[-1,-1]):
    f.write("physicalObject[" + str(i) +"].type=1\n")
    if x[0] != -1:
        f.write("physicalObject[" + str(i) +"].ixmin=" + str(x[0]) + "\n")
        f.write("physicalObject[" + str(i) +"].ixmax=" + str(x[1]) + "\n")
    if y[0] != -1:
        f.write("physicalObject[" + str(i) +"].iymin=" + str(y[0]) + "\n")
        f.write("physicalObject[" + str(i) +"].iymax=" + str(y[1]) + "\n")
    f.write("physicalObject[" + str(i) +"].radius=" + RADIUS + "\n")
    f.write("physicalObject[" + str(i) +"].footprintRadius=" + FOOTPRINT_RADIUS + "\n")
    f.write("physicalObject[" + str(i) +"].displayColorRed=255\n")
    f.write("physicalObject[" + str(i) + "].displayColorGreen=0\n")
    f.write("physicalObject[" + str(i) + "].displayColorBlue=0\n")
    f.write("physicalObject[" + str(i) + "].visible=true\n")
    f.write("physicalObject[" + str(i) + "].relocate=true\n")
    f.write("physicalObject[" + str(i) + "].overwrite=false\n")
    f.write("physicalObject[" + str(i) + "].regrowTimeMax=0\n")
    f.write("physicalObject[" + str(i) +"].energy=" + ENERGY + "\n")
    f.write("physicalObject[" + str(i) +"].energyMode=" + ENERGY_MODE + "\n")

def make_green_puck(f, i, x=[-1,-1], y=[-1,-1]):
    f.write("physicalObject[" + str(i) +"].type=1\n")
    if x[0] != -1:
        f.write("physicalObject[" + str(i) +"].ixmin=" + str(x[0]) + "\n")
        f.write("physicalObject[" + str(i) +"].ixmax=" + str(x[1]) + "\n")
    if y[0] != -1:
        f.write("physicalObject[" + str(i) +"].iymin=" + str(y[0]) + "\n")
        f.write("physicalObject[" + str(i) +"].iymax=" + str(y[1]) + "\n")
    f.write("physicalObject[" + str(i) +"].radius=" + RADIUS + "\n")
    f.write("physicalObject[" + str(i) +"].footprintRadius=" + FOOTPRINT_RADIUS + "\n")
    f.write("physicalObject[" + str(i) +"].displayColorRed=0\n")
    f.write("physicalObject[" + str(i) + "].displayColorGreen=255\n")
    f.write("physicalObject[" + str(i) + "].displayColorBlue=0\n")
    f.write("physicalObject[" + str(i) + "].visible=true\n")
    f.write("physicalObject[" + str(i) + "].relocate=true\n")
    f.write("physicalObject[" + str(i) + "].overwrite=false\n")
    f.write("physicalObject[" + str(i) + "].regrowTimeMax=0\n")
    f.write("physicalObject[" + str(i) +"].energy=" + ENERGY + "\n")
    f.write("physicalObject[" + str(i) +"].energyMode=" + ENERGY_MODE + "\n")

def smart_xy(i, x, gen_type, total_pucks):
    #TODO: implement way to make bands, quadrants, etc. using this
    #set x/y vars 
    if x is 'x':
        var = X_VAR
        screen = SCREEN_X
        num_bands = X_BANDS
    else:
        var = Y_VAR
        screen = SCREEN_Y
        num_bands = Y_BANDS

    #Types of Distributions
    if gen_type == 'rand':
        return [-1,-1]
    elif gen_type == 'quadrants':
        #270 = -1
        #90 = 1
        #180, 0 = 0
        section = -1
        if i < 0.25 * total_pucks:
            return [0, screen/2]
        elif i < 0.5 * total_pucks:
            return [screen/2, screen]
        elif i < 0.75 * total_pucks:
            if x is 'x':
                return [screen/2, screen]
            else:
                return [0, screen/2]
        else:
            if x is 'y':
                return [screen/2, screen]
            else:
                return [0, screen/2]




    elif gen_type == 'bands':
        sections = num_bands / 2

        if i > total_pucks / 2:
            red = False
            i -= total_pucks / 2
        else:
            red = True        
        selection = -1
        ctr = 1

        while selection == -1:
            if i < (total_pucks/2) * (ctr/sections):
                selection = ctr
            ctr += 1

        if red:
            return [ ( (selection-1) / sections ) * screen, ( (selection-0.5) / sections ) * screen ]
        else:
            return [ ( (selection-0.5) / sections ) * screen, ( (selection) / sections ) * screen ]

    elif gen_type == 'const':
        return [const_val, const_val]


def main():
    parser = argparse.ArgumentParser(description="Create new properties file with desired puck ratios")
    parser.add_argument( "numPucks", type=int, help="Total number of pucks to add into simulation" )
    parser.add_argument( "numRed", type=float, help="Proportion or absolute number of red pucks to add compared to total number of pucks. \
        Values <=1 will be treated as proportions, else treated as absolute numbers." )
    parser.add_argument( "-r", "--numRobots", type=int, help="OPTIONAL: Number of robots in simulation. Default: 200", default=200 )
    parser.add_argument( "-s", "--specialization", type=float, help="OPTIONAL: Specialization value. Default: 1.0.", default = 1. )
    parser.add_argument("-f", "--filename", type=str, help="OPTIONAL: Filename to write to. Pucks data written to pucks_<input>, \
        agent data to agent_<input>. Default setting is a time-stamped txt file.", default="")
    parser.add_argument( "-sel", "--selection", type=int, help="OPTIONAL: Selection type. 0: Random, 1: First collected, 2: Best, 3: Proportional, 4: MONEE (experimental)",
        default=-1)
    parser.add_argument( "-sw", "--switch", type=int, help="OPTIONAL: Generation to switch to random distribution of pucks.")
    parser.add_argument( "-m", '--monee', action='store_true', help='OPTIONAL: Activate MONEE Parameters')

    args=parser.parse_args()

    totalRobots = args.numRobots
    totalPucks = args.numPucks
    fname = args.filename
    spec = args.specialization
    selection = args.selection
    switch = args.switch
    monee = args.monee
    if args.numRed <= 1:
        totalRed = totalPucks * args.numRed
    else:
        totalRed = args.numRed

    old = open( cwd + "/pucks_vanilla_template.properties", 'r' ).read()
    old = old.replace( 'gNbOfPhysicalObjects = 150', 'gNbOfPhysicalObjects = ' + str(totalPucks) )
    old = old.replace( 'gNbOfRedPucks = 75', 'gNbOfRedPucks = ' + str(totalRed) )
    old = old.replace( 'gSelectionMethod = 2', 'gSelectionMethod = ' + str(selection))
    old = old.replace( 'gPhysicalObjectSwitchGen = 10000', 'gPhysicalObjectSwitchGen = ' + str(switch))
    
    if monee:
        old = old.replace('gMONEEConfig = false', 'gMONEEConfig = true')
        old = old.replace('gEnergyLevel = false', 'gEnergyLevel = true')
        old = old.replace('gEnergyRefill = true', 'gEnergyRefill = false')

    if totalRobots != 200:
        old = old.replace('gInitialNumberOfRobots = 200', 'gInitialNumberOfRobots = ' + str(totalRobots) )
    
    if fname: #strings evaluate as booleans in python
        old.replace( '#gAgentFilename =', 'gSpecFilename = spec_' + fname + ".txt" )
        old.replace( '#gPucksFilename =', 'gPucksFilename = pucks_' + fname + ".txt" )

    old = old.replace( 'gSpecialization = 1.0', 'gSpecialization = ' + str(spec) )
    new = open( cwd + "/pucks_vanilla.properties", 'w' )
    new.write( old )
    if fname: #strings are falsy in python
        new.write( '\ngAgentFilename = agent_' + fname + ".txt\n" )
        new.write( 'gPucksFilename = pucks_' + fname + ".txt\n" )
    new.close()


    with open( "pucks_vanilla.properties", 'a' ) as f:
        f.write('\n')
        for i in range( int(totalPucks) ):
            x = smart_xy(i, 'x', X_TYPE, totalPucks)
            y = smart_xy(i, 'y', Y_TYPE, totalPucks)
            if i < totalRed:
                make_red_puck(f, i, x, y)
            else:
                make_green_puck(f, i, x, y)



if __name__ == '__main__':
    main()












