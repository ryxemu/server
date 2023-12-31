#include "../spawn2.h"
#include "lua_npc.h"
#include "lua_spawn.h"

uint32 Lua_Spawn::GetID() {
	Lua_Safe_Call_Int();
	return self->GetID();
}
/*
void Lua_Spawn::LoadGrid() {
	Lua_Safe_Call_Void();
	self->LoadGrid();
}

void Lua_Spawn::Enable() {
	Lua_Safe_Call_Void();
	return self->Enable();
}

void Lua_Spawn::Disable() {
	Lua_Safe_Call_Void();
	return self->Disable();
}

bool Lua_Spawn::Enabled() {
	Lua_Safe_Call_Bool();
	return self->Enabled();
}

void Lua_Spawn::Reset() {
	Lua_Safe_Call_Void();
	self->Reset();
}

void Lua_Spawn::Depop() {
	Lua_Safe_Call_Void();
	self->Depop();
}

void Lua_Spawn::Repop() {
	Lua_Safe_Call_Void();
	self->Repop();
}

void Lua_Spawn::Repop(uint32 delay) {
	Lua_Safe_Call_Void();
	self->Repop(delay);
}

void Lua_Spawn::ForceDespawn() {
	Lua_Safe_Call_Void();
	self->ForceDespawn();
}



float Lua_Spawn::GetX() {
	Lua_Safe_Call_Real();
	return self->GetX();
}

float Lua_Spawn::GetY() {
	Lua_Safe_Call_Real();
	return self->GetY();
}

float Lua_Spawn::GetZ() {
	Lua_Safe_Call_Real();
	return self->GetZ();
}

float Lua_Spawn::GetHeading() {
	Lua_Safe_Call_Real();
	return self->GetHeading();
}

void Lua_Spawn::SetRespawnTimer(uint32 newrespawntime) {
	Lua_Safe_Call_Void();
	self->SetRespawnTimer(newrespawntime);
}

void Lua_Spawn::SetVariance(uint32 newvariance) {
	Lua_Safe_Call_Void();
	self->SetVariance(newvariance);
}

uint32 Lua_Spawn::GetVariance() {
	Lua_Safe_Call_Int();
	return self->GetVariance();
}

uint32 Lua_Spawn::RespawnTimer() {
	Lua_Safe_Call_Int();
	return self->RespawnTimer();
}

uint32 Lua_Spawn::SpawnGroupID() {
	Lua_Safe_Call_Int();
	return self->SpawnGroupID();
}

uint32 Lua_Spawn::CurrentNPCID() {
	Lua_Safe_Call_Int();
	return self->CurrentNPCID();
}

void Lua_Spawn::SetCurrentNPCID(uint32 nid) {
	Lua_Safe_Call_Void();
	self->SetCurrentNPCID(nid);
}

uint32 Lua_Spawn::GetSpawnCondition() {
	Lua_Safe_Call_Int();
	return self->GetSpawnCondition();
}

bool Lua_Spawn::NPCPointerValid() {
	Lua_Safe_Call_Bool();
	return self->NPCPointerValid();
}

void Lua_Spawn::SetNPCPointer(Lua_NPC n) {
	Lua_Safe_Call_Void();
	self->SetNPCPointer(n);
}

void Lua_Spawn::SetTimer(uint32 duration) {
	Lua_Safe_Call_Void();
	self->SetTimer(duration);
}

uint32 Lua_Spawn::GetKillCount() {
	Lua_Safe_Call_Int();
	return self->GetKillCount();
} */