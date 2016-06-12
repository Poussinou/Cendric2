#pragma once

#include "Beans/DatabaseBean.h"

// a spell item bean, directly from the database
struct ItemSpellBean : DatabaseBean {
	std::string item_id;
	int spell_id;
};