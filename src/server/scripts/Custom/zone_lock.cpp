#include "ScriptPCH.h"
#include "Chat.h"

class zone_lock : public PlayerScript

{

public:
	    zone_lock() : PlayerScript("zone_lock") {}

	    void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea) { 
	    
  if(newZone == 876 && player->GetSession()->GetSecurity() < SEC_MODERATOR)
  {
   ChatHandler(player->GetSession()).PSendSysMessage("Shoo! This area is only for VIPs! If you wish to become one, contact a Staff member.");
   if (player->GetTeam() == ALLIANCE)
   {
	    player->TeleportTo(0, -4953.955078f, -1006.528f, 501.441223f, .860296f);
   }
   else // Player is horde.
   {
	    player->TeleportTo(1, 1483.152588f, -4416.8671f, 25.043356f, .171176f);
   }}
  





		}};

void AddSC_zone_lock()
{
	    new zone_lock();
}

