/* ----------------------------------------------------------
 * v_repExtLanelets plugin
 * (c) Candido Otero, 2017, Universidade de Vigo
 * ----------------------------------------------------------*/

#include "v_repExtLanelets.h"
#include "v_repLib.h"
#include <unistd.h>
#include <iostream>
#include "laneletsdialog.h"

#ifdef _WIN32
    #include <direct.h>
#endif /* _WIN32 */

#if defined (__linux) || defined (__APPLE__)
    #include <string.h>
    #define _stricmp(x,y) strcasecmp(x,y)
#endif

#define PLUGIN_VERSION 1

LIBRARY vrepLib;
laneletsdialog* laneletsDialog=NULL;

// This is the plugin start routine (called just once, just after the plugin was loaded):
VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{
    // Dynamically load and bind V-REP functions:
     // ******************************************
     // 1. Figure out this plugin's directory:
     char curDirAndFile[1024];
 #ifdef _WIN32
     _getcwd(curDirAndFile, sizeof(curDirAndFile));
 #elif defined (__linux) || defined (__APPLE__)
     getcwd(curDirAndFile, sizeof(curDirAndFile));
 #endif
     std::string currentDirAndPath(curDirAndFile);
     // 2. Append the V-REP library's name:
     std::string temp(currentDirAndPath);
 #ifdef _WIN32
     temp+="/v_rep.dll";
 #elif defined (__linux)
     temp+="/libv_rep.so";
 #elif defined (__APPLE__)
     temp+="/libv_rep.dylib";
 #endif /* __linux || __APPLE__ */
    // 3. Load the V-REP library:
    vrepLib=loadVrepLibrary(temp.c_str());
    if (vrepLib==NULL)
    {
        std::cout << "Error, could not find or correctly load the V-REP library. Cannot start 'Lanelets' plugin.\n";
        return(0); // Means error, V-REP will unload this plugin
    }
    if (getVrepProcAddresses(vrepLib)==0)
    {
        std::cout << "Error, could not find all required functions in the V-REP library. Cannot start 'Lanelets' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    // Check the version of V-REP:
    // ******************************************
    int vrepVer;
    simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
    if (vrepVer<30200) // if V-REP version is smaller than 3.02.00
    {
        std::cout << "Sorry, your V-REP copy is somewhat old. Cannot start 'Lanelets' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    // Check if V-REP runs in headless mode:
    // ******************************************
    if (simGetBooleanParameter(sim_boolparam_headless)>0)
    {
        std::cout << "V-REP runs in headless mode. Cannot start 'Lanelets' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    QWidget* pMainWindow = (QWidget*)simGetMainWindow(1);
    laneletsDialog = new laneletsdialog(pMainWindow); // The plugin dialog
    simAddModuleMenuEntry("",1,&laneletsDialog->dialogMenuItemHandle);
    simSetModuleMenuItemState(laneletsDialog->dialogMenuItemHandle,1,"Lanelets import...");


    return(PLUGIN_VERSION); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
}

// This is the plugin end routine (called just once, when V-REP is ending, i.e. releasing this plugin):
VREP_DLLEXPORT void v_repEnd()
{
    // Here you could handle various clean-up tasks
    unloadVrepLibrary(vrepLib); // release the library
}

// This is the plugin messaging routine (i.e. V-REP calls this function very often, with various messages):
VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ // This is called quite often. Just watch out for messages/events you want to handle
    // Keep following 5 lines at the beginning and unchanged:
    static bool refreshDlgFlag=true;
    int errorModeSaved;
    simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
    simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);
    void* retVal=NULL;

    //---------------------------------- CALLBACKS ----------------------------------------

    if (message==sim_message_eventcallback_refreshdialogs)
        refreshDlgFlag=true; // V-REP dialogs were refreshed. Maybe a good idea to refresh this plugin's dialog too

    if (message==sim_message_eventcallback_menuitemselected)
    { // A custom menu bar entry was selected..
        if (auxiliaryData[0]==laneletsDialog->dialogMenuItemHandle)
            laneletsDialog->makeVisible(!laneletsDialog->getVisible()); // Toggle visibility of the dialog
    }

    if (message==sim_message_eventcallback_instancepass)
    { // It is important to always correctly react to events in V-REP. This message is the most convenient way to do so:
        laneletsDialog->setSimulationStopped(simGetSimulationState()==sim_simulation_stopped);

        int flags=auxiliaryData[0];
        bool sceneContentChanged=((flags&(1+2+4+8+16+32+64+256))!=0); // object erased, created, model or scene loaded, und/redo called, instance switched, or object scaled since last sim_message_eventcallback_instancepass message
        bool instanceSwitched=((flags&64)!=0);

        if (instanceSwitched)
        {
            // React to an instance switch here!!
        }

        if (sceneContentChanged)
        {
            refreshDlgFlag=true;
        }
    }
    if ((message==sim_message_eventcallback_guipass)&&refreshDlgFlag)
    { // handle refresh of the plugin's dialog:
        laneletsDialog->refresh(); // Refresh the dialog
        refreshDlgFlag=false;
    }

    //-------------------------------- END CALLBACKS --------------------------------------

    // Keep following unchanged:
    simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
    return(retVal);
}

