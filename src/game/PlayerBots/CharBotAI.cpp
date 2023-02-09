#include "CharBotAI.h"
#include "Player.h"
#include "Log.h"
#include "MotionMaster.h"
#include "ObjectMgr.h"
#include "PlayerBotMgr.h"
#include "WorldPacket.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "Chat.h"
#include <random>
#include "Util.h"
#include "MoveSpline.h"


enum CharBotSpells
{
	PB_SPELL_FOOD = 1131,
	PB_SPELL_DRINK = 1137,
	PB_SPELL_AUTO_SHOT = 75,
	PB_SPELL_SHOOT_WAND = 5019,
	PB_SPELL_TAME_BEAST = 13481,

	PB_SPELL_SUMMON_IMP = 688,
	PB_SPELL_SUMMON_VOIDWALKER = 697,
	PB_SPELL_SUMMON_FELHUNTER = 691,
	PB_SPELL_SUMMON_SUCCUBUS = 712,

	PB_PET_WOLF = 565,
	PB_PET_CAT = 681,
	PB_PET_BEAR = 822,
	PB_PET_CRAB = 831,
	PB_PET_GORILLA = 1108,
	PB_PET_BIRD = 1109,
	PB_PET_BOAR = 1190,
	PB_PET_BAT = 1554,
	PB_PET_CROC = 1693,
	PB_PET_SPIDER = 1781,
	PB_PET_OWL = 1997,
	PB_PET_STRIDER = 2322,
	PB_PET_SCORPID = 3127,
	PB_PET_SERPENT = 3247,
	PB_PET_RAPTOR = 3254,
	PB_PET_TURTLE = 3461,
	PB_PET_HYENA = 4127,

	BB_ITEM_ARROW = 2512,
	BB_ITEM_BULLET = 2516,
};

#define PB_UPDATE_INTERVAL 1000
#define PB_MIN_FOLLOW_DIST 3.0f
#define PB_MAX_FOLLOW_DIST 6.0f
#define PB_MIN_FOLLOW_ANGLE 0.0f
#define PB_MAX_FOLLOW_ANGLE 6.0f

bool CharBotAI::OnSessionLoaded(PlayerBotEntry* entry, WorldSession* sess)
{
	sess->LoginPlayer(entry->playerGUID);
	return true;
}
void CharBotAI::FreeRandomizationMove()
{
	/// MOVEMENT AI
	if (!me->movespline->Finalized())
		return;
	float x, y, z = 0; // Where to go
	float r = 10;
	me->GetPosition(x, y, z);
	r = frand(0, 10);
	float angle = me->GetOrientation() + frand(-M_PI_F / 2, M_PI_F / 2);
	x += r * cos(angle);
	y += r * sin(angle);
	if (!me->GetMap()->GetWalkHitPosition(nullptr, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), x, y, z))
		return;
	me->Say("i will move...", LANG_UNIVERSAL);
	me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);


}

void CharBotAI::FollowLeaderMove(Player* pLeader)
{
	if (!pLeader)
		return;
	// Teleport to leader if too far away.
	if (!me->IsWithinDistInMap(pLeader, 100.0f))
	{
		if (!me->IsStopped())
			me->StopMoving();
		me->GetMotionMaster()->Clear();
		me->GetMotionMaster()->MoveIdle();
		char name[128] = {};
		strcpy(name, pLeader->GetName());
		ChatHandler(me).HandleGonameCommand(name);
		return;
	}
	if (!me->IsInCombat())
	{
		// Mount if leader is mounted.
		if (pLeader->IsMounted())
		{
			if (!me->IsMounted())
			{
				auto auraList = pLeader->GetAurasByType(SPELL_AURA_MOUNTED);
				if (!auraList.empty())
				{
					bool oldState = me->HasCheatOption(PLAYER_CHEAT_NO_CAST_TIME);
					me->SetCheatOption(PLAYER_CHEAT_NO_CAST_TIME, true);
					me->CastSpell(me, (*auraList.begin())->GetId(), true);
					me->SetCheatOption(PLAYER_CHEAT_NO_CAST_TIME, oldState);
				}
			}
		}
		else if (me->IsMounted())
		{
			me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
		}
	}
	if (me->IsBeingTeleportedFar())
		me->GetSession()->HandleMoveWorldportAckOpcode();
	if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
		me->GetMotionMaster()->MoveFollow(pLeader, urand(PB_MIN_FOLLOW_DIST, PB_MAX_FOLLOW_DIST), frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE));
	if (pLeader->IsTaxiFlying())
	{
		if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
			me->GetMotionMaster()->MoveIdle();
		return;
	}

}

