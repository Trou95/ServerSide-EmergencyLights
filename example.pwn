#include <a_samp>
#include <zcmd>
#include <ssELM>



new timerEl;
forward Timer_EL();


#define FLASH_RATE (300)




public OnFilterScriptInit(){
	timerEl = SetTimer("Timer_EL",FLASH_RATE,true);
	#if MANUEL_ENGINE_AND_LIGHTS
	    ManualVehicleEngineAndLights();
	#endif
	return 1;
}

public OnFilterScriptExit(){
	KillTimer(timerEl);
	return 1;
}

public OnPlayerConnect(playerid){
 SetPlayerEl(playerid);
 return 1;
}

public Timer_EL()
{
 for(new i = GetPlayerPoolSize(); i != -1; i--)
     PlayerVehicleElFlash(i);
}


CMD:elm(playerid){
 TogglePlayerEl(playerid);
 
}



