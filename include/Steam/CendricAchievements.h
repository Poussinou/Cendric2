#pragma once

#include "Steam/AchievementData.h"

// Defining our achievements
enum AchievementID
{
	// bosses
	ACH_SAVE_ZEFF = 0,
	ACH_KILL_ZEFF,
	ACH_KILL_KHAJAG,
	ACH_KILL_ELYSIA,
	ACH_KILL_ALASTOR,
	ACH_KILL_MERCENARIES,
	ACH_FRIEND_YASHA,
	ACH_KILL_YASHA,
	ACH_KILL_ROYAL_GUARDS,
	ACH_KILL_VELIUS,

	// guilds
	ACH_CLERIC_REP_70,
	ACH_NECRO_REP_70,
	ACH_THIEF_REP_70,

	// general
	ACH_NO_DEATH,
	ACH_GOLD_1000,
	ACH_ALL_MODIFIERS,
	ACH_ALL_BOOKS,
	ACH_ALL_WAYPOINTS,
	ACH_ALL_KEYS,

	// etoz' tower
	ACH_ETOZ_1,
	ACH_ETOZ_2,
	ACH_ETOZ_3,
	ACH_ETOZ_4,
	
	// other
	ACH_LEEROY,
	ACH_TEARSTAFF,
	ACH_CANADIAN_LOOP,
	ACH_CHICKEN_SHOCKER,
	ACH_NECRONOMICON
};

#define ACHIEVEMENT_COUNT 28

AchievementData CendricAchievements[] =
{
	_ACH_ID(ACH_SAVE_ZEFF, "ACH_SAVE_ZEFF" ),
	_ACH_ID(ACH_KILL_ZEFF, "ACH_KILL_ZEFF" ),
	_ACH_ID(ACH_KILL_KHAJAG, "ACH_KILL_KHAJAG" ),
	_ACH_ID(ACH_KILL_ELYSIA, "ACH_KILL_ELYSIA" ),
	_ACH_ID(ACH_KILL_ALASTOR, "ACH_KILL_ALASTOR"),
	_ACH_ID(ACH_KILL_MERCENARIES, "ACH_KILL_MERCENARIES"),
	_ACH_ID(ACH_FRIEND_YASHA, "ACH_FRIEND_YASHA"),
	_ACH_ID(ACH_KILL_YASHA, "ACH_KILL_YASHA"),
	_ACH_ID(ACH_KILL_ROYAL_GUARDS, "ACH_KILL_ROYAL_GUARDS"),
	_ACH_ID(ACH_KILL_VELIUS, "ACH_KILL_VELIUS"),

	_ACH_ID(ACH_CLERIC_REP_70, "ACH_CLERIC_REP_70"),
	_ACH_ID(ACH_NECRO_REP_70, "ACH_NECRO_REP_70"),
	_ACH_ID(ACH_THIEF_REP_70, "ACH_THIEF_REP_70"),

	_ACH_ID(ACH_NO_DEATH, "ACH_NO_DEATH"),
	_ACH_ID(ACH_GOLD_1000, "ACH_GOLD_1000"),
	_ACH_ID(ACH_ALL_MODIFIERS, "ACH_ALL_MODIFIERS"),
	_ACH_ID(ACH_ALL_BOOKS, "ACH_ALL_BOOKS"),
	_ACH_ID(ACH_ALL_WAYPOINTS, "ACH_ALL_WAYPOINTS"),
	_ACH_ID(ACH_ALL_KEYS, "ACH_ALL_KEYS"),

	_ACH_ID(ACH_ETOZ_1, "ACH_ETOZ_1"),
	_ACH_ID(ACH_ETOZ_2, "ACH_ETOZ_2"),
	_ACH_ID(ACH_ETOZ_3, "ACH_ETOZ_3"),
	_ACH_ID(ACH_ETOZ_4, "ACH_ETOZ_4"),

	_ACH_ID(ACH_LEEROY, "ACH_LEEROY"),
	_ACH_ID(ACH_TEARSTAFF, "ACH_TEARSTAFF"),
	_ACH_ID(ACH_CANADIAN_LOOP, "ACH_CANADIAN_LOOP"),
	_ACH_ID(ACH_CHICKEN_SHOCKER, "ACH_CHICKEN_SHOCKER"),
	_ACH_ID(ACH_NECRONOMICON, "ACH_NECRONOMICON"),
};