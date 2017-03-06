/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
 SDName: Silithus
 SD%Complete: 100
 SDComment: Quest support: 7785, 8304, 8534, 8519.
 SDCategory: Silithus
 EndScriptData */

/* ContentData
 npc_highlord_demitrian
 npcs_rutgar_and_frankal
 go_pierre_vents
 npc_cenarion_scout_azenel
 EndContentData */

#include "scriptPCH.h"
#include "Database/DatabaseEnv.h"

/*###
 ## npc_highlord_demitrian
 ###*/

#define GOSSIP_ITEM_DEMITRIAN1 "What do you know of it?"
#define GOSSIP_ITEM_DEMITRIAN2 "I am listening , Demitrian."
#define GOSSIP_ITEM_DEMITRIAN3 "Continue, please."
#define GOSSIP_ITEM_DEMITRIAN4 "A battle?"
#define GOSSIP_ITEM_DEMITRIAN5 "<Nod>"
#define GOSSIP_ITEM_DEMITRIAN6 "Caught unaware? How?"
#define GOSSIP_ITEM_DEMITRIAN7 "So what did Ragnaros do next?"

enum
{
    QUEST_EXAMINE_THE_VESSEL        =   7785,
    ITEM_BINDINGS_WINDSEEKER_LEFT   =   18563,
    ITEM_BINDINGS_WINDSEEKER_RIGHT  =   18564,
    ITEM_VESSEL_OF_REBIRTH          =   19016,
    GOSSIP_TEXTID_DEMITRIAN1        =   6842,
    GOSSIP_TEXTID_DEMITRIAN2        =   6843,
    GOSSIP_TEXTID_DEMITRIAN3        =   6844,
    GOSSIP_TEXTID_DEMITRIAN4        =   6867,
    GOSSIP_TEXTID_DEMITRIAN5        =   6868,
    GOSSIP_TEXTID_DEMITRIAN6        =   6869,
    GOSSIP_TEXTID_DEMITRIAN7        =   6870
};

bool GossipHello_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_EXAMINE_THE_VESSEL) == QUEST_STATUS_NONE &&
            (pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_LEFT, 1, false) || pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_RIGHT, 1, false)))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN7, pCreature->GetGUID());

            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_VESSEL_OF_REBIRTH, 1);
            if (msg == EQUIP_ERR_OK)
                pPlayer->StoreNewItem(dest, ITEM_VESSEL_OF_REBIRTH, true);
            break;
    }
    return true;
}

/*###
 ## npcs_rutgar_and_frankal
 ###*/

//gossip item text best guess
#define GOSSIP_ITEM_SEEK1 "I seek information about Natalia"

#define GOSSIP_ITEM_RUTGAR2 "That sounds dangerous!"
#define GOSSIP_ITEM_RUTGAR3 "What did you do?"
#define GOSSIP_ITEM_RUTGAR4 "Who?"
#define GOSSIP_ITEM_RUTGAR5 "Women do that. What did she demand?"
#define GOSSIP_ITEM_RUTGAR6 "What do you mean?"
#define GOSSIP_ITEM_RUTGAR7 "What happened next?"

#define GOSSIP_ITEM_FRANKAL11 "Yes, please continue"
#define GOSSIP_ITEM_FRANKAL12 "What language?"
#define GOSSIP_ITEM_FRANKAL13 "The Priestess attacked you?!"
#define GOSSIP_ITEM_FRANKAL14 "I should ask the monkey about this"
#define GOSSIP_ITEM_FRANKAL15 "Then what..."

enum
{
    QUEST_DEAREST_NATALIA       =   8304,
    NPC_RUTGAR                  =   15170,
    NPC_FRANKAL                 =   15171,
    TRIGGER_RUTGAR              =   15222,
    TRIGGER_FRANKAL             =   15221,
    GOSSIP_TEXTID_RF            =   7754,
    GOSSIP_TEXTID_RUTGAR1       =   7755,
    GOSSIP_TEXTID_RUTGAR2       =   7756,
    GOSSIP_TEXTID_RUTGAR3       =   7757,
    GOSSIP_TEXTID_RUTGAR4       =   7758,
    GOSSIP_TEXTID_RUTGAR5       =   7759,
    GOSSIP_TEXTID_RUTGAR6       =   7760,
    GOSSIP_TEXTID_RUTGAR7       =   7761,
    GOSSIP_TEXTID_FRANKAL1      =   7762,
    GOSSIP_TEXTID_FRANKAL2      =   7763,
    GOSSIP_TEXTID_FRANKAL3      =   7764,
    GOSSIP_TEXTID_FRANKAL4      =   7765,
    GOSSIP_TEXTID_FRANKAL5      =   7766,
    GOSSIP_TEXTID_FRANKAL6      =   7767
};

bool GossipHello_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
            pCreature->GetEntry() == NPC_RUTGAR &&
            !pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
            pCreature->GetEntry() == NPC_FRANKAL &&
            pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RF, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR7, pCreature->GetGUID());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_RUTGAR, pCreature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL12, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL13, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL14, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL15, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 14:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL6, pCreature->GetGUID());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_FRANKAL, pCreature->GetGUID());
            break;
    }
    return true;
}

enum
{
    SPELL_SET_AURA            = 24746,
    SPELL_RED_LIGHTNING       = 24240,

    ITEM_SET_ENTRY            = 492,

    ITEM_SET_SHOULDERS        = 20406,
    ITEM_SET_CHEST            = 20407,
    ITEM_SET_HEAD             = 20408,

    SPELL_APPARITION          = 25035,

    GO_TYPE_PIERRE_ERR        = 0,
    GO_TYPE_PIERRE_INF        = 1,
    GO_TYPE_PIERRE_MOYENNE    = 2,
    GO_TYPE_PIERRE_SUP        = 3,

    // Pierre moyenne
    ITEM_ACCES_PIERRE_MOYENNE = 20422,
    AURA_ACCES_PIERRE_MOYENNE = 24748,

    // Pierre superieure
    ITEM_ACCES_PIERRE_SUP     = 20451,
    AURA_ACCES_PIERRE_SUP     = 24782,

    GOSSIP_STONE_FIRST_HELLO    = 69,
    GOSSIP_STONE_FIRST_OPTION   = NOST_TEXT(220)
};

struct Silithus_WindStonesBossData
{
    int stoneType;
    int action;
    int summonEntry;
    int reqItem;
    int gossipOption;
};
static Silithus_WindStonesBossData const windStonesBosses[] =
{
    {GO_TYPE_PIERRE_INF,    1,  15209,  20416, NOST_TEXT(223) },
    {GO_TYPE_PIERRE_INF,    2,  15307,  20419, NOST_TEXT(224) },
    {GO_TYPE_PIERRE_INF,    3,  15212,  20418, NOST_TEXT(225) },
    {GO_TYPE_PIERRE_INF,    4,  15211,  20420, NOST_TEXT(226) },

    {GO_TYPE_PIERRE_MOYENNE,1,  15206,  20432, NOST_TEXT(227) },
    {GO_TYPE_PIERRE_MOYENNE,2,  15208,  20435, NOST_TEXT(228) },
    {GO_TYPE_PIERRE_MOYENNE,3,  15220,  20433, NOST_TEXT(229) },
    {GO_TYPE_PIERRE_MOYENNE,4,  15207,  20436, NOST_TEXT(230) },

    {GO_TYPE_PIERRE_SUP,    1,  15203,  20447, NOST_TEXT(231) },
    {GO_TYPE_PIERRE_SUP,    2,  15205,  20449, NOST_TEXT(232) },
    {GO_TYPE_PIERRE_SUP,    3,  15204,  20448, NOST_TEXT(233) },
    {GO_TYPE_PIERRE_SUP,    4,  15305,  20450, NOST_TEXT(234) },
};

struct go_pierre_ventsAI: public GameObjectAI
{
    go_pierre_ventsAI(GameObject* pGo) : GameObjectAI(pGo) {}

    uint32 GetStoneType()
    {
        switch (me->GetEntry())
        {
            // Pierre SUP
            case 180466:
            case 180539:
            case 180559:
                return GO_TYPE_PIERRE_SUP;
            // Pierre MOYENNE
            case 180554:
            case 180534:
            case 180502:
            case 180461:
                return GO_TYPE_PIERRE_MOYENNE;
            // Pierre INF
            case 180456:
            case 180518:
            case 180529:
            case 180544:
            case 180549:
            case 180564:
                return GO_TYPE_PIERRE_INF;
            default:
                return GO_TYPE_PIERRE_ERR;
        }
    }
    uint32 SelectRandomBoss(uint32 stoneType)
    {
        std::vector<uint32> possibleBosses;
        for (int i = 0; i < sizeof(windStonesBosses) / sizeof(windStonesBosses[0]); ++i)
            if (windStonesBosses[i].stoneType == stoneType)
                possibleBosses.push_back(windStonesBosses[i].summonEntry);
        ASSERT(!possibleBosses.empty());
        return possibleBosses[urand(0, possibleBosses.size() - 1)];
    }

    bool CheckPlayerHasAura(uint32 uiReqAura, Player *pUser, uint32 itemToDelete = 0)
    {
        if (uiReqAura && !pUser->HasAura(uiReqAura))
            if (!pUser->isGameMaster())
                return false;
        return true;
    }

