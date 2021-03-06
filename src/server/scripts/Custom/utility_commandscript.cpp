#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Group.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"
#include "Language.h"
 
//This script is made by Blex and was orginally posted on www.ac-web.org
//This script was created after being inspired by Arena-Tournament's player commands. www.arena-tournament.com
 
class utility_commandscript : public CommandScript
{
public:
    utility_commandscript() : CommandScript("utility_commandscript") { }
 
    ChatCommand* GetCommands() const
    {
        static ChatCommand utilityCommandTable[] =
        {
            { "changerace",             SEC_PLAYER,  false, &HandleChangeRaceCommand,           "", NULL },
                        { "changefaction",                      SEC_PLAYER,  false, &HandleChangeFactionCommand,                "", NULL },
                        { "maxskills",                      SEC_PLAYER,  false, &HandleMaxSkillsCommand,                "", NULL },
                        { "customize",                      SEC_PLAYER,  false, &HandleCustomizeCommand,                "", NULL },
                        { "mmr",                                SEC_PLAYER,  false, &HandleMmrCommand,                  "", NULL },
						{ "duel",	    SEC_PLAYER,     true, &HandleDuelChatCommand,         "", NULL },
            { NULL,             0,                   false, NULL,                               "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "utility",           SEC_PLAYER,      true, NULL,                   "", utilityCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }
 
    static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                handler->PSendSysMessage("Relog to change race of your character.");
        return true;
    }
 
    static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
    }
 
    static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->UpdateSkillsForLevel();
                handler->PSendSysMessage("Your weapon skills are now maximized.");
        return true;
    }
 
        static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {
 
        Player* me = handler->GetSession()->GetPlayer();
                me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }
 
            static bool HandleMmrCommand(ChatHandler* handler, const char* args)
        {
        Player* player = handler->GetSession()->GetPlayer();
 
        uint16 mmr;
        
                        if(ArenaTeam *getmmr = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(2))) 
							mmr = getmmr->GetMember(player->GetGUID())->MatchMakerRating;
						
						 else
							mmr = 1500; 
        
        
        handler->PSendSysMessage("Your MMR is: %u.", mmr);
        return true;
						}

			static bool HandleDuelChatCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

		me->TeleportTo(530,	-1521.469238f,	-12498.887695f,	3.447278f,	.025931f); // MapId, X, Y, Z, O
                return true;
    }
};
 
void AddSC_utility_commandscript()
{
    new utility_commandscript();
}