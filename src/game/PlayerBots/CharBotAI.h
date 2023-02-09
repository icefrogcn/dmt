#ifndef MANGOS_CHARBOTAI_H
#define MANGOS_CHARBOTAI_H

#include "CombatBotBaseAI.h"





class CharBotAI : public CombatBotBaseAI
{
public:

	CharBotAI() : CombatBotBaseAI()
	{
		m_role = ROLE_INVALID;
		m_updateTimer.Reset(2000);
	}
	bool OnSessionLoaded(PlayerBotEntry* entry, WorldSession* sess) override;
	void FreeRandomizationMove();
	void FollowLeaderMove(Player* pLeader);
	void OnPlayerLogin() final;
	void UpdateAI(uint32 const diff) final;

	void OnPacketReceived(WorldPacket const* packet) final;
	void SendFakePacket(uint16 opcode) final;
	
	void AddToPlayerGroup();
	
	Player* GetPartyLeader() const;
	bool AttackStart(Unit* pVictim);
	Unit* SelectAttackTarget(Player* pLeader) const;
	Unit* SelectAttackTarget(Unit* pExcept = nullptr) const; 
	Unit* SelectPartyAttackTarget() const;
	//Player* SelectResurrectionTarget() const;
	//Player* SelectShieldTarget() const;
	bool DrinkAndEat();
	void RunAwayFromTarget(Unit* pTarget);
	//bool EnterCombatDruidForm();
	
	void UpdateInCombatAI() final;
	void UpdateOutOfCombatAI() final;
	void UpdateInCombatAI_Paladin() final;
	void UpdateOutOfCombatAI_Paladin() final;
	void UpdateInCombatAI_Shaman() final;
	void UpdateOutOfCombatAI_Shaman() final;
	void UpdateInCombatAI_Hunter() final;
	void UpdateOutOfCombatAI_Hunter() final;
	void UpdateInCombatAI_Mage() final;
	void UpdateOutOfCombatAI_Mage() final;
	void UpdateInCombatAI_Priest() final;
	void UpdateOutOfCombatAI_Priest() final;
	void UpdateInCombatAI_Warlock() final;
	void UpdateOutOfCombatAI_Warlock() final;
	void UpdateInCombatAI_Warrior() final;
	void UpdateOutOfCombatAI_Warrior() final;
	void UpdateInCombatAI_Rogue() final;
	void UpdateOutOfCombatAI_Rogue() final;
	void UpdateInCombatAI_Druid() final;
	void UpdateOutOfCombatAI_Druid() final;

	
	std::vector<LootResponseData> m_lootResponses;
	ShortTimeTracker m_updateTimer;
	ObjectGuid m_leaderGuid;
	ObjectGuid m_cloneGuid;
	uint8 m_race = 0;
	uint8 m_class = 0;
	uint32 m_mapId = 0;
	uint32 m_instanceId = 0;
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
	float m_o = 0.0f;

	char sMessage[200] = "";

	bool m_initialized = false;
	bool m_isBuffing = false;
	bool m_receivedBgInvite = false;
	bool m_randomMove = false;
	CombatBotRoles m_role = ROLE_INVALID;


};

#endif