    void UseFailed(Unit* user)
    {
        if (user->isAlive())
        {
            user->CastSpell(user, SPELL_RED_LIGHTNING, true);
            user->DealDamage(user, user->GetHealth() > 1000 ? 1000 : user->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
    }
    bool CanUse(Player* user)
    {
        if (!user || !me->isSpawned())
            return false;

        bool playerHasAura = true;

        ///- Check if allowed to use the stone ?
        switch (GetStoneType())
        {
            // Pierre SUP
            case GO_TYPE_PIERRE_SUP:
                if (!user->HasItemWithIdEquipped(ITEM_ACCES_PIERRE_SUP))
                    playerHasAura = false;
            // Pierre MOYENNE
            case GO_TYPE_PIERRE_MOYENNE:
                if (!user->HasItemWithIdEquipped(ITEM_ACCES_PIERRE_MOYENNE))
                    playerHasAura = false;
            // Pierre INF
            case GO_TYPE_PIERRE_INF:
                if (!user->HasItemWithIdEquipped(ITEM_SET_HEAD) ||
                    !user->HasItemWithIdEquipped(ITEM_SET_SHOULDERS) ||
                    !user->HasItemWithIdEquipped(ITEM_SET_CHEST))
                    playerHasAura = false;
                break;
        }

        if (!playerHasAura)
        {
            UseFailed(user);
            return false;
        }
        return true;
    }

    bool OnUse(Unit* user)
    {
        Player* player = user->ToPlayer();
        if (!CanUse(player))
            return true;

        uint32 stoneType = GetStoneType();
        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_STONE_FIRST_OPTION + stoneType - 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        for (int i = 0; i < sizeof(windStonesBosses) / sizeof(windStonesBosses[0]); ++i)
            if (windStonesBosses[i].stoneType == stoneType)
                if (player->HasItemCount(windStonesBosses[i].reqItem, 1))
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, windStonesBosses[i].gossipOption, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + windStonesBosses[i].action);

        player->SEND_GOSSIP_MENU(GOSSIP_STONE_FIRST_HELLO + stoneType - 1, me->GetGUID());
        return true;
    }

    bool GossipSelect(Player* player, uint32 action)
    {
        if (!CanUse(player))
            return true;

        uint32 stoneType = GetStoneType();
        if (!stoneType)
            return true;

        uint32 summonEntry = 0;
        uint32 textId = 0;

        ///- Let's find out which mob we have to summon.
        switch (stoneType)
        {
            case GO_TYPE_PIERRE_SUP:
                textId = 116;
                break;
            case GO_TYPE_PIERRE_MOYENNE:
                textId = 115;
                break;
            case GO_TYPE_PIERRE_INF:
                textId = 105 + (player->getRace());
                break;
        }
        for (int i = 0; i < sizeof(windStonesBosses) / sizeof(windStonesBosses[0]); ++i)
            if (windStonesBosses[i].stoneType == stoneType && action == GOSSIP_ACTION_INFO_DEF + windStonesBosses[i].action)
                if (player->HasItemCount(windStonesBosses[i].reqItem, 1))
                {
                    summonEntry = windStonesBosses[i].summonEntry;
                    player->DestroyItemCount(windStonesBosses[i].reqItem, 1, true, false);
                }

        if (!summonEntry && action != GOSSIP_ACTION_INFO_DEF)
        {
            UseFailed(player);
            return true;
        }

        if (!summonEntry)
            summonEntry = SelectRandomBoss(stoneType);

        if (!summonEntry)
            return true;

        ///- Destroy required items.
        if (!player->ToPlayer()->isGameMaster())
        {
            switch (stoneType)
            {
                case GO_TYPE_PIERRE_SUP:
                    player->DestroyEquippedItem(ITEM_ACCES_PIERRE_SUP);
                // no break
                case GO_TYPE_PIERRE_MOYENNE:
                    player->DestroyEquippedItem(ITEM_ACCES_PIERRE_MOYENNE);
                // no break
                case GO_TYPE_PIERRE_INF:
                    player->DestroyEquippedItem(ITEM_SET_SHOULDERS);
                    player->DestroyEquippedItem(ITEM_SET_CHEST);
                    player->DestroyEquippedItem(ITEM_SET_HEAD);
                    break;
            }
        }

        ///- Summon the creature
        if (Creature* pInvoc = me->SummonCreature(summonEntry, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), me->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 3600000))
        {
            pInvoc->SetTempPacified(5000);
            pInvoc->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            player->CastSpell(player, SPELL_RED_LIGHTNING, true);
            pInvoc->CastSpell(pInvoc, SPELL_APPARITION, true);
            pInvoc->SetLootRecipient(player); // Force tag for summoner
            if (textId)
                pInvoc->MonsterSay(NOST_TEXT(textId));
        }

        ///- Mark stone as used.
        me->UseDoorOrButton();
        if (stoneType == GO_TYPE_PIERRE_SUP)
            me->SetRespawnTime(3600);
        else if (stoneType == GO_TYPE_PIERRE_MOYENNE)
            me->SetRespawnTime(300);
        else if (stoneType == GO_TYPE_PIERRE_INF)
            me->SetRespawnTime(90);
        else
            me->SetRespawnTime(me->ComputeRespawnDelay());
        return true;
    }
};

GameObjectAI* GetAIgo_pierre_vents(GameObject *go)
{
    return new go_pierre_ventsAI(go);
}

bool GossipSelect_go_pierre_vents(Player* user, GameObject* gobj, uint32 sender, uint32 action)
{
    user->CLOSE_GOSSIP_MENU();
    if (go_pierre_ventsAI* ai = dynamic_cast<go_pierre_ventsAI*>(gobj->AI()))
        ai->GossipSelect(user, action);
    return true;
}

/*###
 ## npc_cenarion_scout_azenel
 ###*/

#define GOSSIP_ITEM_REPORT "Your report, please!"

#define SAY_COMPLETE "Quickly, bring my report to Cenarion Hold!"

#define SPELL_CREATE_HIVE_ZORA_SCOUT_REPORT    25843

bool GossipHello_npc_cenarion_scout_azenel(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(8534) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_REPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pCreature->GetEntry(), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_cenarion_scout_azenel(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, SPELL_CREATE_HIVE_ZORA_SCOUT_REPORT, false);
        pCreature->MonsterWhisper(SAY_COMPLETE, pPlayer);
    }
    return true;
}

enum
{
    SPELL_FOOLS_PLIGHT              = 23504,
    
    SPELL_SOUL_FLAME                = 23272,
    SPELL_DREADFUL_FRIGHT           = 23275,
    SPELL_CREEPING_DOOM             = 23589,
    SPELL_CRIPPLING_CLIP            = 23279,

    EMOTE_IMMOBILIZED               = -1000650,
    
    SPELL_FROST_TRAP                = 13810,
    
    NPC_NELSON_THE_NICE             = 14536,
    NPC_SOLENOR_THE_SLAYER          = 14530,
    NPC_CREEPING_DOOM               = 14761,
    NPC_THE_CLEANER                 = 14503,
    
    QUEST_STAVE_OF_THE_ANCIENTS     = 7636
};

#define GOSSIP_ITEM                 "Show me your real face, demon."

/*#####
 ## npc_nelson_the_nice
 ######*/

/*#####
 ## npc_solenor_the_slayer
 ######*/

struct npc_solenorAI : public ScriptedAI
{
    npc_solenorAI(Creature* pCreature) : ScriptedAI(pCreature) 
    { 
        m_bTransform      = false;
        m_uiDespawn_Timer = 0;
        Reset(); 
    }

    uint32 m_uiTransform_Timer;
    uint32 m_uiTransformEmote_Timer;
    bool m_bTransform;

    ObjectGuid m_hunterGuid;
    uint32 m_uiDreadfulFright_Timer;
    uint32 m_uiCreepingDoom_Timer;
    uint32 m_uiCastSoulFlame_Timer;
    uint32 m_uiDespawn_Timer;

    void Reset()
    {
        switch (m_creature->GetEntry())
        {
            case NPC_NELSON_THE_NICE:
                m_creature->SetRespawnDelay(35*MINUTE);
                m_creature->SetRespawnTime(35*MINUTE);
                m_creature->SetHomePosition(-7724.21f, 1676.43f, 7.0571f, 4.80044f);
                m_creature->NearTeleportTo(-7724.21f, 1676.43f, 7.0571f, 4.80044f);
                if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != WAYPOINT_MOTION_TYPE)
                {
                    m_creature->SetDefaultMovementType(WAYPOINT_MOTION_TYPE);
                    m_creature->GetMotionMaster()->Initialize();
                }

                m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                m_uiTransform_Timer      = 10000;
                m_uiTransformEmote_Timer = 5000;
                m_bTransform             = false;
                m_uiDespawn_Timer        = 0;
                m_uiCastSoulFlame_Timer  = 0;
                break;
            case NPC_SOLENOR_THE_SLAYER:
                if (!m_uiDespawn_Timer)
                {
                    m_uiDespawn_Timer = 20*MINUTE*IN_MILLISECONDS; 
                    m_uiCastSoulFlame_Timer  = 150;
                    m_creature->AddAura(SPELL_SOUL_FLAME); // apply on spawn in case of instant Freezing Trap
                }

                m_hunterGuid.Clear();
                m_uiDreadfulFright_Timer = urand(10000, 15000);
                m_uiCreepingDoom_Timer   = urand(3000, 6000);
                break;
        }
    }

    /** Nelson the Nice */
    void Transform()
    {
        m_creature->UpdateEntry(NPC_SOLENOR_THE_SLAYER);
        m_creature->SetHomePosition(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation());
        m_creature->SetDefaultMovementType(IDLE_MOTION_TYPE);
        m_creature->GetMotionMaster()->Initialize();
        Reset();
    }

    void BeginEvent(ObjectGuid playerGuid)
    {
        m_hunterGuid = playerGuid;
        m_creature->GetMotionMaster()->Clear(false);
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
        m_bTransform = true;
    }

    /** Solenor the Slayer */
    void Aggro(Unit* pWho)
    {
        if (pWho->getClass() == CLASS_HUNTER && (m_hunterGuid.IsEmpty() || m_hunterGuid == pWho->GetObjectGuid())/*&& pWho->GetQuestStatus(QUEST_STAVE_OF_THE_ANCIENTS) == QUEST_STATUS_INCOMPLETE*/)
        {
            m_hunterGuid = pWho->GetObjectGuid();
        }
        else
            DemonDespawn();
    }
    
    void EnterEvadeMode() override
    {
        m_creature->RemoveGuardians();
        
        ScriptedAI::EnterEvadeMode();
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (m_creature->getVictim())
            pSummoned->AI()->AttackStart(m_creature->getVictim());
    }
    
    void JustDied(Unit* /*pKiller*/)
    {
        m_creature->SetHomePosition(-7724.21f, 1676.43f, 7.0571f, 4.80044f);
        // DRSS
        uint32 m_respawn_delay_Timer = 3*HOUR;
        if (sWorld.GetActiveSessionCount() > BLIZZLIKE_REALM_POPULATION)
            m_respawn_delay_Timer *= float(BLIZZLIKE_REALM_POPULATION) / float(sWorld.GetActiveSessionCount());

        m_creature->SetRespawnDelay(m_respawn_delay_Timer);
        m_creature->SetRespawnTime(m_respawn_delay_Timer);
        m_creature->SaveRespawnTime();
    }

    void DemonDespawn(bool triggered = true)
    {
        m_creature->RemoveGuardians();
        m_creature->SetHomePosition(-7724.21f, 1676.43f, 7.0571f, 4.80044f);
        m_creature->SetRespawnDelay(15*MINUTE);
        m_creature->SetRespawnTime(15*MINUTE);
        m_creature->SaveRespawnTime();

        if (triggered)
        {
            Creature* pCleaner = m_creature->SummonCreature(NPC_THE_CLEANER, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetAngle(m_creature), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20*MINUTE*IN_MILLISECONDS);
            if (pCleaner)
            {
                ThreatList const& tList = m_creature->getThreatManager().getThreatList();
                
                for (ThreatList::const_iterator itr = tList.begin();itr != tList.end(); ++itr)
                {
                    if (Unit* pUnit = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
                    {
                        if (pUnit->isAlive())
                        {
                            pCleaner->SetInCombatWith(pUnit);
                            pCleaner->AddThreat(pUnit);
                            pCleaner->AI()->AttackStart(pUnit);
                        }
                    }
                }
            }
        }
        
        m_creature->ForcedDespawn();
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
       
        if (pSpell && pSpell->Id == 14268)   // Wing Clip (Rank 3)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_CRIPPLING_CLIP, CAST_TRIGGERED) == CAST_OK)
                DoScriptText(EMOTE_IMMOBILIZED, m_creature);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        /** Nelson the Nice */
        if (m_bTransform) 
        {
            if (m_uiTransformEmote_Timer)
            {
                if (m_uiTransformEmote_Timer <= uiDiff)
                {
                    m_creature->HandleEmote(EMOTE_ONESHOT_LAUGH);
                    m_uiTransformEmote_Timer = 0;
                }
                else
                    m_uiTransformEmote_Timer -= uiDiff;
            }

            if (m_uiTransform_Timer < uiDiff)
            {
                m_bTransform = false;
                Transform();
            } 
            else
                m_uiTransform_Timer -= uiDiff;
        }

        /** Solenor the Slayer */
        if (m_uiDespawn_Timer)
        {
            if (m_uiDespawn_Timer <= uiDiff)
            {
                if (m_creature->isAlive() && !m_creature->isInCombat())
                    DemonDespawn(false);
            }
            else
                m_uiDespawn_Timer -= uiDiff;
        }
        
        if (m_uiCastSoulFlame_Timer)
        {
            if (m_uiCastSoulFlame_Timer <= uiDiff)
            {
                // delay this cast so spell animation is visible to the player
                m_creature->CastSpell(m_creature, SPELL_SOUL_FLAME, false);
                m_uiCastSoulFlame_Timer = 0;
            }
            else
                m_uiCastSoulFlame_Timer -= uiDiff;
        }
    
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        if (m_creature->HasAura(SPELL_SOUL_FLAME) && m_creature->HasAura(SPELL_FROST_TRAP))
                m_creature->RemoveAurasDueToSpell(SPELL_SOUL_FLAME);
    
        if (m_creature->getThreatManager().getThreatList().size() > 1 /*|| pHunter->isDead()*/)
            DemonDespawn();

        if (m_uiCreepingDoom_Timer < uiDiff) 
        {
            DoCastSpellIfCan(m_creature, SPELL_CREEPING_DOOM);
            m_uiCreepingDoom_Timer = 15000;
        }
        else 
            m_uiCreepingDoom_Timer -= uiDiff;

        if (m_uiDreadfulFright_Timer < uiDiff)
        {
            if (Unit* pUnit = m_creature->getVictim())
            {
                if (m_creature->GetDistance2d(pUnit) > 5.0f)
                {
                    if (DoCastSpellIfCan(pUnit, SPELL_DREADFUL_FRIGHT) == CAST_OK)
                        m_uiDreadfulFright_Timer = urand(15000, 20000);
                }
            }
        }
        else
            m_uiDreadfulFright_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_npc_solenor(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_STAVE_OF_THE_ANCIENTS) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_ITEM , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_solenor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction )
{
    pPlayer->CLOSE_GOSSIP_MENU();
    ((npc_solenorAI*)pCreature->AI())->BeginEvent(pPlayer->GetObjectGuid());
    return true;
}

CreatureAI* GetAI_npc_solenor(Creature* pCreature)
{
    return new npc_solenorAI(pCreature);
}

/*#####
 ## npc_creeping_doom
 ######*/

struct npc_creeping_doomAI : public ScriptedAI
{
    npc_creeping_doomAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset() {};
    
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage) override
    {
        Unit* pOwner = m_creature->GetCharmerOrOwner();
        if (pDoneBy && pOwner)
        {
            pOwner->AddThreat(pDoneBy);
            pOwner->SetInCombatWith(pDoneBy);
        }
        ScriptedAI::DamageTaken(pDoneBy, uiDamage);
    }
};