void CharBotAI::UpdateAI(uint32 const diff)
{
	m_updateTimer.Update(diff);
	if (m_updateTimer.Passed())
		m_updateTimer.Reset(PB_UPDATE_INTERVAL);
	else
		return;

	if (!me->IsInWorld() || me->IsBeingTeleported())
		return;

	if (!m_initialized)
	{
		//AddToPlayerGroup();

		//if (m_role == ROLE_INVALID)
		//	AutoAssignRole();

		ResetSpellData();
		PopulateSpellData();
		AddAllSpellReagents();

		me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

		uint32 newzone, newarea;
		me->GetZoneAndAreaId(newzone, newarea);
		me->UpdateZone(newzone, newarea);

		m_initialized = true;
		return;
	}
	if (me->IsDead())
	{
		return;
	}

	if (me->GetGroupInvite())
	{
		//group = new Group;
		Player* inviter = sObjectMgr.GetPlayer(me->GetGroupInvite()->GetLeaderGuid());
		if (inviter)
		{
			m_leaderGuid = inviter->GetObjectGuid();
			WorldPacket p;
			uint32 roles_mask = 0;
			p << roles_mask;
			me->GetSession()->HandleGroupAcceptOpcode(p);
			me->Say("hello", LANG_UNIVERSAL);
			
		}
		
	}

	if (me->HasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL))
		return;
	

	if (me->GetTargetGuid() == me->GetObjectGuid())
		me->ClearTarget();

	Player* pLeader = GetPartyLeader();
	
	
	if (!me->IsInCombat() && !me->IsMounted())
	{
		
		UpdateOutOfCombatAI();

		if (m_isBuffing)
			return;

		if (me->IsNonMeleeSpellCasted())
			return;

		if (pLeader)
			m_randomMove = false;
		else
			m_randomMove = true;

	}

	Unit* pVictim = me->SelectRandomUnfriendlyTarget(nullptr, 30.0F, true, true);
	//if (!me->IsWithinLOSInMap(pVictim))
	//	return;
	//Unit* pVictim = me->SelectNearestTarget(30.0f);

	if (!pVictim || pVictim->IsDead() || pVictim->HasBreakableByDamageCrowdControlAura())
	{
		if (pVictim = SelectAttackTarget(pVictim))
		{
			AttackStart(pVictim);
			return;
		}
	}
	
	
	if (pVictim && !me->HasInArc(pVictim, 2 * M_PI_F / 3) && !me->IsMoving())
	{
		me->SetInFront(pVictim);
		me->SendMovementPacket(MSG_MOVE_SET_FACING, false);
	}
	
	if (!me->IsMoving())
	{
		if (!pVictim)
		{
			if (m_randomMove)
				FreeRandomizationMove();
			else
				if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
					me->GetMotionMaster()->MoveFollow(pLeader, urand(PB_MIN_FOLLOW_DIST, PB_MAX_FOLLOW_DIST), frand(PB_MIN_FOLLOW_ANGLE, PB_MAX_FOLLOW_ANGLE));
		}
		else
		{
			if (!me->HasUnitState(UNIT_STAT_MELEE_ATTACKING) &&
				(me->GetClass() == CLASS_ROGUE || me->GetClass() == CLASS_WARRIOR) &&
				IsValidHostileTarget(pVictim) &&
				AttackStart(pVictim))
				return;

			if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
				me->GetMotionMaster()->MoveChase(pVictim);
		}
	}
	
	if (me->IsInCombat())
		UpdateInCombatAI();
}


void CharBotAI::OnPlayerLogin()
{
	if (!m_initialized)
		me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
	m_randomMove = true;
	me->SetCheatGod(true);
}
void CharBotAI::SendFakePacket(uint16 opcode)
{
	switch (opcode)
	{
		case CMSG_LOOT_ROLL:
		{
			if (m_lootResponses.empty())
				return;

			auto loot = m_lootResponses.begin();
			WorldPacket data(CMSG_LOOT_ROLL);
			data << uint64((*loot).guid);
			data << uint32((*loot).slot);
			data << uint8(0); // pass
			m_lootResponses.erase(loot);
			me->GetSession()->HandleLootRoll(data);
			return;
		}
	}

	CombatBotBaseAI::SendFakePacket(opcode);
}

void CharBotAI::OnPacketReceived(WorldPacket const* packet)
{
	//printf("Bot received %s\n", LookupOpcodeName(packet->GetOpcode()));
	switch (packet->GetOpcode())
	{
		case SMSG_LOOT_START_ROLL:
		{
			uint64 guid = *((uint64*)(*packet).contents());
			uint32 slot = *(((uint32*)(*packet).contents()) + 2);
			m_lootResponses.emplace_back(LootResponseData(guid, slot));
			botEntry->m_pendingResponses.push_back(CMSG_LOOT_ROLL);
			return;
		}
	}

	CombatBotBaseAI::OnPacketReceived(packet);
}

