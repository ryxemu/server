#include "light_source.h"

#include <string.h>

uint8 EQ::lightsource::TypeToLevel(uint8 light_type) {
	switch (light_type) {
		case LightTypeGlobeOfStars:
			return LightLevelBrilliant;  // 10
		case LightTypeFlamelessLantern:
		case LightTypeGreaterLightstone:
			return LightLevelLargeMagic;  // 9
		case LightTypeLargeLantern:
			return LightLevelLargeLantern;  // 8
		case LightTypeSteinOfMoggok:
		case LightTypeLightstone:
			return LightLevelMagicLantern;  // 7
		case LightTypeSmallLantern:
			return LightLevelSmallLantern;  // 6
		case LightTypeColdlight:
		case LightTypeUnknown2:
			return LightLevelBlueLight;  // 5
		case LightTypeFireBeetleEye:
		case LightTypeUnknown1:
			return LightLevelRedLight;  // 4
		case LightTypeTinyGlowingSkull:
		case LightTypeLightGlobe:
			return LightLevelSmallMagic;  // 3
		case LightTypeTorch:
			return LightLevelTorch;  // 2
		case LightTypeCandle:
			return LightLevelCandle;  // 1
		default:
			return LightLevelUnlit;  // 0
	}
}

bool EQ::lightsource::IsLevelGreater(uint8 left_type, uint8 right_type) {
	static const uint8 light_levels[LightTypeCount] = {
	    LightLevelUnlit,        /* LightTypeNone */
	    LightLevelCandle,       /* LightTypeCandle */
	    LightLevelTorch,        /* LightTypeTorch */
	    LightLevelSmallMagic,   /* LightTypeTinyGlowingSkull */
	    LightLevelSmallLantern, /* LightTypeSmallLantern */
	    LightLevelMagicLantern, /* LightTypeSteinOfMoggok */
	    LightLevelLargeLantern, /* LightTypeLargeLantern */
	    LightLevelLargeMagic,   /* LightTypeFlamelessLantern */
	    LightLevelBrilliant,    /* LightTypeGlobeOfStars */
	    LightLevelSmallMagic,   /* LightTypeLightGlobe */
	    LightLevelMagicLantern, /* LightTypeLightstone */
	    LightLevelLargeMagic,   /* LightTypeGreaterLightstone */
	    LightLevelRedLight,     /* LightTypeFireBeetleEye */
	    LightLevelBlueLight,    /* LightTypeColdlight */
	    LightLevelRedLight,     /* LightTypeUnknown1 */
	    LightLevelBlueLight     /* LightTypeUnknown2 */
	};

	if (left_type >= LightTypeCount) {
		left_type = LightTypeNone;
	}
	if (right_type >= LightTypeCount) {
		right_type = LightTypeNone;
	}

	return (light_levels[left_type] > light_levels[right_type]);
}

EQ::LightSource_Struct::LightSource_Struct() {
	Clear();
}

void EQ::LightSource_Struct::Clear() {
	memset(&Slot, 0, (sizeof(uint8) * lightsource::LightCount));
}

void EQ::LightSourceProfile::Clear() {
	Type.Clear();
	Level.Clear();
}