CreatureAI* GetAI_npc_creeping_doom(Creature* pCreature)
{
    return new npc_creeping_doomAI(pCreature);
}

/*#####
 ## npc_prince_thunderaan
 ######*/

enum
{
    SPELL_TENDRILS_OF_AIR           = 23009, // KB
    SPELL_TEARS_OF_THE_WIND_SEEKER    = 23011
};

struct npc_prince_thunderaanAI : public ScriptedAI
{
    npc_prince_thunderaanAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        engaged = false;
        emerged = false;
        Reset();
    }

    uint32 m_uiTendrilsTimer;
    uint32 m_uiTearsTimer;
    bool engaged;
    bool emerged;

    void Reset()
    {
        m_uiTendrilsTimer   = 8000;
        m_uiTearsTimer      = 15000;
    }

    void SpellHitTarget(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pCaster->GetTypeId() != TYPEID_PLAYER)
            return;

        if (pSpell->Id == SPELL_TENDRILS_OF_AIR)
            m_creature->getThreatManager().modifyThreatPercent(pCaster, -100);
    }

    void Aggro(Unit* pWho)
    {
        if (!engaged)
        {
            m_creature->MonsterYell("My power is discombobulatingly devastating! It is ludicrous that these mortals even attempt to enter my realm!", 0);
            engaged = true;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!emerged)
        {
            m_creature->CastSpell(m_creature, 20568, false);     // Ragnaros Emerge
            emerged = true;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTendrilsTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_TENDRILS_OF_AIR) == CAST_OK) // KB
                m_uiTendrilsTimer = urand(12000, 20000);
        }
        else
            m_uiTendrilsTimer -= uiDiff;

        if (m_uiTearsTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_TEARS_OF_THE_WIND_SEEKER) == CAST_OK)
                m_uiTearsTimer = urand(8000, 11000);
        }
        else
            m_uiTearsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_prince_thunderaan(Creature* pCreature)
{
    return new npc_prince_thunderaanAI(pCreature);
}


/*#####
 ## npc_colossus
 ######*/

enum
{
    SPELL_COLOSSAL_SMASH            = 26167 // Maxi KB
};

struct npc_colossusAI : public ScriptedAI
{
    npc_colossusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiColossalSmashTimer;
    uint32 m_uiColossalSmashEmoteTimer;
    bool firstSmash;

    void Reset()
    {
        firstSmash = true;
        m_uiColossalSmashTimer = 60000;
        m_uiColossalSmashEmoteTimer = 0;
    }

    void SpellHitTarget(Unit* pCaster, const SpellEntry* pSpell)
    {
    }

    void Aggro(Unit* pWho)
    {
    }

    void EnterEvadeMode()
    {
        // Ustaag <Nostalrius> : Must neither resume life if Evade, nor return to its starting point
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        // To avoid jerky movements after aggro end
        m_creature->GetMotionMaster()->MoveIdle();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiColossalSmashTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_COLOSSAL_SMASH) == CAST_OK) // Maxi KB
            {
                m_creature->MonsterTextEmote("Colossus begins to cast Colossus Smash", NULL);
                m_uiColossalSmashTimer = firstSmash ? 10000 : 60000;
                m_uiColossalSmashEmoteTimer = 5000;

                if (firstSmash)
                    firstSmash = false;
                else
                    firstSmash = true;
            }
        }
        else
            m_uiColossalSmashTimer -= uiDiff;

        if (m_uiColossalSmashEmoteTimer && m_uiColossalSmashEmoteTimer < uiDiff)
        {
            m_creature->MonsterTextEmote("Colossus lets loose a massive attack", NULL);
            m_uiColossalSmashEmoteTimer = 0;
        }
        else
            m_uiColossalSmashEmoteTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_colossus(Creature* pCreature)
{
    return new npc_colossusAI(pCreature);
}


/*#####
 ## npc_resonating_Crystal
 ######*/

// UPDATE `creature_template` SET `ScriptName` = 'npc_resonating_Crystal' WHERE `entry` = 15769;

enum
{
    GO_RESONATING_CRYSTAL_FORMATION     = 180810,

    SPELL_WHISPERINGS                   = 26197    // MC
};

struct npc_resonating_CrystalAI : public ScriptedAI
{
    npc_resonating_CrystalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool playerDetected;
    uint32 m_uiCheckTimer;
    uint32 m_uiWisperingsTimer;

    void Reset()
    {
        SetCombatMovement(false);
        playerDetected      = false;
        m_uiCheckTimer      = 2000;
        m_uiWisperingsTimer = 1000;
    }

    void MoveInLineOfSight(Unit* who)
    {
        if (who->GetTypeId() != TYPEID_PLAYER || who->ToPlayer()->isGameMaster())
            return;

        if (!who->isAlive())
            return;

        playerDetected = m_creature->IsWithinDistInMap(who, 50.0f) ? true : false;
    }

