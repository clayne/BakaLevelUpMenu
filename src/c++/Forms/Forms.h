#pragma once

class Forms
{
private:
	static std::uint32_t HookInitializer_DefaultObject()
	{
		// Initializer override
		AmmoWornKeyword_DO =
			RE::DefaultObjectFormFactory::Create(
				"AmmoWornKeyword_DO",
				"This ammo is worn on the actors body.",
				RE::ENUM_FORM_ID::kKYWD);

		logger::debug("Injected DefaultObjects."sv);
		return 1;
	}

	static std::uint32_t HookInitializer_Setting()
	{
		RE::GameSettingCollection::InitCollection();
		if (auto GameSettingCollection = RE::GameSettingCollection::GetSingleton(); GameSettingCollection)
		{
			// Initializer override
			GameSettingCollection->Add(&fBlockPowerAttackMult);

			// Add new
			GameSettingCollection->Add(&sBakaEqual);
			GameSettingCollection->Add(&sBakaNotEqual);
			GameSettingCollection->Add(&sBakaGreater);
			GameSettingCollection->Add(&sBakaGreaterEqual);
			GameSettingCollection->Add(&sBakaLess);
			GameSettingCollection->Add(&sBakaLessEqual);
			GameSettingCollection->Add(&sBakaHasPerk);
			GameSettingCollection->Add(&sBakaNotPerk);
			GameSettingCollection->Add(&sBakaLevel);
			GameSettingCollection->Add(&sBakaReqs);
			GameSettingCollection->Add(&sBakaRanks);
			GameSettingCollection->Add(&sBakaLevelUpText);
			GameSettingCollection->Add(&sBakaPerkMenu);
		}

		logger::debug("Injected GMSTs."sv);
		return 1;
	}

	// members
	inline static RE::Setting fBlockPowerAttackMult{ "fBlockPowerAttackMult", 0.75f };
	inline static RE::BGSDefaultObject* AmmoWornKeyword_DO{ nullptr };

public:
	static void InstallHooks()
	{
		REL::Relocation<std::uintptr_t> targetDefault{ REL::ID(1359842) };
		REL::Relocation<std::uintptr_t> targetSetting{ REL::ID(984976) };

		stl::asm_replace(targetDefault.address(), 0x31, reinterpret_cast<std::uintptr_t>(HookInitializer_DefaultObject));
		stl::asm_replace(targetSetting.address(), 0x68, reinterpret_cast<std::uintptr_t>(HookInitializer_Setting));
	}

	// members
	inline static RE::Setting sBakaEqual{ "sBakaEqual", "{:s} is exactly {:0.0F}" };
	inline static RE::Setting sBakaNotEqual{ "sBakaNotEqual", "{:s} is not {:0.0F}" };
	inline static RE::Setting sBakaGreater{ "sBakaGreater", "{:s} {:0.0F}" };
	inline static RE::Setting sBakaGreaterEqual{ "sBakaGreaterEqual", "{:s} {:0.0F}" };
	inline static RE::Setting sBakaLess{ "sBakaLess", "{:s} &lt; {:0.0F}" };
	inline static RE::Setting sBakaLessEqual{ "sBakaLessEqual", "{:s} &lt; {:0.0F}" };
	inline static RE::Setting sBakaHasPerk{ "sBakaHasPerk", "has {:s} perk" };
	inline static RE::Setting sBakaNotPerk{ "sBakaNotPerk", "does not have {:s} perk" };
	inline static RE::Setting sBakaLevel{ "sBakaLevel", "Level {:d}" };
	inline static RE::Setting sBakaReqs{ "sBakaReqs", "Reqs: {:s}" };
	inline static RE::Setting sBakaRanks{ "sBakaRanks", "Ranks: {:d}" };
	inline static RE::Setting sBakaLevelUpText{ "sBakaLevelUpText", "Welcome to Level {:d}" };
	inline static RE::Setting sBakaPerkMenu{ "sBakaPerkMenu", "Perk Menu" };
};
