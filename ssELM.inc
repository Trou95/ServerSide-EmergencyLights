
#if defined ssELM_INC
#endinput
#endif
#define ssELM_INC

#define MANUEL_ENGINE_AND_LIGHTS 0
#define CHECK_VEHICLETYPE_ONUPDATE 0

#define MODE_ON 0
#define MODE_OFF 255



new static bIsPlayerEL[MAX_PLAYERS char];
#if CHECK_VEHICLETYPE_ONUPDATE == 0
new static playerELVehicle[MAX_PLAYERS];
#endif


new static __unu;

new static const emergencyVehicles[] = {596,597,598,599,601,528};
new static const emergencyModes[] = {0x1,0x4,0x9,0x0,0x9,0x40};
new static const modelSize = sizeof(emergencyVehicles) - 1;
new const modeSize = sizeof(emergencyModes) - 1;


PlayerVehicleElFlash(playerid)
{
 if(IsPlayerElOn(playerid))
 {
  if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
  {
   new vehicle = GetPlayerVehicleID(playerid);
   #if CHECK_VEHICLETYPE_ONUPDATE
   new model = GetVehicleModel(vehicle);
   if(IsEmergencyVehicle(model))
   {
    new vehpanel,vehdoors,vehtires;
    GetVehicleDamageStatus(vehicle,vehpanel,vehdoors,__unu,vehtires);
    UpdateVehicleDamageStatus(vehicle,vehpanel,vehdoors,emergencyModes[bIsPlayerEL{playerid}++],vehtires);
    if(bIsPlayerEL{playerid} > modeSize) bIsPlayerEL{playerid} = 0;
   }
   #else
   if(vehicle == playerELVehicle[playerid])
   {
    new vehpanel,vehdoors,vehtires;
    GetVehicleDamageStatus(vehicle,vehpanel,vehdoors,__unu,vehtires);
    UpdateVehicleDamageStatus(vehicle,vehpanel,vehdoors,emergencyModes[bIsPlayerEL{playerid}++],vehtires);
    if(bIsPlayerEL{playerid} > modeSize) bIsPlayerEL{playerid} = 0;
   }
   else bIsPlayerEL{playerid} = MODE_OFF;
   #endif
  }
 }
}

IsPlayerElOn(playerid)
{
 return bIsPlayerEL{playerid} < MODE_OFF ? true : false;
}

stock IsEmergencyVehicle(model)
{
 for(new i = modelSize; i != -1; i--)
    if(model == emergencyVehicles[i])
		return true;
 return false;
}

stock TogglePlayerEl(playerid){
 if(playerid >= MAX_PLAYERS)
	return;
 if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
 {
  new vehicle = GetPlayerVehicleID(playerid);
  if(IsEmergencyVehicle(GetVehicleModel(vehicle)))
  {
   #if CHECK_VEHICLETYPE_ONUPDATE == 0
   playerELVehicle[playerid] = vehicle;
   #endif
   if(bIsPlayerEL{playerid} < MODE_OFF)
   {
	new vehpanel,vehdoors,vehtires;
	GetVehicleDamageStatus(vehicle,vehpanel,vehdoors,__unu,vehtires);
	UpdateVehicleDamageStatus(vehicle,vehpanel,vehdoors,0xFF,vehtires);
	bIsPlayerEL{playerid} = MODE_OFF;
   }
   else bIsPlayerEL{playerid} = MODE_ON;
  }
 }
}

stock SetPlayerEl(playerid,mode = false){
 if(playerid >= MAX_PLAYERS)
	return;
 if(mode) bIsPlayerEL{playerid} = MODE_ON;
 else
 {
  bIsPlayerEL{playerid} = MODE_OFF;
  #if CHECK_VEHICLETYPE_ONUPDATE == 0
  playerELVehicle[playerid] = -1;
  #endif
 }
}
 