    bool MoreThanOnePlayerNear()
    {
        Map::PlayerList const& players = m_creature->GetMap()->GetPlayers();
        int var = 0;
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            Player* pPlayer = itr->getSource();
            if (pPlayer && pPlayer->isAlive() && m_creature->IsWithinDistInMap(pPlayer, 40.0f) && m_creature->IsWithinLOSInMap(pPlayer) && !pPlayer->isGameMaster())
                ++var;
            if (var > 1)
                return true;
        }
        return false;
    }

    void AggroAllPlayerNear()
    {
        Map::PlayerList const& players = m_creature->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            Player* pPlayer = itr->getSource();
            if (pPlayer && pPlayer->isAlive() && m_creature->IsWithinDistInMap(pPlayer, 40.0f) && m_creature->IsWithinLOSInMap(pPlayer) && !pPlayer->isGameMaster())
            {
                m_creature->AddThreat(pPlayer);
                m_creature->SetInCombatWith(pPlayer);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (playerDetected)
        {
            if (m_uiCheckTimer < uiDiff)
            {
                if (MoreThanOnePlayerNear())
                    AggroAllPlayerNear();
                else
                    EnterEvadeMode();
                m_uiCheckTimer = 2000;
            }
            else
                m_uiCheckTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Whisperings of C'Thun (MC)
        if (MoreThanOnePlayerNear())
        {
            if (m_uiWisperingsTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    if (DoCastSpellIfCan(pTarget, SPELL_WHISPERINGS) == CAST_OK)
                        m_uiWisperingsTimer = 30000;
            }
            else
                m_uiWisperingsTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_resonating_Crystal(Creature* pCreature)
{
    return new npc_resonating_CrystalAI(pCreature);
}


/*###
 ## npc_AQwar_effort
 ###*/

enum WarEffortItemType
{
    WAREFFORT_BAR,
    WAREFFORT_HERBS,
    WAREFFORT_SKINS,
    WAREFFORT_COOKING,
    WAREFFORT_BANDAGES,
};

struct WarEffort
{
    uint32 itemID, reqCount;
    uint32 saveVarID;           // = itemID / This variable is left in case the ID of the item is not an appropriate choice.
    char itemName[50];
    WarEffortItemType type;
};

/*
 -- SQL a executer pour RESET l'event.
 -- Le champ 'comment' sert pour le site.
 REPLACE INTO variables (`index`, value, `comment`) VALUES
 -- Neutre
 (2840, 0, "AQ|N|Barre de cuivre|90000"),
 (8831, 0, "AQ|N|Lotus pourpre|26000"),
 (4304, 0, "AQ|N|Cuir epais|80000"),
 (6887, 0, "AQ|N|Jaune-queue tachete|17000"),
 (14529, 0, "AQ|N|Bandage en etoffe runique|400000"),
 -- Alliance
 (3575, 0, "AQ|A|Barre de fer|28000"),
 (12359, 0, "AQ|A|Barre de thorium|24000"),
 (8836, 0, "AQ|A|Larmes d'Arthas|20000"),
 (3820, 0, "AQ|A|Etouffante|33000"),
 (2318, 0, "AQ|A|Cuir leger|180000"),
 (2319, 0, "AQ|A|Cuir moyen|110000"),
 (12210, 0, "AQ|A|Roti de raptor|20000"),
 (5095, 0, "AQ|A|Thon arc-en-ciel|14000"),
 (1251, 0, "AQ|A|Bandage en lin|800000"),
 (6450, 0, "AQ|A|Bandage en soie|600000"),
 -- Horde
 (3576, 0, "AQ|H|Barre d'etain|22000"),
 (3860, 0, "AQ|H|Barre de mithril|18000"),
 (2447, 0, "AQ|H|Pacifique|96000"),
 (4625, 0, "AQ|H|Fleur de feu|19000"),
 (4234, 0, "AQ|H|Cuir lourd|60000"),
 (8170, 0, "AQ|H|Cuir robuste|60000"),
 (12209, 0, "AQ|H|Steak de loup|10000"),
 (13935, 0, "AQ|H|Pain de saumon|10000"),
 (3530, 0, "AQ|H|Bandage en laine|250000"),
 (8544, 0, "AQ|H|Bandage en tisse-mage|250000");
 */

static const WarEffort SharedObjectives[5] =
{
    {2840,  90000,  2840,  "Barre de cuivre", WAREFFORT_BAR},
    {8831,  26000,  8831,  "Lotus pourpre", WAREFFORT_HERBS},
    {4304,  80000,  4304,  "Cuir epais", WAREFFORT_SKINS},
    {6887,  17000,  6887,  "Jaune-queue tachete", WAREFFORT_COOKING},
    {14529, 400000, 14529, "Bandage en etoffe runique", WAREFFORT_BANDAGES}
};

static const WarEffort AllianceObjectives[10] =
{
    {3575,  28000,  3575,   "Barre de fer", WAREFFORT_BAR},
    {12359, 24000,  12359,  "Barre de thorium", WAREFFORT_BAR},
    {8836,  20000,  8836,   "Larmes d'Arthas", WAREFFORT_HERBS},
    {3820,  33000,  3820,   "Etouffante", WAREFFORT_HERBS},
    {2318,  180000, 2318,   "Cuir leger", WAREFFORT_SKINS},
    {2319,  110000, 2319,   "Cuir moyen", WAREFFORT_SKINS},
    {12210, 20000,  12210,  "Roti de raptor", WAREFFORT_COOKING},
    {5095,  14000,  5095,   "Thon arc-en-ciel", WAREFFORT_COOKING},
    {1251,  800000, 1251,   "Bandage en lin", WAREFFORT_BANDAGES},
    {6450,  600000, 6450,   "Bandage en soie", WAREFFORT_BANDAGES}
};

static const WarEffort HordeObjectives[10] =
{
    {3576,  22000,  3576,   "Barre d'etain", WAREFFORT_BAR},
    {3860,  18000,  3860,   "Barre de mithril", WAREFFORT_BAR},
    {2447,  96000,  2447,   "Pacifique", WAREFFORT_HERBS},
    {4625,  19000,  4625,   "Fleur de feu", WAREFFORT_HERBS},
    {4234,  60000,  4234,   "Cuir lourd", WAREFFORT_SKINS},
    {8170,  60000,  8170,   "Cuir robuste", WAREFFORT_SKINS},
    {12209, 10000,  12209,  "Steak de loup", WAREFFORT_COOKING},
    {13935, 10000,  13935,  "Pain de saumon", WAREFFORT_COOKING},
    {3530,  250000, 3530,   "Bandage en laine", WAREFFORT_BANDAGES},
    {8544,  250000, 8544,   "Bandage en tisse-mage", WAREFFORT_BANDAGES}
};

enum
{
    // Alliance
    NPC_FIELD_MARSHAL_SNOWFALL  = 15701,
    NPC_COMMANDER_STRONGHAMMER  = 15458,

    // Horde
    NPC_WARLORD_GORCHUK         = 15700,
    NPC_GENERAL_ZOG             = 15539
};

// UPDATE `creature_template` SET `ScriptName` = 'npc_AQwar_effort' WHERE `entry` IN (15701, 15458, 15700, 15539);

bool GossipHello_npc_AQwar_effort(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    switch (pCreature->GetEntry())
    {
        case NPC_FIELD_MARSHAL_SNOWFALL:    // Shared + Alliance
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Effort de guerre commun", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        // no break
        case NPC_COMMANDER_STRONGHAMMER:    // Alliance only
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Effort de guerre Alliance", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case NPC_WARLORD_GORCHUK:           // Shared + Horde
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Effort de guerre commun", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        // no break
        case NPC_GENERAL_ZOG:               // Horde only
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Effort de guerre Horde", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            break;
        default:
            break;
    }

    pPlayer->SEND_GOSSIP_MENU(1, pCreature->GetObjectGuid()); // Text to put here the state of the resources
    return true;
}

bool GossipSelect_npc_AQwar_effort(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
        {
            // Shared War Effort
            for (int i = 0; i < 5; i++)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(SharedObjectives[i].saveVarID, 0);
                uint32 objectif = SharedObjectives[i].reqCount;
                if (stock > objectif)
                    stock = objectif;

                char sMessage[200] = "";
                sprintf(sMessage, "%s: %u / %u", SharedObjectives[i].itemName, stock, objectif);

                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF+1:
        {
            // Alliance War Effort
            for (int i = 0; i < 10; i++)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(AllianceObjectives[i].saveVarID, 0);
                uint32 objectif = AllianceObjectives[i].reqCount;

                if (stock > objectif)
                    stock = objectif;

                char sMessage[200] = "";
                sprintf(sMessage, "%s: %u / %u", AllianceObjectives[i].itemName, stock, objectif);

                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF+2:
        {
            // Horde War Effort
            for (int i = 0; i < 10; i++)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(HordeObjectives[i].saveVarID, 0);
                uint32 objectif = HordeObjectives[i].reqCount;

                if (stock > objectif)
                    stock = objectif;

                char sMessage[200] = "";
                sprintf(sMessage, "%s: %u / %u", HordeObjectives[i].itemName, stock, objectif);

                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->CLOSE_GOSSIP_MENU();
            return true;
        default:
            break;
    }

    pPlayer->SEND_GOSSIP_MENU(1, pCreature->GetObjectGuid());
    return true;
}

/*###
 ## npc_AQwar_collector
 ###*/

// UPDATE `creature_template` SET `ScriptName` = 'npc_AQwar_collector' WHERE `subname` like '%collector%' and subname not like '%ancestry%';

bool GossipHello_npc_AQwar_collector(Player* pPlayer, Creature* pCreature)
{
    bool objectiveReached = false;
    char itemNameReqReached[51] = "";

    QuestRelationsMapBounds bounds = sObjectMgr.GetCreatureQuestRelationsMapBounds(pCreature->GetEntry());
    for (QuestRelationsMap::const_iterator itr = bounds.first; itr != bounds.second; ++itr)
    {
        uint32 quest_id = itr->second;
        if (!quest_id)
            continue;
        Quest const *pQuest = sObjectMgr.GetQuestTemplate(quest_id);
        if (!pQuest)
            continue;

        for (uint8 i = 0; i < 5; i++)
        {
            if (pQuest->ReqItemId[0] == SharedObjectives[i].itemID)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(SharedObjectives[i].saveVarID, 0);
                uint32 objectif = SharedObjectives[i].reqCount;
                if (stock >= objectif)
                {
                    objectiveReached = true;
                    strcat(itemNameReqReached, SharedObjectives[i].itemName);
                    break;
                }
            }
        }
        for (uint8 i = 0; i < 10; i++)
        {
            if (pQuest->ReqItemId[0] == AllianceObjectives[i].itemID)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(AllianceObjectives[i].saveVarID, 0);
                uint32 objectif = AllianceObjectives[i].reqCount;
                if (stock >= objectif)
                {
                    objectiveReached = true;
                    strcat(itemNameReqReached, AllianceObjectives[i].itemName);
                    break;
                }
            }
        }
        for (uint8 i = 0; i < 10; i++)
        {
            if (pQuest->ReqItemId[0] == HordeObjectives[i].itemID)
            {
                uint32 stock = sObjectMgr.GetSavedVariable(HordeObjectives[i].saveVarID, 0);
                uint32 objectif = HordeObjectives[i].reqCount;
                if (stock >= objectif)
                {
                    objectiveReached = true;
                    strcat(itemNameReqReached, HordeObjectives[i].itemName);
                    break;
                }
            }
        }

        if (objectiveReached)
            break;
    }


    if (objectiveReached)
    {
        if (pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

        if (pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        char sMessage[200] = "";
        sprintf(sMessage, "La recolte de %s n'est plus necessaire.", itemNameReqReached);

        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay(sMessage, 0, 0);
        pCreature->HandleEmote(EMOTE_ONESHOT_BOW);
        return true;
    }

    if (pCreature->isQuestGiver())
    {
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    }
    return true;
}

struct GOWarEffort
{
    int Tiers;      // A titre informatif uniquement
    uint32 GOEntry;
    int faction;    // = GetTeamId() // Alliance = 0 Horde = 1
};

static const GOWarEffort GOBars[10] =
{
    // Alliance
    {1, 180780, 0},
    {2, 180781, 0},
    {3, 180782, 0},
    {4, 180783, 0},
    {5, 180784, 0},
    // Horde
    {1, 180839, 1},
    {2, 180840, 1},
    {3, 180841, 1},
    {4, 180842, 1},
    {5, 180843, 1}
};

static const GOWarEffort GOCooking[10] =
{
    // Alliance
    {1, 180800, 0},
    {2, 180806, 0},
    {3, 180807, 0},
    {4, 180808, 0},
    {5, 180809, 0},
    // Horde
    {1, 180833, 1},
    {2, 180834, 1},
    {3, 180835, 1},
    {4, 180836, 1},
    {5, 180837, 1}
};

static const GOWarEffort GOHerbs[10] =
{
    // Alliance
    {1, 180801, 0},
    {2, 180802, 0},
    {3, 180803, 0},
    {4, 180804, 0},
    {5, 180805, 0},
    // Horde
    {1, 180819, 1},
    {2, 180820, 1},
    {3, 180821, 1},
    {4, 180822, 1},
    {5, 180823, 1}
};

static const GOWarEffort GOSkins[10] =
{
    // Alliance
    {1, 180692, 0},
    {2, 180693, 0},
    {3, 180694, 0},
    {4, 180695, 0},
    {5, 180696, 0},
    // Horde
    {1, 180813, 1},
    {2, 180814, 1},
    {3, 180815, 1},
    {4, 180816, 1},
    {5, 180817, 1}
};

static const GOWarEffort GOBandages[10] =
{
    // Alliance
    {1, 180674, 0},
    {2, 180675, 0},
    {3, 180676, 0},
    {4, 180677, 0},
    {5, 180678, 0},
    // Horde
    {1, 180827, 1},
    {2, 180828, 1},
    {3, 180829, 1},
    {4, 180830, 1},
    {5, 180831, 1}
};

void HandleWarEffortGameObject(GOWarEffort const* gameobjects, Creature* questGiver, TeamId team, WarEffortItemType type)
{
    uint32 Objective    = 0;
    uint32 current      = 0;

    // Comptage de l'objectif
    for (int i = 0; i < 5; ++i)
    {
        if (SharedObjectives[i].type == type)
        {
            Objective += SharedObjectives[i].reqCount;
            current   += sObjectMgr.GetSavedVariable(SharedObjectives[i].saveVarID, 0);
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        if (team == TEAM_HORDE && HordeObjectives[i].type == type)
        {
            Objective += HordeObjectives[i].reqCount;
            current   += sObjectMgr.GetSavedVariable(HordeObjectives[i].saveVarID, 0);
        }
        if (team == TEAM_ALLIANCE && AllianceObjectives[i].type == type)
        {
            Objective += AllianceObjectives[i].reqCount;
            current   += sObjectMgr.GetSavedVariable(AllianceObjectives[i].saveVarID, 0);
        }
    }

    // Affichage des gameobjects
    uint32 tempCount = Objective;
    for (int j = 9; j >= 0; j--)
    {
        if (gameobjects[j].faction != team)
            continue;
        if (current >= tempCount)
        {
            if (GameObject* go = questGiver->FindNearestGameObject(gameobjects[j].GOEntry, 50.0f))
            {
                if (!go->isSpawned())
                {
                    go->SetRespawnTime(1209600); // 14 jours
                    go->SaveToDB();
                }
            }
        }
        tempCount -= Objective / 5;
    }
}

bool QuestComplete_npc_AQwar_collector(Player* pPlayer, Creature* pQuestGiver, Quest const* pQuest)
{
    if (!pQuest->ReqItemId[0] || !pQuest->ReqItemCount[0])
        return false;

    uint32 var = sObjectMgr.GetSavedVariable(pQuest->ReqItemId[0], 0);
    var += pQuest->ReqItemCount[0] * 2;
    sObjectMgr.SetSavedVariable(pQuest->ReqItemId[0], var, true); // ICI ON MULTIPLIE L'APPORT POUR ACCELERER L'EFFORT DE GUERRE

    // Gestion des UNIT_NPC_FLAG_QUESTGIVER et UNIT_NPC_FLAG_GOSSIP des PNJ "collector"
    char itemName[51] = "";
    bool objectiveReached = false;

    for (int i = 0; i < 5; i++)
    {
        if (pQuest->ReqItemId[0] == SharedObjectives[i].itemID)
        {
            if (var >= SharedObjectives[i].reqCount)
            {
                strcat(itemName, SharedObjectives[i].itemName);
                objectiveReached = true;
                break;
            }
        }
    }

    // Gestion apparition des GO
    // GO Bars
    HandleWarEffortGameObject(GOBars, pQuestGiver, pPlayer->GetTeamId(), WAREFFORT_BAR);
    // GO Herbs
    HandleWarEffortGameObject(GOHerbs, pQuestGiver, pPlayer->GetTeamId(), WAREFFORT_HERBS);
    // GO Skins
    HandleWarEffortGameObject(GOSkins, pQuestGiver, pPlayer->GetTeamId(), WAREFFORT_SKINS);
    // GO Cooking
    HandleWarEffortGameObject(GOCooking, pQuestGiver, pPlayer->GetTeamId(), WAREFFORT_COOKING);
    // GO Bandages
    HandleWarEffortGameObject(GOBandages, pQuestGiver, pPlayer->GetTeamId(), WAREFFORT_BANDAGES);

    switch (pPlayer->GetTeam())
    {
        case HORDE:
        {
            // Gestion des UNIT_NPC_FLAG_QUESTGIVER et UNIT_NPC_FLAG_GOSSIP des PNJ "collector"
            if (objectiveReached)
                break;

            for (int i = 0; i < 10; i++)
            {
                if (pQuest->ReqItemId[0] == HordeObjectives[i].itemID)
                {
                    if (var >= HordeObjectives[i].reqCount)
                    {
                        strcat(itemName, HordeObjectives[i].itemName);
                        objectiveReached = true;
                        break;
                    }
                }
            }
            break;
        }
        case ALLIANCE:
        {
            // Gestion des UNIT_NPC_FLAG_QUESTGIVER et UNIT_NPC_FLAG_GOSSIP des PNJ "collector"
            if (objectiveReached)
                break;

            for (int i = 0; i < 10; i++)
            {
                if (pQuest->ReqItemId[0] == AllianceObjectives[i].itemID)
                {
                    if (var >= AllianceObjectives[i].reqCount)
                    {
                        strcat(itemName, AllianceObjectives[i].itemName);
                        objectiveReached = true;
                        break;
                    }
                }
            }
            break;
        }
        default:
            break;
    }

    if (objectiveReached)
    {
        if (pQuestGiver->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            pQuestGiver->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

        if (pQuestGiver->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            pQuestGiver->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        char sMessage[200] = "";
        sprintf(sMessage, "Felicitations %s ! La recolte de %s est enfin terminee !", pPlayer->GetName(), itemName);
        pQuestGiver->MonsterSay(sMessage, 0, 0);
        pQuestGiver->HandleEmote(EMOTE_ONESHOT_CHEER);
    }
    return true;
}


/*###
 ## npc_Geologist_Larksbane
 ###*/

/*UPDATE `gameobject_template` SET `size` = 1.5, `data2` = 39321600, `type` = 1 WHERE `entry` = 210342;
 UPDATE `gameobject_template` SET data2 = 39321600 WHERE `entry` = 180514;
 DELETE FROM `gameobject` WHERE `id` IN (180514, 210342);
 UPDATE `creature_template` SET `ScriptName` = 'npc_Geologist_Larksbane' WHERE `entry` = 15183;*/

enum
{
    GO_GLYPHED_CRYSTAL      = 180514,
    GO_GLYPHED_CRYSTAL_BIG  = 210342
};

struct npc_Geologist_LarksbaneAI : public ScriptedAI
{
    npc_Geologist_LarksbaneAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    std::list<uint64> lCrystalGUIDs;
    uint32 uiNextActionTimer;
    uint32 uiCurrAction;

    void Reset()
    {
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        lCrystalGUIDs.clear();
        uiCurrAction = 0;
        uiNextActionTimer = 0;
    }

    void QuestCompleted(Player* pPlayer, Quest const* pQuest)
    {
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        if (GameObject* pGo = m_creature->SummonGameObject(GO_GLYPHED_CRYSTAL, -6826.51f, 809.082f, 51.8577f, 0.259445f))
            lCrystalGUIDs.push_back(pGo->GetGUID());
        if (GameObject* pGo = m_creature->SummonGameObject(GO_GLYPHED_CRYSTAL, -6827.54f, 806.711f, 51.9809f, 2.2241f))
            lCrystalGUIDs.push_back(pGo->GetGUID());
        if (GameObject* pGo = m_creature->SummonGameObject(GO_GLYPHED_CRYSTAL_BIG, -6825.31f, 805.146f, 51.9435f, -1.255528f))
            lCrystalGUIDs.push_back(pGo->GetGUID());

        uiCurrAction = 1;
        uiNextActionTimer = 4000;
    }

    void Larksbane_DoAction()
    {
        switch (uiCurrAction)
        {
            case 1:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(77));
                uiNextActionTimer = 4000;
                break;
            }
            case 2:
            {
                for (std::list<uint64>::iterator it = lCrystalGUIDs.begin(); it != lCrystalGUIDs.end(); ++it)
                {
                    if (GameObject* pCrystal = m_creature->GetMap()->GetGameObject(*it))
                        pCrystal->Use(m_creature);
                }
                uiNextActionTimer = 5000;
                break;
            }
            case 3:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(78));
                uiNextActionTimer = 7000;
                break;
            }
            case 4:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(79));
                uiNextActionTimer = 11000;
                break;
            }
            case 5:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(80));
                uiNextActionTimer = 9000;
                break;
            }
            case 6:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(81));
                uiNextActionTimer = 11000;
                break;
            }
            case 7:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(82));
                uiNextActionTimer = 11000;
                break;
            }
            case 8:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                m_creature->MonsterSay(NOST_TEXT(83));
                uiNextActionTimer = 9000;
                break;
            }
            case 9:
            {
                m_creature->MonsterTextEmote(NOST_TEXT(84), NULL, false);
                uiNextActionTimer = 3000;
                break;
            }
            case 10:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(85));
                uiNextActionTimer = 4000;
                break;
            }
            case 11:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(86));
                uiNextActionTimer = 12000;
                break;
            }
            case 12:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                m_creature->MonsterSay(NOST_TEXT(87));
                uiNextActionTimer = 9000;
                break;
            }
            case 13:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(88));
                uiNextActionTimer = 9000;
                break;
            }
            case 14:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(89));
                uiNextActionTimer = 12000;
                break;
            }
            case 15:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(90));
                uiNextActionTimer = 12000;
                break;
            }
            case 16:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(91));
                uiNextActionTimer = 12000;
                break;
            }
            case 17:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(92));
                uiNextActionTimer = 12000;
                break;
            }
            case 18:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(93));
                uiNextActionTimer = 12000;
                break;
            }
            case 19:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(94));
                uiNextActionTimer = 12000;
                break;
            }
            case 20:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(95));
                uiNextActionTimer = 9000;
                break;
            }
            case 21:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(96));
                uiNextActionTimer = 3000;
                break;
            }
            case 22:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(97));
                uiNextActionTimer = 12000;
                break;
            }
            case 23:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(98));
                uiNextActionTimer = 9000;
                break;
            }
            case 24:
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_TALK);
                m_creature->MonsterSay(NOST_TEXT(99));
                uiNextActionTimer = 3000;
                break;
            }
            case 25:
            {
                m_creature->MonsterTextEmote(NOST_TEXT(100), NULL, false);
                uiNextActionTimer = 4000;
                break;
            }
            case 26:
            {
                if (Creature* Crea = m_creature->FindNearestCreature(15180, 50.0f))    // Baristolth of the Shifting Sands
                    m_creature->MonsterSay(NOST_TEXT(101));
                uiNextActionTimer = 5000;
                break;
            }
            case 27:
            {
                for (std::list<uint64>::iterator it = lCrystalGUIDs.begin(); it != lCrystalGUIDs.end(); ++it)
                {
                    if (GameObject* pCrystal = m_creature->GetMap()->GetGameObject(*it))
                        pCrystal->Delete();
                }
                lCrystalGUIDs.clear();
                uiNextActionTimer = 5000;
                break;
            }
            case 28:
            {
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                uiCurrAction = 0;
                uiNextActionTimer = 0;
                return;
            }
            default:
            {
                uiNextActionTimer = 4000;
                break;
            }
        }
        ++uiCurrAction;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (uiCurrAction)
        {
            if (uiNextActionTimer < uiDiff)
                Larksbane_DoAction();
            else
                uiNextActionTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_Geologist_Larksbane(Creature* pCreature)
{
    return new npc_Geologist_LarksbaneAI(pCreature);
}

bool QuestComplete_npc_Geologist_Larksbane(Player* pPlayer, Creature* pQuestGiver, Quest const* pQuest)
{
    if (pQuest->GetQuestId() != 8315) // The Calling
        return false;

    if (npc_Geologist_LarksbaneAI* pLark = dynamic_cast<npc_Geologist_LarksbaneAI*>(pQuestGiver->AI()))
        pLark->QuestCompleted(pPlayer, pQuest);
    return true;
}

/*###
 ## npc_Emissary_Romankhan
 ###*/

/*
 UPDATE `creature_template` SET `minmana` = 432240, `maxmana` = 434240, `armor` = 3769, `speed_walk` = 1.24, `speed_run` = 1.24, `baseattacktime` = 1280,
 `resistance1` = 0, `mingold` = 4031, `maxgold` = 4031, `mechanic_immune_mask` = 650854367, `MovementType` = 1,
 `ScriptName` = 'npc_Emissary_Romankhan' WHERE `entry` = 14862;
 */

enum
{
    SPELL_WILT                  = 23772,
    SPELL_SUFFERING_OF_SANITY   = 23773,
    SPELL_SYSTEM_SHOCK          = 23774
};

struct npc_Emissary_RomankhanAI : public ScriptedAI
{
    npc_Emissary_RomankhanAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        pCreature->SetVisibility(VISIBILITY_OFF);

        OverlordCount = 0;
        if (Creature* add = pCreature->SummonCreature(15288, -7233.39f, 906.415f, -1.76649f, 1.81259f, TEMPSUMMON_DEAD_DESPAWN, 0))   // Aluntir
            add->JoinCreatureGroup(pCreature, 0, 0, OPTION_RESPAWN_TOGETHER);
        if (Creature* add = pCreature->SummonCreature(15286, -7212.16f, 911.711f, -1.76649f, 2.58543f, TEMPSUMMON_DEAD_DESPAWN, 0))   // Xil'xix
            add->JoinCreatureGroup(pCreature, 0, 0, OPTION_RESPAWN_TOGETHER);
        if (Creature* add = pCreature->SummonCreature(15290, -7210.3f, 895.014f, -1.76649f, 0.544185f, TEMPSUMMON_DEAD_DESPAWN, 0))   // Arakis
            add->JoinCreatureGroup(pCreature, 0, 0, OPTION_RESPAWN_TOGETHER);
        Reset();
    }

    int OverlordCount;
    uint32 m_uiWiltTimer;
    uint32 m_uiSchockTimer;
    uint32 m_uiSanityTimer;
    uint32 m_uiCheckPlayerTimer;
    uint64 PlayerGuids[60];

    bool m_bNeedCheck;

    void Reset()
    {
        m_uiWiltTimer = urand(3000, 5000);
        m_uiSchockTimer = urand(8000, 12000);
        m_uiSanityTimer = 1;
        m_uiCheckPlayerTimer = 1000;
        m_bNeedCheck = false;
        m_creature->AllowManaRegen(false);
        m_creature->SetPower(POWER_MANA, 0);

        for (int i = 0; i < 60; i++)
            PlayerGuids[i] = 0;
    }

    void SummonedCreatureJustDied(Creature* unit)
    {
        ++OverlordCount;
        if (OverlordCount >= 3)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_ON);
        }
    }

    void Aggro(Unit* pWho)
    {
        m_creature->AllowManaRegen(true);
    }

    inline float GetManaPercent()
    {
        return (((float)m_creature->GetPower(POWER_MANA) / (float)m_creature->GetMaxPower(POWER_MANA)) * 100);
    }

    void SpellHitTarget(Unit* target, const SpellEntry* pSpell)
    {
        if (!target || !target->IsPlayer())
            return;

        if (pSpell->Id == SPELL_WILT || pSpell->Id == SPELL_SUFFERING_OF_SANITY || pSpell->Id == SPELL_SYSTEM_SHOCK)
        {
            for (int i = 0; i < 60; i++)
                if (PlayerGuids[i] == target->GetGUID())
                    return;

            for (int i = 0; i < 60; i++)
            {
                if (PlayerGuids[i] == 0)
                {
                    PlayerGuids[i] = target->GetGUID();
                    break;
                }
            }
            m_bNeedCheck = true;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSchockTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (pTarget->GetTypeId() == TYPEID_PLAYER)
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_SYSTEM_SHOCK) == CAST_OK)
                        m_uiSchockTimer = urand(6000, 10000);
                }
                else
                    m_uiSchockTimer = 1000;
            }
        }
        else
            m_uiSchockTimer -= uiDiff;

        if (m_uiWiltTimer < uiDiff)
        {
            for (int i = 0; i < 60; i++)
                PlayerGuids[i] = 0;
            if (DoCastSpellIfCan(m_creature, SPELL_WILT) == CAST_OK)
                m_uiWiltTimer = urand(3000, 5000);
        }
        else
            m_uiWiltTimer -= uiDiff;

        if (GetManaPercent() == 100.0f)
        {
            if (m_uiSanityTimer < uiDiff)
            {
                for (int i = 0; i < 60; i++)
                    PlayerGuids[i] = 0;
                if (DoCastSpellIfCan(m_creature, SPELL_SUFFERING_OF_SANITY) == CAST_OK)
                    m_uiSanityTimer = 1000;
            }
            else
                m_uiSanityTimer -= uiDiff;
        }
        else if (m_uiSanityTimer != 1)
            m_uiSanityTimer = 1;

        DoMeleeAttackIfReady();

        if (!m_bNeedCheck)
            return;

        if (m_uiCheckPlayerTimer < uiDiff)
        {
            for (int i = 0; i < 60; i++)
            {
                if (PlayerGuids[i] == 0)
                    continue;

                if (Unit* pTarget = m_creature->GetMap()->GetUnit(PlayerGuids[i]))
                {
                    pTarget->SetInCombatWith(m_creature);
                    if (pTarget->isDead())
                    {
                        // + 2% MP at each death
                        float currMana = m_creature->GetPower(POWER_MANA);
                        float MaxMana = m_creature->GetMaxPower(POWER_MANA);
                        m_creature->SetPower(POWER_MANA, (currMana + MaxMana * 0.02f) < MaxMana ? (currMana + MaxMana * 0.02f) : MaxMana);

                        PlayerGuids[i] = 0;
                    }
                }
            }
            m_bNeedCheck = false;
            m_uiCheckPlayerTimer = 1000;
        }
        else
            m_uiCheckPlayerTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_Emissary_Romankhan(Creature* pCreature)
{
    return new npc_Emissary_RomankhanAI(pCreature);
}