void CharBotAI::AddToPlayerGroup()
{
	Player* pPlayer = ObjectAccessor::FindPlayer(m_leaderGuid);
	if (!pPlayer)
		return;

	Group* group = pPlayer->GetGroup();
	if (!group)
	{
		group = new Group;
		// new group: if can't add then delete
		if (!group->Create(pPlayer->GetObjectGuid(), pPlayer->GetName()))
		{
			delete group;
			return;
		}
		sObjectMgr.AddGroup(group);
	}
	if (group->GetMembersCount() >= MAX_GROUP_SIZE)
		group->ConvertToRaid();
	group->AddMember(me->GetObjectGuid(), me->GetName());
}

Player* CharBotAI::GetPartyLeader() const
{
    Group* pGroup = me->GetGroup();
    if (!pGroup)
        return nullptr;

    ObjectGuid leaderGuid = pGroup->GetLeaderGuid();
    if (leaderGuid == me->GetObjectGuid() && !me->InBattleGround())
        return nullptr;
	
	if (!m_leaderGuid)
		return nullptr;
    return ObjectAccessor::FindPlayerNotInWorld(m_leaderGuid);
}

void CharBotAI::RunAwayFromTarget(Unit* pTarget)
{
	if (Player* pLeader = GetPartyLeader())
	{
		if (pLeader->IsInWorld() &&
			pLeader->GetMap() == me->GetMap())
		{
			float const distance = me->GetDistance(pLeader);
			if (distance >= 15.0f && distance <= 30.0f &&
				pLeader->GetDistance(pTarget) >= 15.0f)
			{
				me->GetMotionMaster()->MoveIdle();
				me->MonsterMove(pLeader->GetPositionX(), pLeader->GetPositionY(), pLeader->GetPositionZ());
				return;
			}
		}
	}

	me->GetMotionMaster()->MoveDistance(pTarget, 15.0f);
}

bool CharBotAI::DrinkAndEat()
{
	return false;
}

bool CharBotAI::AttackStart(Unit* pVictim)
{
	m_isBuffing = false;

	if (me->IsMounted())
		me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

	if (me->Attack(pVictim, true))
	{

		m_randomMove = false;

		if ((me->GetClass() == CLASS_MAGE || me->GetClass() == CLASS_WARLOCK || me->GetClass() == CLASS_HUNTER ) &&
			me->GetPowerPercent(POWER_MANA) > 10.0f &&
			me->GetCombatDistance(pVictim) > 8.0f)
			me->SetCasterChaseDistance(36.0f);
		else if (me->GetClass() == CLASS_DRUID || me->GetClass() == CLASS_PALADIN || me->GetClass() == CLASS_PRIEST)
			me->SetCasterChaseDistance(40.0f);
		else if (me->HasDistanceCasterMovement())
			me->SetCasterChaseDistance(3.0f);
		me->GetMotionMaster()->MoveChase(pVictim, 3.0f, me->GetClass() == CLASS_ROGUE ? 3.0f : 0.0f);
		return true;
	}

	return false;
}

Unit* CharBotAI::SelectAttackTarget(Player* pLeader) const
{
	// Who is the leader attacking.
	if (Unit* pVictim = pLeader->GetVictim())
	{
		if (IsValidHostileTarget(pVictim))
			return pVictim;
	}

	// Who is attacking me.
	for (const auto pAttacker : me->GetAttackers())
	{
		if (IsValidHostileTarget(pAttacker))
			return pAttacker;
	}

	// Check if other group members are under attack.
	if (Unit* pPartyAttacker = SelectPartyAttackTarget())
		return pPartyAttacker;

	return nullptr;
}

Unit* CharBotAI::SelectAttackTarget(Unit* pExcept) const
{
	// 1. Check units we are currently in combat with.

	std::list<Unit*> targets;
	HostileReference* pReference = me->GetHostileRefManager().getFirst();

	while (pReference)
	{
		if (Unit* pTarget = pReference->getSourceUnit())
		{
			if (pTarget != pExcept &&
				IsValidHostileTarget(pTarget) &&
				me->IsWithinDist(pTarget, VISIBILITY_DISTANCE_NORMAL))
			{
				targets.push_back(pTarget);
			}
		}
		pReference = pReference->next();
	}

	if (!targets.empty())
	{
		targets.sort([this](Unit* pUnit1, const Unit* pUnit2)
		{
			return me->GetDistance(pUnit1) < me->GetDistance(pUnit2);
		});

		return *targets.begin();
	}

	// 2. Find enemy player in range.

	std::list<Player*> players;
	me->GetAlivePlayerListInRange(me, players, VISIBILITY_DISTANCE_NORMAL);
	float const maxAggroDistance = 50.0f;

	for (const auto& pTarget : players)
	{
		if (pTarget == pExcept)
			continue;

		if (!IsValidHostileTarget(pTarget))
			continue;


		// Aggro weak enemies from further away.
		uint32 const aggroDistance = me->GetHealth() > pTarget->GetHealth() ? maxAggroDistance : 20.0f;
		if (!me->IsWithinDist(pTarget, aggroDistance))
			continue;

		if (me->IsWithinLOSInMap(pTarget))
			return pTarget;
	}

	// 3. Check party attackers.

	if (Group* pGroup = me->GetGroup())
	{
		for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
		{
			if (Unit* pMember = itr->getSource())
			{
				if (pMember == me)
					continue;

				if (me->GetDistance(pMember) > 30.0f)
					continue;

				if (Unit* pAttacker = pMember->GetAttackerForHelper())
					if (IsValidHostileTarget(pAttacker) &&
						me->IsWithinDist(pAttacker, maxAggroDistance * 2.0f) &&
						me->IsWithinLOSInMap(pAttacker) &&
						pAttacker != pExcept)
						return pAttacker;
			}
		}
	}

	return nullptr;
}

