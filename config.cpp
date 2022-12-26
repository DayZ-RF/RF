#define _ARMA_

class CfgPatches
{
	class RF
	{
		author = "Dad Fedor & Swift Dungeon";
		name = "RF";
		url = "https://discord.gg/d9kP7ezX3n";
		units[] = {};
		weapons[] = {};
		requiredAddons[] = {"DZ_Data", "DZ_Sounds_Effects"};
		requiredVersion = 0.1;
	};
};

class CfgMods
{
	class RF
	{
		type="mod";
		dir="RF";
		class defs
		{
			class coreScriptModule
			{
				value = "";
				files[] = { "RF/scripts/1_Core" };
			};
			class gameLibScriptModule
			{
				value = "";
				files[] = { "RF/scripts/2_GameLib" };
			};
			class gameScriptModule
			{
				value = "";
				files[] = { "RF/scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "RF/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "RF/scripts/5_Mission" };
			};
		};
	};
};