/*########################
 ## npc_Krug_SkullSplit ##
 ########################*/

#define GOSSIP_ITEM_KRUG_SKULLSPLIT_1 "Continue."
#define GOSSIP_ITEM_KRUG_SKULLSPLIT_2 "Very well, let's go!"

/* Hunterkiller */
#define HUNTERKILLER_SPAWN_POS_X -7765.0f
#define HUNTERKILLER_SPAWN_POS_Y 536.0f
#define HUNTERKILLER_SPAWN_POS_Z -43.0f

#define HUNTERKILLER_DEST_POS_X -7549.78f
#define HUNTERKILLER_DEST_POS_Y 711.901f
#define HUNTERKILLER_DEST_POS_Z -16.4527f

struct HunterMove
{
    float X;
    float Y;
    float Z;
    float O;
};

#define HUNTERKILLER_WAYPOINTS_NUMBER 16
static HunterMove HunterKillerWaypoint[HUNTERKILLER_WAYPOINTS_NUMBER] =
{
    { -7769.14f, 549.365f, -44.1111f, 0.868761f},
    { -7762.88f, 564.709f, -45.9125f, 1.17899f},
    { -7749.28f, 589.14f, -47.1617f, 1.05334f},
    { -7748.5f, 622.853f, -45.2946f, 0.982653f},
    { -7730.37f, 643.343f, -46.7866f, 0.456442f},
    { -7694.24f, 660.321f, -51.0377f, 0.441519f},
    { -7674.25f, 671.264f, -50.4592f, 0.0841609f},
    { -7655.01f, 671.601f, -47.9161f, 1.13424f},
    { -7634.07f, 672.497f, -47.8617f, 0.0857299f},
    { -7603.06f, 667.321f, -48.6429f, 6.0249f},
    { -7571.59f, 665.263f, -48.3899f, 0.0480175f},
    { -7562.58f, 687.328f, -49.9864f, 1.36749f},
    { -7559.18f, 689.958f, -40.8654f, 1.44927f},
    { -7555.3f, 692.953f, -30.7562f, 0.671711f},
    { -7548.27f, 697.037f, -25.6632f, 1.09582f},
    { -7547.07f, 706.949f, -17.7001f, 4.68419f},
};