Unit* CharBotAI::SelectPartyAttackTarget() const
{
	Group* pGroup = me->GetGroup();
	for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
	{
		if (Player* pMember = itr->getSource())
		{
			// We already checked self.
			if (pMember == me)
				continue;

			for (const auto pAttacker : pMember->GetAttackers())
			{
				if (IsValidHostileTarget(pAttacker) &&
					me->IsWithinDist(pAttacker, 50.0f))
					return pAttacker;
			}
		}
	}

	return nullptr;
}

void CharBotAI::UpdateInCombatAI()
{
	m_randomMove = false;

	uint32 SPELL_WATCH = 24314;
	if (me->HasAura(SPELL_WATCH))//zulgurub mandokir watch AI
	{
		HandlePartyBotPauseApplyHelper(me,2000);
	}

	if (me->GetClass() == CLASS_WARRIOR)
	{
		Unit* pVictim = me->GetVictim();

		// Defend party members.
		if (!pVictim || pVictim->GetVictim() == me)
		{
			if (pVictim = SelectPartyAttackTarget())
			{
				me->AttackStop(true);
				AttackStart(pVictim);
			}
		}

		// Taunt target if its attacking someone else.
		if (pVictim && pVictim->GetVictim() != me)
		{
			for (const auto& pSpellEntry : spellListTaunt)
			{
				if (CanTryToCastSpell(pVictim, pSpellEntry))
				{
					if (DoCastSpell(pVictim, pSpellEntry) == SPELL_CAST_OK)
					{
						me->Say((sPlayerBotMgr.GenerateBotSpeech("taunt").c_str()), 0);
						return;
					}
				}
			}
		}
	}

	switch (me->GetClass())
	{
	case CLASS_PALADIN:
		UpdateInCombatAI_Paladin();
		break;
	case CLASS_SHAMAN:
		UpdateInCombatAI_Shaman();
		break;
	case CLASS_HUNTER:
		UpdateInCombatAI_Hunter();
		break;
	case CLASS_MAGE:
		UpdateInCombatAI_Mage();
		break;
	case CLASS_PRIEST:
		UpdateInCombatAI_Priest();
		break;
	case CLASS_WARLOCK:
		UpdateInCombatAI_Warlock();
		break;
	case CLASS_WARRIOR:
		UpdateInCombatAI_Warrior();
		break;
	case CLASS_ROGUE:
		UpdateInCombatAI_Rogue();
		break;
	case CLASS_DRUID:
		UpdateInCombatAI_Druid();
		break;
	}
}

void CharBotAI::UpdateOutOfCombatAI()
{
	/*
	if (m_resurrectionSpell)
		if (Player* pTarget = SelectResurrectionTarget())
			if (CanTryToCastSpell(pTarget, m_resurrectionSpell))
			{
				me->SetSelectionGuid(pTarget->GetObjectGuid());
				if (DoCastSpell(pTarget, m_resurrectionSpell) == SPELL_CAST_OK)
				{
					sprintf(sMessage, "%s, %s", pTarget->GetName(), sPlayerBotMgr.GenerateBotSpeech("revive").c_str());
					me->Yell(sMessage, 0);
					sprintf(sMessage, "%s%s", sPlayerBotMgr.GenerateBotSpeech("revive-e").c_str(), pTarget->GetName());
					me->TextEmote(sMessage);
					return;
				}
			}
		*/

	switch (me->GetClass())
	{
	case CLASS_PALADIN:
		UpdateOutOfCombatAI_Paladin();
		break;
	case CLASS_SHAMAN:
		UpdateOutOfCombatAI_Shaman();
		break;
	case CLASS_HUNTER:
		UpdateOutOfCombatAI_Hunter();
		break;
	case CLASS_MAGE:
		UpdateOutOfCombatAI_Mage();
		break;
	case CLASS_PRIEST:
		UpdateOutOfCombatAI_Priest();
		break;
	case CLASS_WARLOCK:
		UpdateOutOfCombatAI_Warlock();
		break;
	case CLASS_WARRIOR:
		UpdateOutOfCombatAI_Warrior();
		break;
	case CLASS_ROGUE:
		UpdateOutOfCombatAI_Rogue();
		break;
	case CLASS_DRUID:
		UpdateOutOfCombatAI_Druid();
		break;
	}
}
void CharBotAI::UpdateInCombatAI_Paladin(){}

