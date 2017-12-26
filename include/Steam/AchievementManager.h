#pragma once

#include "global.h"

class SteamAchievements;
class CharacterCore;
class Achievement;

class AchievementManager final {
public:
	AchievementManager(CharacterCore* core);
	~AchievementManager();

	void notifyAchievement(const std::string& achievement, const std::string& tag, const std::string& message);
	void notifyAchievementCore(const std::string& achievement);

private:
	void unlockAchievement(const std::string& achievement);
	void initAchievements();

private:
	CharacterCore* m_characterCore = nullptr;
	SteamAchievements* m_steamAchievements = nullptr;
	std::map<std::string, Achievement*> m_achievements;
};