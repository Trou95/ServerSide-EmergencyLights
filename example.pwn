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


CMD:setel(playerid)
{
 TogglePlayerEl(playerid);
 new Float:x,Float:y,Float:z;
 GetPlayerPos(playerid,x,y,z);
 CreateVehicle(596,x,y,z,0,0,1,-1,0);
}