void CharBotAI::UpdateOutOfCombatAI_Paladin() {}

void CharBotAI::UpdateInCombatAI_Shaman() {}

void CharBotAI::UpdateOutOfCombatAI_Shaman() {}

void CharBotAI::UpdateInCombatAI_Hunter() {}

void CharBotAI::UpdateOutOfCombatAI_Hunter() {}

void CharBotAI::UpdateInCombatAI_Mage() 
{
	if (Unit* pVictim = me->GetVictim())
	{
		if (m_spells.mage.pPyroblast &&
			((m_spells.mage.pPresenceOfMind && me->HasAura(m_spells.mage.pPresenceOfMind->Id)) ||
			(!pVictim->IsInCombat() && (pVictim->GetMaxHealth() > me->GetMaxHealth()) && (me->GetDistance(pVictim) > 30.0f))) &&
			CanTryToCastSpell(pVictim, m_spells.mage.pPyroblast))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pPyroblast) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pIceBlock &&
			(me->GetHealthPercent() < 10.0f) &&
			CanTryToCastSpell(me, m_spells.mage.pIceBlock))
		{
			if (DoCastSpell(me, m_spells.mage.pIceBlock) == SPELL_CAST_OK)
				return;
		}

		if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE
			&& me->GetDistance(pVictim) > 30.0f)
		{
			me->GetMotionMaster()->MoveChase(pVictim, 30.0f);
		}
		else if (GetAttackersInRangeCount(10.0f))
		{
			if (m_spells.mage.pManaShield &&
				(me->GetPowerPercent(POWER_MANA) > 20.0f) &&
				CanTryToCastSpell(me, m_spells.mage.pManaShield))
			{
				if (DoCastSpell(me, m_spells.mage.pManaShield) == SPELL_CAST_OK)
					return;
			}

			if ((m_role != ROLE_MELEE_DPS) &&
				(me->GetMotionMaster()->GetCurrentMovementGeneratorType() != DISTANCING_MOTION_TYPE))
			{
				if (m_spells.mage.pBlink &&
					(me->HasUnitState(UNIT_STAT_CAN_NOT_MOVE) ||
						me->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED)) &&
					CanTryToCastSpell(me, m_spells.mage.pBlink))
				{
					if (me->GetMotionMaster()->GetCurrentMovementGeneratorType())
						me->GetMotionMaster()->MoveIdle();

					if (DoCastSpell(me, m_spells.mage.pBlink) == SPELL_CAST_OK)
						return;
				}

				if (!me->HasUnitState(UNIT_STAT_CAN_NOT_MOVE))
				{
					if (m_spells.mage.pFrostNova &&
						!pVictim->HasUnitState(UNIT_STAT_ROOT) &&
						!pVictim->HasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL) &&
						CanTryToCastSpell(me, m_spells.mage.pFrostNova))
					{
						DoCastSpell(me, m_spells.mage.pFrostNova);
					}

					RunAwayFromTarget(pVictim);

					return;
				}
			}
		}

		if (me->GetEnemyCountInRadiusAround(me, 10.0f) > 2)
		{

			if (m_spells.mage.pConeofCold &&
				CanTryToCastSpell(me, m_spells.mage.pConeofCold))
			{
				if (DoCastSpell(pVictim, m_spells.mage.pConeofCold) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.mage.pBlastWave &&
				CanTryToCastSpell(me, m_spells.mage.pBlastWave))
			{
				if (DoCastSpell(me, m_spells.mage.pBlastWave) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.mage.pArcaneExplosion &&
				CanTryToCastSpell(me, m_spells.mage.pArcaneExplosion))
			{
				if (DoCastSpell(me, m_spells.mage.pArcaneExplosion) == SPELL_CAST_OK)
					return;
			}
		}

		if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == DISTANCING_MOTION_TYPE)
			return;

		if (m_spells.mage.pCounterspell &&
			pVictim->IsNonMeleeSpellCasted(false, false, true) &&
			CanTryToCastSpell(pVictim, m_spells.mage.pCounterspell))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pCounterspell) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pRemoveLesserCurse &&
			CanTryToCastSpell(me, m_spells.mage.pRemoveLesserCurse) &&
			IsValidDispelTarget(me, m_spells.mage.pRemoveLesserCurse))
		{
			if (DoCastSpell(me, m_spells.mage.pRemoveLesserCurse) == SPELL_CAST_OK)
				return;
		}

		if (me->GetEnemyCountInRadiusAround(pVictim, 10.0f) > 2)
		{
			if (m_spells.mage.pBlizzard &&
				CanTryToCastSpell(pVictim, m_spells.mage.pBlizzard))
			{
				if (DoCastSpell(pVictim, m_spells.mage.pBlizzard) == SPELL_CAST_OK)
				{
					me->Say(sPlayerBotMgr.GenerateBotSpeech("aoe").c_str(), 0);
					return;
				}
			}
		}

		if (m_spells.mage.pPolymorph)
		{
			if (Unit* pTarget = SelectAttackerDifferentFrom(pVictim))
			{
				if (CanTryToCastSpell(pVictim, m_spells.mage.pPolymorph))
				{
					if (DoCastSpell(pVictim, m_spells.mage.pPolymorph) == SPELL_CAST_OK)
						return;
				}
			}
		}

		if (m_spells.mage.pArcanePower &&
			(me->GetPowerPercent(POWER_MANA) > 50.0f) &&
			CanTryToCastSpell(me, m_spells.mage.pArcanePower))
		{
			if (DoCastSpell(me, m_spells.mage.pArcanePower) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pPresenceOfMind &&
			(me->GetPowerPercent(POWER_MANA) > 50.0f) &&
			CanTryToCastSpell(me, m_spells.mage.pPresenceOfMind))
		{
			if (DoCastSpell(me, m_spells.mage.pPresenceOfMind) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pScorch &&
			(pVictim->GetHealthPercent() < 20.0f) &&
			CanTryToCastSpell(pVictim, m_spells.mage.pScorch))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pScorch) == SPELL_CAST_OK)
				return;
		}
		if ((!me->HasUnitState(UNIT_STAT_ROOT) || me->HasUnitState(UNIT_STAT_CAN_NOT_MOVE)) &&
			(me->GetCombatDistance(pVictim) < 8.0f) &&
			(m_role != ROLE_MELEE_DPS) &&
			me->GetMotionMaster()->GetCurrentMovementGeneratorType() != DISTANCING_MOTION_TYPE)
		{
			if (!me->IsStopped())
				me->StopMoving();
			me->GetMotionMaster()->Clear();
			RunAwayFromTarget(pVictim);
			return;
		}
		if (m_spells.mage.pFrostbolt &&
			CanTryToCastSpell(pVictim, m_spells.mage.pFrostbolt))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pFrostbolt) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pFireBlast &&
			CanTryToCastSpell(pVictim, m_spells.mage.pFireBlast))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pFireBlast) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pFireball &&
			CanTryToCastSpell(pVictim, m_spells.mage.pFireball))
		{
			if (DoCastSpell(pVictim, m_spells.mage.pFireball) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.mage.pEvocation &&
			(me->GetPowerPercent(POWER_MANA) < 30.0f) &&
			(GetAttackersInRangeCount(10.0f) == 0) &&
			CanTryToCastSpell(me, m_spells.mage.pEvocation))
		{
			if (DoCastSpell(me, m_spells.mage.pEvocation) == SPELL_CAST_OK)
			{
				me->Yell(sPlayerBotMgr.GenerateBotSpeech("low mana").c_str(), 0);
				return;
			}
		}

		if (me->HasSpell(PB_SPELL_SHOOT_WAND) &&
			!me->IsMoving() &&
			(me->GetPowerPercent(POWER_MANA) < 5.0f) &&
			!me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
			me->CastSpell(pVictim, PB_SPELL_SHOOT_WAND, false);
	}
}