/* Shai */
#define SHAI_SPAWN_POS_X -7556.600098f
#define SHAI_SPAWN_POS_Y 749.007019f
#define SHAI_SPAWN_POS_Z -17.578800f

#define SHAI_DEST_POS_X -7553.46f
#define SHAI_DEST_POS_Y 720.924f
#define SHAI_DEST_POS_Z -16.715f

/* Merok */
#define MEROK_SPAWN_POS_X -7537.149902f
#define MEROK_SPAWN_POS_Y 731.184021f
#define MEROK_SPAWN_POS_Z -16.418100f

#define MEROK_DEST_POS_X -7542.45f
#define MEROK_DEST_POS_Y 720.155f
#define MEROK_DEST_POS_Z -15.6801f

enum
{
    QUEST_FIELD_DUTY = 8731,
    QUEST_FIELD_DUTY_PAPERS = 8732,

    NPC_HUNTERKILLER = 15620,
    NPC_KRUG_SKULLSPLIT = 15612,
    NPC_MEROK_LONGSTRIDE = 15613,
    NPC_SHADOW_PRIESTESS_SHAI = 15615,
    NPC_ORGRIMMAR_LEGION_GRUNT = 15616,

    /* Emotes */
    SAY_LINE_1 = -1780131, //Spawn
    SAY_LINE_2 = -1780132,
    SAY_LINE_3 = -1780133,
    SAY_LINE_4 = -1780134,
    SAY_LINE_5 = -1780135,
    SAY_LINE_6 = -1780136,
    SAY_LINE_7 = -1780137,
    SAY_LINE_8 = -1780138,
    SAY_LINE_9 = -1780139,

