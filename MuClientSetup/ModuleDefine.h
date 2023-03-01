#pragma once

const char* REG_KEY_PATH			= "SOFTWARE\\WebZen\\Mu\\Config";
const char* REG_KEY_MUSIC			= "MusicOnOff";
const char* REG_KEY_SOUND			= "SoundOnOff";
const char* REG_KEY_WINDOWMODE		= "WindowMode";
const char* REG_KEY_RESOULTION		= "Resolution";
const char* REG_KEY_TEXTINPUT		= "TextInput";
const char* REG_KEY_ID				= "ID";

enum MUSIC_VALUE
{
	MUSIC_VALUE_OFF	= 0,
	MUSIC_VALUE_ON	= 1,	
};

enum SOUND_VALUE
{
	SOUND_VALUE_OFF	= 0,
	SOUND_VALUE_ON	= 1,	
};

enum WINDOW_MODE_VALUE
{
	WM_VALUE_FULL_SCREEN	= 0,	// 全屏模式
	WM_VALUE_WINDOW			= 1,	// 窗口化模式
};

enum RESOLUTION_VALUE
{
	RESOLUTION_VALUE_640_480	= 0,
	RESOLUTION_VALUE_800_600	= 1,
	RESOLUTION_VALUE_1024_768	= 2,
	RESOLUTION_VALUE_1280_1024	= 3,
};

/*
高级文字
TextInput		0未开启，2开启。
默认是1，不知道是干嘛的，进游戏看了下，也看不出0、1、2的区别
*/
enum TEXT_INPUT_VALUE
{
	TI_VALUE_OFF	= 0,
	TI_VALUE_ON		= 2,
};


enum GLOBAL_HOTKEY
{
	GLOBAL_HOTKEY_CTRL_Y	= 1,	//自动右键
};