void CharBotAI::UpdateOutOfCombatAI_Mage() 
{
	if (m_spells.mage.pArcaneBrilliance)
	{
		if (CanTryToCastSpell(me, m_spells.mage.pArcaneBrilliance))
		{
			if (DoCastSpell(me, m_spells.mage.pArcaneBrilliance) == SPELL_CAST_OK)
			{
				m_isBuffing = true;
				return;
			}
		}
	}
	else if (m_spells.mage.pArcaneIntellect)
	{
		if (Player* pTarget = SelectBuffTarget(m_spells.mage.pArcaneIntellect))
		{
			if (CanTryToCastSpell(pTarget, m_spells.mage.pArcaneIntellect))
			{
				if (DoCastSpell(pTarget, m_spells.mage.pArcaneIntellect) == SPELL_CAST_OK)
				{
					m_isBuffing = true;
					return;
				}
			}
		}
	}
	if (m_spells.mage.pIceArmor &&
		CanTryToCastSpell(me, m_spells.mage.pIceArmor))
	{
		if (DoCastSpell(me, m_spells.mage.pIceArmor) == SPELL_CAST_OK)
		{
			m_isBuffing = true;
			return;
		}
	}
	if (m_spells.mage.pIceBarrier &&
		CanTryToCastSpell(me, m_spells.mage.pIceBarrier))
	{
		if (DoCastSpell(me, m_spells.mage.pIceBarrier) == SPELL_CAST_OK)
		{
			m_isBuffing = true;
			return;
		}
	}

	if (m_isBuffing &&
		(!m_spells.mage.pArcaneIntellect ||
			!me->HasGCD(m_spells.mage.pArcaneIntellect)))
	{
		m_isBuffing = false;
	}
	if (m_spells.mage.pRemoveLesserCurse)
	{
		if (Unit* pFriend = SelectDispelTarget(m_spells.mage.pRemoveLesserCurse))
		{
			if (CanTryToCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse))
			{
				if (DoCastSpell(pFriend, m_spells.mage.pRemoveLesserCurse) == SPELL_CAST_OK)
					return;
			}
		}
	}
	if (me->GetVictim())
		UpdateInCombatAI_Mage();
}
void CharBotAI::UpdateInCombatAI_Priest() {}