    /* Hunterkiller */
    SPELL_THUNDERCLAP = 15588,
    SPELL_CHARGE = 25821,
    SPELL_CLEAVE = 40504,
    SPELL_FEAR = 25815,

    /* Merok */
    SPELL_HEALING_WAVE = 15982,

    /* Shai */
    SPELL_FLASH_HEAL = 17138
};

struct mob_HiveRegal_HunterKillerAI : public ScriptedAI
{
    mob_HiveRegal_HunterKillerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiThunderClapTimer;
    uint32 m_uiChargeTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiFearTimer;

    void Reset()
    {
        m_uiThunderClapTimer = 17000;
        m_uiChargeTimer = urand(15000, 20000);
        m_uiCleaveTimer = urand(4000, 8000);
        m_uiFearTimer = urand(5000, 10000);
        // m_creature->MonsterTextEmote("Reset", NULL); // pour debug
    }

    Unit* GetVictimInRangePlayerOnly(float min, float max)
    {
        ThreatList const& tList = m_creature->getThreatManager().getThreatList();
        for (ThreatList::const_iterator itr = tList.begin(); itr != tList.end(); ++itr)
        {
            if (ObjectGuid uiTargetGuid = (*itr)->getUnitGuid())
            {
                if (Unit* pTarget = m_creature->GetMap()->GetUnit(uiTargetGuid))
                {
                    if (pTarget->GetTypeId() == TYPEID_PLAYER && m_creature->IsInRange(pTarget, min, max))
                        return pTarget;
                }
            }
        }
        return NULL;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->IsNonMeleeSpellCasted(false))
            return;

        // THUNDERCLAP
        if (m_uiThunderClapTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_THUNDERCLAP);
            m_uiThunderClapTimer = 20000;
        }
        else
            m_uiThunderClapTimer -= uiDiff;

        // CHARGE
        if (m_uiChargeTimer <= uiDiff)
        {
            if (Unit* pTarget = GetVictimInRangePlayerOnly(5.0f, 30.0f))
            {
                DoCastSpellIfCan(pTarget, SPELL_CHARGE);
                m_uiChargeTimer = urand(30000, 35000);
            }
        }
        else
            m_uiChargeTimer -= uiDiff;

        // CLEAVE
        if (m_uiCleaveTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
            m_uiCleaveTimer = urand(5000, 12000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // FEAR
        if (m_uiFearTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FEAR);
            m_uiFearTimer = urand(58000, 63000);
        }
        else
            m_uiFearTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/* TODO: Fixer les lanceurs de hache au sol */

CreatureAI* GetAI_mob_HiveRegal_HunterKiller(Creature* pCreature)
{
    return new mob_HiveRegal_HunterKillerAI(pCreature);
}


typedef enum
{
    EVENT_NOT_STARTED,
    EVENT_STARTED,
    EVENT_COMPLETE
} FieldDutyPaperEventStatus;


struct npc_Krug_SkullSplitAI : public ScriptedAI
{
    /* Written by Ivina & Malkins < Nostalrius > */
    npc_Krug_SkullSplitAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        ResetEvent();
    }

    FieldDutyPaperEventStatus eEventStatus;
    uint32 m_uiEventResetTimer;
    uint32 m_uiSpeachNum;
    uint32 m_uiGruntSpeachTimer;
    uint32 m_uiMoveTimer;
    uint32 InitTimer;
    uint32 m_uiSpeachTimer;
    bool m_bAlreadyMoved;
    bool m_bIsDoingSpeach;
    bool m_bGruntSpeech;
    ObjectGuid m_uiShaiGUID;
    ObjectGuid m_uiMerokGUID;
    ObjectGuid m_uiHunterKillerGUID;
    int waypoint;

    void Reset()
    {
    }

    /* Custom methods */

    FieldDutyPaperEventStatus GetEventStatus()
    {
        return eEventStatus;
    }

    void ResetEvent()
    {
        m_creature->MonsterTextEmote("reset", NULL); // pour debug
        eEventStatus = EVENT_NOT_STARTED;
        if (Creature* pHunterKiller = m_creature->GetMap()->GetCreature(m_uiHunterKillerGUID))
        {
            pHunterKiller->ForcedDespawn();
            pHunterKiller->AddObjectToRemoveList();
        }
        m_uiSpeachTimer = 0;
        m_uiSpeachNum = 0;
        m_uiHunterKillerGUID.Clear();
        m_uiEventResetTimer = 120000;
        m_bAlreadyMoved = true;
        m_bIsDoingSpeach = false;
        m_bGruntSpeech = false;
        m_uiMoveTimer = 10000;
        ResetOtherNPCsPosition();
        InitTimer = 2000;
        waypoint = 0;
    }

    void StartEvent()
    {
        if (eEventStatus == EVENT_NOT_STARTED)
        {
            DoScriptText(SAY_LINE_1, m_creature);

            m_uiGruntSpeachTimer = 3000;
            m_uiSpeachTimer = 10000;
            m_uiSpeachNum = 0;
            m_bIsDoingSpeach = true;
            m_bGruntSpeech = false;

            Creature* pHunterKiller = m_creature->SummonCreature(NPC_HUNTERKILLER,
                                      HUNTERKILLER_SPAWN_POS_X, HUNTERKILLER_SPAWN_POS_Y, HUNTERKILLER_SPAWN_POS_Z, 0.8f,
                                      TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 150000);
            if (pHunterKiller)
            {
                eEventStatus = EVENT_STARTED;
                m_bAlreadyMoved = false;
                m_uiHunterKillerGUID = pHunterKiller->GetObjectGuid();
                InitOtherNPCsGuids();
                pHunterKiller->setFaction(35);
            }
        }
    }

    void CompleteEvent()
    {
        m_uiEventResetTimer = 30000;
        eEventStatus = EVENT_COMPLETE;
        m_bIsDoingSpeach = false;
        m_bGruntSpeech = true;
    }

    void InitOtherNPCsGuids()
    {
        m_uiMerokGUID = 0;
        m_uiShaiGUID = 0;

        if (Creature* pMerok = m_creature->FindNearestCreature(15613, 100.0f, true))
            m_uiMerokGUID = pMerok->GetObjectGuid();

        if (Creature* pShai = m_creature->FindNearestCreature(15615, 100.0f, true))
            m_uiShaiGUID = pShai->GetObjectGuid();
    }

    void ResetOtherNPCsPosition()
    {
        if (Creature* pMerok = m_creature->GetMap()->GetCreature(m_uiMerokGUID))
            pMerok->GetMotionMaster()->MovePoint(0, MEROK_SPAWN_POS_X, MEROK_SPAWN_POS_Y, MEROK_SPAWN_POS_Z);

        if (Creature* pShai = m_creature->GetMap()->GetCreature(m_uiShaiGUID))
            pShai->GetMotionMaster()->MovePoint(0, SHAI_SPAWN_POS_X, SHAI_SPAWN_POS_Y, SHAI_SPAWN_POS_Z);
    }

    /* Standart AI methods */
    void SummonedCreatureJustDied(Creature* pSummoned)
    {

        if (pSummoned->GetObjectGuid() == m_uiHunterKillerGUID)
        {
            m_creature->MonsterTextEmote("SumCreaJustDied", NULL); // pour debug
            CompleteEvent();
        }
    }

    void SummonedCreatureDespawn(Creature* pSummoned)
    {
        if (pSummoned->GetObjectGuid() == m_uiHunterKillerGUID)
        {
            m_creature->MonsterTextEmote("SumCreaDespawn", NULL); // pour debug
            ResetEvent();
        }
    }

    void JustDied(Unit* pKiller)
    {
        m_creature->MonsterTextEmote("JustDied", NULL); // pour debug
        ResetEvent();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        /* Event complete state is lasting 30 sec then event is reset */
        if (eEventStatus == EVENT_COMPLETE)
        {
            if (m_uiEventResetTimer <= uiDiff)
            {
                m_creature->MonsterTextEmote("CompleteEnd", NULL); // pour debug
                ResetEvent();
            }
            else
                m_uiEventResetTimer -= uiDiff;
        }

        /* Speech */
        if (m_bIsDoingSpeach)
        {
            if (m_uiSpeachTimer < uiDiff)
            {
                switch (m_uiSpeachNum)
                {
                    case 0:
                        // 8 seconds till next line
                        DoScriptText(SAY_LINE_2, m_creature);
                        m_uiSpeachTimer = 10000;
                        ++m_uiSpeachNum;
                        break;
                    case 1:
                        // 8 seconds till next line
                        DoScriptText(SAY_LINE_3, m_creature);
                        m_uiSpeachTimer = 10000;
                        ++m_uiSpeachNum;
                        break;
                    case 2:
                        // 8 seconds till next line
                        DoScriptText(SAY_LINE_4, m_creature);
                        m_uiSpeachTimer = 10000;
                        ++m_uiSpeachNum;
                        break;
                    case 3:
                        // 6,5 seconds till next line
                        DoScriptText(SAY_LINE_5, m_creature);
                        m_uiSpeachTimer = 6500;
                        ++m_uiSpeachNum;
                        break;
                    case 4:
                        // 2 seconds till next line
                        DoScriptText(SAY_LINE_6, m_creature);
                        m_uiSpeachTimer = 1000;
                        ++m_uiSpeachNum;
                        break;
                    case 5:
                        if (Creature* pMerok = m_creature->GetMap()->GetCreature(m_uiMerokGUID))
                            pMerok->GetMotionMaster()->MovePoint(0, MEROK_DEST_POS_X, MEROK_DEST_POS_Y, MEROK_DEST_POS_Z);

                        if (Creature* pShai = m_creature->GetMap()->GetCreature(m_uiShaiGUID))
                            pShai->GetMotionMaster()->MovePoint(0, SHAI_DEST_POS_X, SHAI_DEST_POS_Y, SHAI_DEST_POS_Z);
                        // 7 seconds till next line
                        DoScriptText(SAY_LINE_7, m_creature);
                        m_uiSpeachTimer = 6000;
                        ++m_uiSpeachNum;
                        break;
                    case 6:
                        DoScriptText(SAY_LINE_8, m_creature);
                        ++m_uiSpeachNum;
                        break;
                }
            }
            else
                m_uiSpeachTimer -= uiDiff;
        }

        /* Grunt */
        if (m_bGruntSpeech)
        {
            if (m_uiGruntSpeachTimer < uiDiff)
            {
                std::list<Creature*> gruntList;
                m_creature->GetCreatureListWithEntryInGrid(gruntList, NPC_ORGRIMMAR_LEGION_GRUNT, 100.0f);

                if (!gruntList.empty())
                {
                    for (std::list<Creature*>::iterator itr = gruntList.begin(); itr != gruntList.end(); ++itr)
                    {
                        if ((*itr)->isAlive())
                            DoScriptText(SAY_LINE_9, (*itr));
                    }
                }
                m_bGruntSpeech = false;
            }
            else
                m_uiGruntSpeachTimer -= uiDiff;
        }

        /* Move */
        if ((eEventStatus == EVENT_STARTED) && (waypoint <= HUNTERKILLER_WAYPOINTS_NUMBER))
        {
            if (m_uiMoveTimer < uiDiff)
            {
                if (Creature* pHunterKiller = m_creature->GetMap()->GetCreature(m_uiHunterKillerGUID))
                {
                    if (waypoint == HUNTERKILLER_WAYPOINTS_NUMBER)
                    {
                        pHunterKiller->setFaction(14);
                        pHunterKiller->AI()->AttackStart(m_creature);
                    }
                    else
                    {
                        float X = 0.0f;
                        float Y = 0.0f;
                        pHunterKiller->GetMotionMaster()->MovePoint(0, HunterKillerWaypoint[waypoint].X, HunterKillerWaypoint[waypoint].Y, HunterKillerWaypoint[waypoint].Z);
                        X = pHunterKiller->GetPositionX() - HunterKillerWaypoint[waypoint].X;
                        Y = pHunterKiller->GetPositionY() - HunterKillerWaypoint[waypoint].Y;
                        m_uiMoveTimer = sqrt((X * X) + (Y * Y)) / (m_creature->GetSpeed(MOVE_WALK) * 0.003f);
                    }
                    waypoint++;
                }
            }
            else
                m_uiMoveTimer -= uiDiff;
        }

        /* Clean unwanted states */
        if (Creature* pHunterKiller = m_creature->GetMap()->GetCreature(m_uiHunterKillerGUID))
        {
            if (eEventStatus == EVENT_NOT_STARTED)
            {
                pHunterKiller->ForcedDespawn();
                pHunterKiller->AddObjectToRemoveList();
            }
        }
        else
        {
            if (eEventStatus == EVENT_STARTED)
            {
                m_creature->MonsterTextEmote("Clean2", NULL); // pour debug
                ResetEvent();
            }
        }

        /* Start of combat script */
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_npc_Krug_SkullSplit(Creature* pCreature)
{
    return new npc_Krug_SkullSplitAI(pCreature);
}


bool GossipHello_npc_Krug_SkullSplit(Player* pPlayer, Creature* pCreature)
{
    /* TO DO : la tous les SEND_GOSSIP_MENU renvoient le menu par defaut,
       or il faut mettre le gossip adapte a chaque cas */
    FieldDutyPaperEventStatus eEventStatus = EVENT_NOT_STARTED;

    if (npc_Krug_SkullSplitAI* pKrugSkullSplitAI = dynamic_cast<npc_Krug_SkullSplitAI*>(pCreature->AI()))
        eEventStatus = pKrugSkullSplitAI->GetEventStatus();

    if ((pPlayer->GetQuestStatus(QUEST_FIELD_DUTY) == QUEST_STATUS_INCOMPLETE)
            && (eEventStatus == EVENT_NOT_STARTED))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KRUG_SKULLSPLIT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }
    else if ((pPlayer->GetQuestStatus(QUEST_FIELD_DUTY) == QUEST_STATUS_INCOMPLETE)
             && (eEventStatus == EVENT_COMPLETE))
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}


bool GossipSelect_npc_Krug_SkullSplit(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KRUG_SKULLSPLIT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        if (npc_Krug_SkullSplitAI* pKrugSkullSplitAI = dynamic_cast<npc_Krug_SkullSplitAI*>(pCreature->AI()))
            pKrugSkullSplitAI->StartEvent();
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

struct npc_MerokAI : public ScriptedAI
{
    npc_MerokAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiHealingWave;

    void Reset()
    {
        m_uiHealingWave = 12000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->IsNonMeleeSpellCasted(false))
            return;

        // HEALING WAVE
        if (m_uiHealingWave <= uiDiff)
        {
            Unit* pUnit = DoSelectLowestHpFriendly(60.0f, 1);
            if (!pUnit)
                return;

            if (DoCastSpellIfCan(pUnit, SPELL_HEALING_WAVE) == CAST_OK)
                m_uiHealingWave = 12000;
        }
        else
            m_uiHealingWave -= uiDiff;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_npc_Merok(Creature* pCreature)
{
    return new npc_MerokAI(pCreature);
}


struct npc_ShaiAI : public ScriptedAI
{
    npc_ShaiAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFlashHeal;

    void Reset()
    {
        m_uiFlashHeal = 12000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->IsNonMeleeSpellCasted(false))
            return;

        // FLASH HEAL
        if (m_uiFlashHeal <= uiDiff)
        {
            Unit* pUnit = DoSelectLowestHpFriendly(60.0f, 1);
            if (!pUnit)
                return;

            if (DoCastSpellIfCan(pUnit, SPELL_FLASH_HEAL) == CAST_OK)
                m_uiFlashHeal = 12000;
        }
        else
            m_uiFlashHeal -= uiDiff;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_npc_Shai(Creature* pCreature)
{
    return new npc_ShaiAI(pCreature);
}


//=====================------------------------------------
//Alita <Nostalrius>
// PNJ tp AQ20, AQ40.
//====================
enum
{
    CHRIS = 56000 //notre pnj de tp.
};
bool GossipHello_npc_chris_starlightshadow(Player* pPlayer, Creature* pCreature)
{

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Guide me to the Ruins of Ahn'Qiraj", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Guide me to the Temple of Ahn'Qiraj", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_chris_starlightshadow(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (pPlayer->TeleportTo(509, -8429.74f, 1512.14f, 31.9074f, 2.56f))
            if (!pPlayer->isAlive())
            {
                pPlayer->ResurrectPlayer(0.5f, false);
                pPlayer->SpawnCorpseBones();
            }
    }
    else if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (pPlayer->TeleportTo(531, -8231.330078f, 2010.6f, 129.33051f, 0.95f))
            if (!pPlayer->isAlive())
            {
                pPlayer->ResurrectPlayer(0.5f, false);
                pPlayer->SpawnCorpseBones();
            }
    }

    return true;
}

/** EVENT NOSTALRIUS VAM ,SAND PRINCE */

enum
{
    SPELL_CHARGE_VAM     = 26561,
    SPELL_IMPALE         = 28783,
    SPELL_ENRAGE         = 34624,
};

struct boss_vamAI : public ScriptedAI
{
    boss_vamAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 Charge_Timer;
    uint32 KnockBack_Timer;
    uint32 Enrage_Timer;

    bool Enraged;

    void Reset()
    {
        Charge_Timer = urand(15000, 27000);
        KnockBack_Timer = urand(8000, 20000);
        Enrage_Timer = 240000;

        Enraged = false;
    }

    void Aggro(Unit *who)
    {
    }

    void JustDied(Unit* Killer)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Charge_Timer
        if (Charge_Timer < diff)
        {
            Charge_Timer = 10000;
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(target, SPELL_CHARGE_VAM) == CAST_OK)
                    Charge_Timer = urand(8000, 16000);
            }
        }
        else Charge_Timer -= diff;

        //KnockBack_Timer
        if (KnockBack_Timer < diff)
        {
            KnockBack_Timer = 15000;
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(target, SPELL_IMPALE) == CAST_OK)
                    KnockBack_Timer = urand(15000, 25000);
            }
        }
        else KnockBack_Timer -= diff;

        //Enrage_Timer
        if (!Enraged && Enrage_Timer < diff)
            Enraged = true;
        else if (Enraged)
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE, CAST_AURA_NOT_PRESENT);
        else
            Enrage_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_vamAI(Creature* pCreature)
{
    return new boss_vamAI(pCreature);
}

