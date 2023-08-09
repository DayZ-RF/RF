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
				files[] = { "RF/common", "RF/scripts/1_Core" };
			};
			class gameLibScriptModule
			{
				value = "";
				files[] = { "RF/common", "RF/scripts/2_GameLib" };
			};
			class gameScriptModule
			{
				value = "";
				files[] = { "RF/common", "RF/scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "RF/common", "RF/scripts/4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "RF/common", "RF/scripts/5_Mission" };
			};
		};
	};
};

class CfgSoundShaders
{
	class RF_Notification_SoundShader
	{
		samples[] = {{"RF\data\sounds\notification", 1}};
		volume = 1;
	};
	
};

class CfgSoundSets
{
	class RF_Notification_SoundSet
	{
		soundShaders[] = {"RF_Notification_SoundShader"};
		volumeFactor = 1;
		frequencyFactor = 1;
		spatial = 1;
	};
};