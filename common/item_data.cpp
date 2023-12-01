#include "item_data.h"
#include "classes.h"
#include "races.h"

bool EQ::ItemData::IsEquipable(uint16 race_id, uint16 class_id) const {
	if (!(Races & GetPlayerRaceBit(race_id)))
		return false;

	if (!(Classes & GetPlayerClassBit(GetPlayerClassValue(class_id))))
		return false;

	return true;
}

bool EQ::ItemData::IsClassCommon() const {
	return (ItemClass == item::ItemClassCommon);
}

bool EQ::ItemData::IsClassBag() const {
	return (ItemClass == item::ItemClassBag);
}

bool EQ::ItemData::IsClassBook() const {
	return (ItemClass == item::ItemClassBook);
}

bool EQ::ItemData::IsType1HWeapon() const {
	return ((ItemType == item::ItemType1HBlunt) || (ItemType == item::ItemType1HSlash) || (ItemType == item::ItemType1HPiercing));
}

bool EQ::ItemData::IsType2HWeapon() const {
	return ((ItemType == item::ItemType2HBlunt) || (ItemType == item::ItemType2HSlash) || (ItemType == item::ItemType2HPiercing));
}

bool EQ::ItemData::IsTypeShield() const {
	return (ItemType == item::ItemTypeShield);
}