/*
 *
 */

void AddSC_silithus()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_highlord_demitrian";
    pNewScript->pGossipHello =  &GossipHello_npc_highlord_demitrian;
    pNewScript->pGossipSelect = &GossipSelect_npc_highlord_demitrian;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npcs_rutgar_and_frankal";
    pNewScript->pGossipHello =  &GossipHello_npcs_rutgar_and_frankal;
    pNewScript->pGossipSelect = &GossipSelect_npcs_rutgar_and_frankal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_pierre_vents";
    pNewScript->pGOGossipSelect =  &GossipSelect_go_pierre_vents;
    pNewScript->GOGetAI = &GetAIgo_pierre_vents;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_cenarion_scout_azenel";
    pNewScript->pGossipHello =  &GossipHello_npc_cenarion_scout_azenel;
    pNewScript->pGossipSelect = &GossipSelect_npc_cenarion_scout_azenel;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_prince_thunderaan";
    pNewScript->GetAI = &GetAI_npc_prince_thunderaan;
    pNewScript->RegisterSelf();

    // AQ WAR
    pNewScript = new Script;
    pNewScript->Name = "npc_colossus";
    pNewScript->GetAI = &GetAI_npc_colossus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_resonating_Crystal";
    pNewScript->GetAI = &GetAI_npc_resonating_Crystal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_AQwar_effort";
    pNewScript->pGossipHello = &GossipHello_npc_AQwar_effort;
    pNewScript->pGossipSelect = &GossipSelect_npc_AQwar_effort;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_AQwar_collector";
    pNewScript->pGossipHello = &GossipHello_npc_AQwar_collector;
    pNewScript->pQuestRewardedNPC = &QuestComplete_npc_AQwar_collector;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_Geologist_Larksbane";
    pNewScript->GetAI = &GetAI_npc_Geologist_Larksbane;
    pNewScript->pQuestRewardedNPC = &QuestComplete_npc_Geologist_Larksbane;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_Emissary_Romankhan";
    pNewScript->GetAI = &GetAI_npc_Emissary_Romankhan;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_Krug_SkullSplit";
    pNewScript->GetAI = &GetAI_npc_Krug_SkullSplit;
    pNewScript->pGossipHello = &GossipHello_npc_Krug_SkullSplit;
    pNewScript->pGossipSelect = &GossipSelect_npc_Krug_SkullSplit;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_HiveRegal_HunterKiller";
    pNewScript->GetAI = &GetAI_mob_HiveRegal_HunterKiller;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_Merok";
    pNewScript->GetAI = &GetAI_npc_Merok;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_Shai";
    pNewScript->GetAI = &GetAI_npc_Shai;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_chris_starlightshadow";
    pNewScript->pGossipHello =  &GossipHello_npc_chris_starlightshadow;
    pNewScript->pGossipSelect = &GossipSelect_npc_chris_starlightshadow;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_boss_vam";
    pNewScript->GetAI = &GetAI_boss_vamAI;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_solenor"; // npc_solenor_the_slayer
    pNewScript->GetAI = &GetAI_npc_solenor;
    pNewScript->pGossipHello =  &GossipHello_npc_solenor;
    pNewScript->pGossipSelect = &GossipSelect_npc_solenor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_creeping_doom";
    pNewScript->GetAI = &GetAI_npc_creeping_doom;
    pNewScript->RegisterSelf();
}