void CharBotAI::UpdateOutOfCombatAI_Priest() {}

void CharBotAI::UpdateInCombatAI_Warlock() {}

void CharBotAI::UpdateOutOfCombatAI_Warlock() {}

void CharBotAI::UpdateInCombatAI_Warrior() {}

void CharBotAI::UpdateOutOfCombatAI_Warrior() {}

void CharBotAI::UpdateInCombatAI_Rogue()
{
	if (Unit* pVictim = me->GetVictim())
	{
		me->SetFacingToObject(pVictim);
		if (me->HasAuraType(SPELL_AURA_MOD_STEALTH))
		{
			if (m_spells.rogue.pPremeditation &&
				CanTryToCastSpell(pVictim, m_spells.rogue.pPremeditation))
			{
				DoCastSpell(pVictim, m_spells.rogue.pPremeditation);
			}

			if (pVictim->IsCaster())
			{
				if (m_spells.rogue.pGarrote &&
					CanTryToCastSpell(pVictim, m_spells.rogue.pGarrote))
				{
					if (DoCastSpell(pVictim, m_spells.rogue.pGarrote) == SPELL_CAST_OK)
						return;
				}
			}
			else
			{
				if (m_spells.rogue.pAmbush &&
					CanTryToCastSpell(pVictim, m_spells.rogue.pAmbush))
				{
					if (DoCastSpell(pVictim, m_spells.rogue.pAmbush) == SPELL_CAST_OK)
						return;
				}

				if (m_spells.rogue.pCheapShot &&
					CanTryToCastSpell(pVictim, m_spells.rogue.pCheapShot))
				{
					if (DoCastSpell(pVictim, m_spells.rogue.pCheapShot) == SPELL_CAST_OK)
						return;
				}
			}
		}
		else
		{
			if (m_spells.rogue.pVanish &&
				(me->GetHealthPercent() < 10.0f))
			{
				if (m_spells.rogue.pPreparation &&
					me->IsSpellReady(m_spells.rogue.pVanish->Id) &&
					CanTryToCastSpell(me, m_spells.rogue.pPreparation))
				{
					if (DoCastSpell(me, m_spells.rogue.pPreparation) == SPELL_CAST_OK)
						return;
				}

				if (CanTryToCastSpell(me, m_spells.rogue.pVanish))
				{
					if (DoCastSpell(me, m_spells.rogue.pVanish) == SPELL_CAST_OK)
					{
						RunAwayFromTarget(pVictim);
						return;
					}
				}
			}
		}

		if (me->GetComboPoints() > 4)
		{
			std::vector<SpellEntry const*> vSpells;
			if (m_spells.rogue.pSliceAndDice)
				vSpells.push_back(m_spells.rogue.pSliceAndDice);
			if (m_spells.rogue.pEviscerate)
				vSpells.push_back(m_spells.rogue.pEviscerate);
			if (m_spells.rogue.pKidneyShot)
				vSpells.push_back(m_spells.rogue.pKidneyShot);
			if (m_spells.rogue.pExposeArmor)
				vSpells.push_back(m_spells.rogue.pExposeArmor);
			if (m_spells.rogue.pRupture)
				vSpells.push_back(m_spells.rogue.pRupture);
			if (!vSpells.empty())
			{
				SpellEntry const* pComboSpell = SelectRandomContainerElement(vSpells);
				if (CanTryToCastSpell(pVictim, pComboSpell))
				{
					if (DoCastSpell(pVictim, pComboSpell) == SPELL_CAST_OK)
					{
						return;
					}
				}
			}
		}

		if (m_spells.rogue.pBlind)
		{
			if (Unit* pTarget = SelectAttackerDifferentFrom(pVictim))
			{
				if (CanTryToCastSpell(pTarget, m_spells.rogue.pBlind))
				{
					if (DoCastSpell(pTarget, m_spells.rogue.pBlind) == SPELL_CAST_OK)
					{
						me->AttackStop();
						AttackStart(pVictim);
						return;
					}
				}
			}
		}

		if (m_spells.rogue.pAdrenalineRush &&
			!me->GetPower(POWER_ENERGY) &&
			CanTryToCastSpell(me, m_spells.rogue.pAdrenalineRush))
		{
			if (DoCastSpell(me, m_spells.rogue.pAdrenalineRush) == SPELL_CAST_OK)
				return;
		}

		if (pVictim->IsNonMeleeSpellCasted())
		{
			if (m_spells.rogue.pGouge &&
				CanTryToCastSpell(pVictim, m_spells.rogue.pGouge))
			{
				if (DoCastSpell(pVictim, m_spells.rogue.pGouge) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.rogue.pKick &&
				CanTryToCastSpell(pVictim, m_spells.rogue.pKick))
			{
				if (DoCastSpell(pVictim, m_spells.rogue.pKick) == SPELL_CAST_OK)
					return;
			}
		}

		if (!me->HasAuraType(SPELL_AURA_MOD_STEALTH))
		{
			if (m_spells.rogue.pEvasion &&
				(me->GetHealthPercent() < 80.0f) &&
				((GetAttackersInRangeCount(10.0f) > 2) || !IsRangedDamageClass(pVictim->GetClass())) &&
				CanTryToCastSpell(me, m_spells.rogue.pEvasion))
			{
				if (DoCastSpell(me, m_spells.rogue.pEvasion) == SPELL_CAST_OK)
					return;
			}

			if (m_spells.rogue.pColdBlood &&
				CanTryToCastSpell(me, m_spells.rogue.pColdBlood))
			{
				DoCastSpell(me, m_spells.rogue.pColdBlood);
			}

			if (m_spells.rogue.pBladeFlurry &&
				CanTryToCastSpell(me, m_spells.rogue.pBladeFlurry))
			{
				if (DoCastSpell(me, m_spells.rogue.pBladeFlurry) == SPELL_CAST_OK)
					return;
			}
		}

		if (m_spells.rogue.pBackstab &&
			CanTryToCastSpell(pVictim, m_spells.rogue.pBackstab))
		{
			if (DoCastSpell(pVictim, m_spells.rogue.pBackstab) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.rogue.pGhostlyStrike &&
			CanTryToCastSpell(pVictim, m_spells.rogue.pGhostlyStrike))
		{
			if (DoCastSpell(pVictim, m_spells.rogue.pGhostlyStrike) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.rogue.pHemorrhage &&
			CanTryToCastSpell(pVictim, m_spells.rogue.pHemorrhage))
		{
			if (DoCastSpell(pVictim, m_spells.rogue.pHemorrhage) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.rogue.pSinisterStrike &&
			CanTryToCastSpell(pVictim, m_spells.rogue.pSinisterStrike))
		{
			if (DoCastSpell(pVictim, m_spells.rogue.pSinisterStrike) == SPELL_CAST_OK)
				return;
		}

		if (m_spells.rogue.pSprint &&
			!me->HasUnitState(UNIT_STAT_ROOT) &&
			!me->CanReachWithMeleeAutoAttack(pVictim) &&
			CanTryToCastSpell(me, m_spells.rogue.pSprint))
		{
			if (DoCastSpell(me, m_spells.rogue.pSprint) == SPELL_CAST_OK)
				return;
		}
	}
}

void CharBotAI::UpdateOutOfCombatAI_Rogue() 
{
	if (m_spells.rogue.pMainHandPoison &&
		CanTryToCastSpell(me, m_spells.rogue.pMainHandPoison))
	{
		if (CastWeaponBuff(m_spells.rogue.pMainHandPoison, EQUIPMENT_SLOT_MAINHAND) == SPELL_CAST_OK)
			return;
	}

	if (m_spells.rogue.pOffHandPoison &&
		CanTryToCastSpell(me, m_spells.rogue.pOffHandPoison))
	{
		if (CastWeaponBuff(m_spells.rogue.pOffHandPoison, EQUIPMENT_SLOT_OFFHAND) == SPELL_CAST_OK)
			return;
	}

	if (m_spells.rogue.pStealth &&
		CanTryToCastSpell(me, m_spells.rogue.pStealth))
	{
		if (DoCastSpell(me, m_spells.rogue.pStealth) == SPELL_CAST_OK)
			return;
	}

	if (me->GetVictim())
		UpdateInCombatAI_Rogue();
}

void CharBotAI::UpdateInCombatAI_Druid() {}

void CharBotAI::UpdateOutOfCombatAI_Druid() {}
