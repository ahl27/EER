/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 *
 */

#include "TemplateEE/include/TemplateEEWorldObserver.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "TemplateEE/include/TemplateEEController.h"
#include "RoboroboMain/roborobo.h"
#include "TemplateEE/include/TemplateEESharedData.h"
#include "Utilities/Graphics.h"

TemplateEEWorldObserver::TemplateEEWorldObserver( World* world ) : WorldObserver( world )
{
    _world = world;
    
    // ==== create specific "lite" logger file
    
    std::string litelogFullFilename = gLogDirectoryname + "/lite_" + gLogFilename;
    gLitelogFile.open(litelogFullFilename.c_str());

    std::string pucksFullFilename = gPucksDirectoryname + "/" + gPucksFilename;
    gPucksFile.open(pucksFullFilename.c_str());

    std::string agentFullFilename = gAgentDirectoryname + "/" + gAgentFilename;
    gAgentFile.open(agentFullFilename.c_str());

    if(!gPucksFile) {
        std::cout << "[CRITICAL] Cannot open \"pucks\" log file " << pucksFullFilename << "." << std::endl << std::endl;
        exit(-1);
    }

    if(!gAgentFile) {
        std::cout << "[CRITICAL] Cannot open \"pucks\" log file " << pucksFullFilename << "." << std::endl << std::endl;
        exit(-1);
    }
        
    if(!gLitelogFile) {
        std::cout << "[CRITICAL] Cannot open \"lite\" log file " << litelogFullFilename << "." << std::endl << std::endl;
        exit(-1);
    }

    gPuckslogManager = new LogManager();
    gPuckslogManager->setLogFile(gPucksFile);
    gPuckslogManager->write("# pucks logger\n");
    gPuckslogManager->write("# generation, total redpucks, total greenpucks.\n");
    gPuckslogManager->flush();    

    gAgentlogManager = new LogManager();
    gAgentlogManager->setLogFile(gAgentFile);
    gAgentlogManager->write("#Per agent: proportion red, total pucks, xcoord, ycoord, isAlive().\n");
    gAgentlogManager->write("#Specialization reported as (numRed) / (numGreen + numRed)\n");
    gAgentlogManager->flush();
        
    gLitelogManager = new LogManager();
    gLitelogManager->setLogFile(gLitelogFile);
    gLitelogManager->write("# lite logger\n");
    gLitelogManager->write("# generation,iteration,populationSize,minFitness,maxFitness,avgFitnessNormalized.\n");
    gLitelogManager->flush();

    // ==== loading project-specific properties

    gProperties.checkAndGetPropertyValue("gSigmaRef",&TemplateEESharedData::gSigmaRef,true);
    gProperties.checkAndGetPropertyValue("gSigmaMin",&TemplateEESharedData::gSigmaMin,true);
    gProperties.checkAndGetPropertyValue("gSigmaMax",&TemplateEESharedData::gSigmaMax,true);
    
    gProperties.checkAndGetPropertyValue("gProbaMutation",&TemplateEESharedData::gProbaMutation,true);
    gProperties.checkAndGetPropertyValue("gUpdateSigmaStep",&TemplateEESharedData::gUpdateSigmaStep,true);
    gProperties.checkAndGetPropertyValue("gEvaluationTime",&TemplateEESharedData::gEvaluationTime,true);
    gProperties.checkAndGetPropertyValue("gSynchronization",&TemplateEESharedData::gSynchronization,true);
    
    gProperties.checkAndGetPropertyValue("gEnergyRequestOutput",&TemplateEESharedData::gEnergyRequestOutput,false);
    
    gProperties.checkAndGetPropertyValue("gMonitorPositions",&TemplateEESharedData::gMonitorPositions,true);
    
    gProperties.checkAndGetPropertyValue("gNbHiddenLayers",&TemplateEESharedData::gNbHiddenLayers,true);
    gProperties.checkAndGetPropertyValue("gNbNeuronsPerHiddenLayer",&TemplateEESharedData::gNbNeuronsPerHiddenLayer,true);
    gProperties.checkAndGetPropertyValue("gNeuronWeightRange",&TemplateEESharedData::gNeuronWeightRange,true);
    
    gProperties.checkAndGetPropertyValue("gSnapshots",&TemplateEESharedData::gSnapshots,false);
    gProperties.checkAndGetPropertyValue("gSnapshotsFrequency",&TemplateEESharedData::gSnapshotsFrequency,false);
    
    gProperties.checkAndGetPropertyValue("gControllerType",&TemplateEESharedData::gControllerType,true);
    
    gProperties.checkAndGetPropertyValue("gMaxNbGenomeTransmission",&TemplateEESharedData::gMaxNbGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gLimitGenomeTransmission",&TemplateEESharedData::gLimitGenomeTransmission,true);
    gProperties.checkAndGetPropertyValue("gSelectionMethod",&TemplateEESharedData::gSelectionMethod,true);
    
    gProperties.checkAndGetPropertyValue("gNotListeningStateDelay",&TemplateEESharedData::gNotListeningStateDelay,true);
    gProperties.checkAndGetPropertyValue("gListeningStateDelay",&TemplateEESharedData::gListeningStateDelay,true);
    
    gProperties.checkAndGetPropertyValue("gLogGenome",&TemplateEESharedData::gLogGenome,false);
    gProperties.checkAndGetPropertyValue("gLogGenomeSnapshot",&TemplateEESharedData::gLogGenomeSnapshot,false);
    
    gProperties.checkAndGetPropertyValue("gIndividualMutationRate",&TemplateEESharedData::gIndividualMutationRate,false);

    gProperties.checkAndGetPropertyValue("gMutationOperator",&TemplateEESharedData::gMutationOperator,false);
    
    gProperties.checkAndGetPropertyValue("gSigma",&TemplateEESharedData::gSigma,false);
    
    // ====
    
    if ( !gRadioNetwork)
    {
        std::cout << "Error : gRadioNetwork must be true." << std::endl;
        exit(-1);
    }
    
    // * iteration and generation counters
    
    _generationItCount = -1;
    _generationCount = -1;
}

TemplateEEWorldObserver::~TemplateEEWorldObserver()
{
    gLitelogFile.close();
}

void TemplateEEWorldObserver::initPre()
{
    // nothing to do.
}

void TemplateEEWorldObserver::initPost()
{
    // nothing to do.
}

void TemplateEEWorldObserver::stepPre()
{
    _generationItCount++;
    
    if( _generationItCount == TemplateEESharedData::gEvaluationTime+1 ) // switch to next generation.
    {
        // update iterations and generations counters
        _generationItCount = 0;
        _generationCount++;
    }
    
    updateMonitoring();
    
    updateEnvironment();
    
}

void TemplateEEWorldObserver::stepPost()
{
    // nothing to do.
}

void TemplateEEWorldObserver::updateEnvironment()
{
    // example: moving landmarks
    /*
    if ( gWorld->getIterations() % 2000 == 0 )
        for ( int i = 0 ; i != gNbOfLandmarks ; i++ )
        {
            Point2d* position = new Point2d( 200+randint()%(gAreaWidth-400) , 200+randint()%(gAreaHeight-400) );
            gLandmarks[i]->setPosition(*position);
        }
    */
}

void TemplateEEWorldObserver::updateMonitoring()
{
    // * Log at end of each generation

    //if( gWorld->getIterations() % TemplateEESharedData::gEvaluationTime == 1 || gWorld->getIterations() % TemplateEESharedData::gEvaluationTime == TemplateEESharedData::gEvaluationTime-1 ) // beginning(+1) *and* end of generation. ("==1" is required to monitor the outcome of the first iteration)
    // log at end of generation.
    if( gWorld->getIterations() % TemplateEESharedData::gEvaluationTime == TemplateEESharedData::gEvaluationTime-1 )
    {
        monitorPopulation();
    }
    
    // * Every N generations, take a video (duration: one generation time)
    
    if ( TemplateEESharedData::gSnapshots )
    {
        if ( ( gWorld->getIterations() ) % ( TemplateEESharedData::gEvaluationTime * TemplateEESharedData::gSnapshotsFrequency ) == 0 )
        {
            if ( gVerbose )
                std::cout << "[START] Video recording: generation #" << (gWorld->getIterations() / TemplateEESharedData::gEvaluationTime ) << ".\n";
            gTrajectoryMonitorMode = 0;
            initTrajectoriesMonitor();
        }
        else
            if ( ( gWorld->getIterations() ) % ( TemplateEESharedData::gEvaluationTime * TemplateEESharedData::gSnapshotsFrequency ) == TemplateEESharedData::gEvaluationTime - 1 )
            {
                if ( gVerbose )
                    std::cout << "[STOP]  Video recording: generation #" << (gWorld->getIterations() / TemplateEESharedData::gEvaluationTime ) << ".\n";
                saveTrajectoryImage();
            }
    }    
}

void TemplateEEWorldObserver::monitorPopulation( bool localVerbose )
{
    // * monitoring: count number of active agents.
    
    int activeCount = 0;
    double sumOfFitnesses = 0;
    double minFitness = DBL_MAX;
    double maxFitness = -DBL_MAX;
    double maxRed[2] = {-1, -1};
    double maxGreen[2] = {-1, -1};
    double minRed[2] = {DBL_MAX, DBL_MAX};
    double minGreen[2] = {DBL_MAX, DBL_MAX};
    double totalRed = 0;
    double totalGreen = 0;
    double avgSpeed = 0;
    double avgSpec = 0;

    gAgentlogManager->write("[");
    gAgentlogManager->flush();
    std::string specMessage = "";
    
    for ( int i = 0 ; i != gNbOfRobots ; i++ )
    {
        TemplateEEController *ctl = dynamic_cast<TemplateEEController*>(gWorld->getRobot(i)->getController());
        
        if ( ctl->getWorldModel()->isAlive() == true )
        {
            activeCount++;
            sumOfFitnesses += ctl->getFitness() ;
            if ( ctl->getFitness() < minFitness )
                minFitness = ctl->getFitness();
            if ( ctl->getFitness() > maxFitness )
                maxFitness = ctl->getFitness();

            //tracking pucks
            //Format: (Red Collected, Green Collected)
            if( ctl->getRed() > maxRed[0]  || (ctl->getRed() == maxRed[0] && ctl->getGreen() < maxRed[1]) ){
                maxRed[0] = ctl->getRed(); 
                maxRed[1] = ctl->getGreen();
            }
            if( ctl->getRed() < minRed[0]  || (ctl->getRed() == minRed[0] && ctl->getGreen() > minRed[1]) ){
                minRed[0] = ctl->getRed(); 
                minRed[1] = ctl->getGreen();
            }
            if ( ctl->getGreen() > maxGreen[1]  || (ctl->getGreen() == maxGreen[1] && ctl->getRed() < maxGreen[0]) ){
                maxGreen[0] = ctl->getRed();
                maxGreen[1] = ctl->getGreen();
            }
            if( ctl->getGreen() < minGreen[1]  || (ctl->getGreen() == minGreen[1] && ctl->getRed() > minGreen[0]) ){
                minGreen[0] = ctl->getRed(); 
                minGreen[1] = ctl->getGreen();
            }

            avgSpeed += ctl->getSpec();
            totalRed += ctl->getAbsRed();
            totalGreen += ctl->getAbsGreen();
            if (ctl->getAbsGreen() == 0 && ctl->getAbsRed() == 0){
                avgSpec += 0;
            }
            else{
                avgSpec += std::max(ctl->getAbsRed(), ctl->getAbsGreen()) / (ctl->getAbsRed() + ctl->getAbsGreen());
            }
        }

            //DEBUG: for some reason we're writing nans
        double spec;
        if (ctl->getRed() == 0 && ctl->getGreen()==0)
            spec = -1; //deal with these datapoints later
        else
            spec = ( ctl->getRed() / (ctl->getRed() + ctl->getGreen()) );

        gAgentlogManager->write("(" + std::to_string(spec) +  "," + std::to_string(ctl->getRed() + ctl->getGreen()) + "," + 
            std::to_string(ctl->getWorldModel()->_xReal) + "," + std::to_string(ctl->getWorldModel()->_yReal) + "," + std::to_string(ctl->getWorldModel()->isAlive()) + ")");
        if (i != gNbOfRobots - 1)
            gAgentlogManager->write(",");
        gAgentlogManager->flush();
        
    }
    avgSpec /= activeCount;
    gAgentlogManager->write("]\n");
    gAgentlogManager->flush();
    
    if ( gVerbose && localVerbose )
    {
        std::cout << "\nGeneration: " << (gWorld->getIterations()/TemplateEESharedData::gEvaluationTime) << "\t(Iteration " <<  gWorld->getIterations() << ")\n";
        std::cout << "[ pop:" << activeCount << "\tminFitness:" << minFitness << "\tmaxFitness:" << maxFitness << "\tavgFitnessNormalized:" << sumOfFitnesses/activeCount << " ]\n"; 
        std::cout << "[ maxRed: ( r:" << maxRed[0] << " , g:" << maxRed[1] << " ) \tminRed: ( r:" << minRed[0] << " , g:" << minRed[1] << " )\tmaxGreen: ( r:" << maxGreen[0] << " , g:" << maxGreen[1] << " ) \tminGreen: ( r:" << minGreen[0] << " , g:" << minGreen[1] << " ) ]\n";
        std::cout << "Total Red: " << totalRed << "\tTotal Green: " << totalGreen << "\n";
        //std::cout << "maxGreen: (" << maxGreen[0] << "," << maxGreen[1] << ") \tminGreen: (" << minGreen[0] << "," << minGreen[1] << ") ]\n\n";
    }
    
    // display lightweight logs for easy-parsing
    std::string sLitelog =
        "log:"
        + std::to_string(gWorld->getIterations()/TemplateEESharedData::gEvaluationTime)
        + ","
        + std::to_string(gWorld->getIterations())
        + ","
        + std::to_string(activeCount)
        + ","
        + std::to_string(minFitness)
        + ","
        + std::to_string(maxFitness)
        + ","
        + std::to_string(sumOfFitnesses/activeCount);
    gLitelogManager->write(sLitelog);
    gLitelogManager->flush();  // flush internal buffer to file
    gLitelogFile << std::endl; // flush file output (+ "\n")


    avgSpeed /= activeCount;
    // display pucks logs for easy-parsing
    std::string sPuckslog =
        std::to_string(gWorld->getIterations()/TemplateEESharedData::gEvaluationTime)
        + " "
        + std::to_string(totalRed)
        + " "
        + std::to_string(totalGreen)
        + " "
        + std::to_string(avgSpec)
        + " "
        + std::to_string(activeCount);

    gPuckslogManager->write(sPuckslog);
    gPuckslogManager->flush();  // flush internal buffer to file
    gPucksFile << std::endl; // flush file output (+ "\n")
    
    // Logging, population-level: alive
    std::string sLog = std::string("") + std::to_string(gWorld->getIterations()) + ",pop,alive," + std::to_string(activeCount) + "\n";
    gLogManager->write(sLog);
    gLogManager->flush();
}
