#pragma once
#include "../../Math/MathStatics.h"
#include "FileManager.h"

//#include <D3D11.h>
//#include <DXGI.h>
//#include <D3DX11.h>
//#include <DxErr.h>
#include <Windows.h>
#include <dinput.h>

#include <vector>
#include <functional>
#include <map>
#include <thread>
#include <mutex>


// A list of all valid key inputs.
enum EKey
{
	IE_AbntC1 = 0xC1,
	IE_AbntC2 = 0xC2,

	IE_Add = 0x6B,
	IE_ATTN = 0xF6,
	IE_Back = 0x08,
	IE_Cancel = 0x03,
	IE_Clear = 0x0C,
	IE_CrSel = 0xF7,
	IE_Decimal = 0x6E,
	IE_Divide = 0x6F,
	IE_ErEof = 0xF9,
	IE_Escape = 0x1B,
	IE_ExSel = 0xF8,
	IE_IcoClear = 0xE6,
	IE_IcoHelp = 0xE3,
	
	IE_0 = 0x30,
	IE_1 = 0x31,
	IE_2 = 0x32,
	IE_3 = 0x33,
	IE_4 = 0x34,
	IE_5 = 0x35,
	IE_6 = 0x36,
	IE_7 = 0x37,
	IE_8 = 0x38,
	IE_9 = 0x39,
	
	IE_A = 0x41,
	IE_B = 0x42,
	IE_C = 0x43,
	IE_D = 0x44,
	IE_E = 0x45,
	IE_F = 0x46,
	IE_G = 0x47,
	IE_H = 0x48,
	IE_I = 0x49,
	IE_J = 0x4A,
	IE_K = 0x4B,
	IE_L = 0x4C,
	IE_M = 0x4D,
	IE_N = 0x4E,
	IE_O = 0x4F,
	IE_P = 0x50,
	IE_Q = 0x51,
	IE_R = 0x52,
	IE_S = 0x53,
	IE_T = 0x54,
	IE_U = 0x55,
	IE_V = 0x56,
	IE_W = 0x57,
	IE_X = 0x58,
	IE_Y = 0x59,
	IE_Z = 0x5A,

	IE_Multiply = 0x6A,
	IE_NoName = 0xFC,
	IE_Numpad0 = 0x60,
	IE_Numpad1 = 0x61,
	IE_Numpad2 = 0x62,
	IE_Numpad3 = 0x63,
	IE_Numpad4 = 0x64,
	IE_Numpad5 = 0x65,
	IE_Numpad6 = 0x66,
	IE_Numpad7 = 0x67,
	IE_Numpad8 = 0x68,
	IE_Numpad9 = 0x69,

	IE_Oem102 = 0xE2,
	IE_Oem1 = 0xBA,
	IE_Oem2 = 0xBF,
	IE_Oem3 = 0xC0,
	IE_Oem4 = 0xDB,
	IE_Oem5 = 0xDC,
	IE_Oem6 = 0xDD,
	IE_Oem7 = 0xDE,
	IE_Oem8 = 0xDF,
	IE_OemAttn = 0xF0,
	IE_OemAuto = 0xF3,
	IE_OemAx = 0xE1,
	IE_Oem_Backtab = 0xF5,
	IE_OemClear = 0xFE,
	IE_OemComma = 0xBC,
	IE_OemCopy = 0xF2,
	IE_OemCuSel = 0xEF,
	IE_OemEnlw = 0xF4,
	IE_OemFinish = 0xF1,
	IE_OemFJLoya = 0x95,
	IE_OemFJMasshou = 0x93,
	IE_OemFJRoya = 0x96,
	IE_OemFJTouroku = 0x94,
	IE_OemFJ_Jisho = 0x92,
	IE_OemJump = 0xEA,
	IE_OemMinus = 0xBD,
	IE_OemPA1 = 0xEB,
	IE_OemPA2 = 0xEC,
	IE_OemPA3 = 0xED,
	IE_OemPeriod = 0xBE,
	IE_OemPlus = 0xBB,
	IE_OemReset = 0xE9,
	IE_OemWsCtrl = 0xEE,
	
	IE_Pa1 = 0xFD,
	IE_Packet = 0xE7,
	IE_Play = 0xFA,
	IE_ProcessKey = 0xE5,
	IE_Return = 0x0D,
	IE_Select = 0x29,
	IE_Separator = 0x6C,
	IE_Space = 0x20,
	IE_Subtract = 0x6D,
	IE_Tab = 0x09,
	IE_Zoom = 0xFB,

	IE_None = 0xFF,
	IE_Accept = 0x1E,
	IE_Apps = 0x5D,
	IE_BrowserBack = 0xA6,
	IE_BrowserFavorites = 0xAB,
	IE_BrowserForward = 0xA7,
	IE_BrowserHome = 0xAC,
	IE_BrowserRefresh = 0xA8,
	IE_BrowserSearch = 0xAA,
	IE_BrowserStop = 0xA9,

	IE_Capital = 0x14,
	IE_Convert = 0x1C,
	IE_Delete = 0x2E,
	IE_End = 0x23,

	IE_F1 = 0x70,
	IE_F2 = 0x71,
	IE_F3 = 0x72,
	IE_F4 = 0x73,
	IE_F5 = 0x74,
	IE_F6 = 0x75,
	IE_F7 = 0x76,
	IE_F8 = 0x77,
	IE_F9 = 0x78,
	IE_F10 = 0x79,
	IE_F11 = 0x7A,
	IE_F12 = 0x7B,
	IE_F13 = 0x7C,
	IE_F14 = 0x7D,
	IE_F15 = 0x7E,
	IE_F16 = 0x7F,
	IE_F17 = 0x80,
	IE_F18 = 0x81,
	IE_F19 = 0x82,
	IE_F20 = 0x83,
	IE_F21 = 0x84,
	IE_F22 = 0x85,
	IE_F23 = 0x86,
	IE_F24 = 0x87,

	IE_Final = 0x18,
	IE_Help = 0x2F,
	IE_Home = 0x24,
	IE_Ico00 = 0xE4,
	IE_Insert = 0x2D,
	IE_Junja = 0x17,
	IE_Kana = 0x15,
	IE_Kanji = 0x19,
	IE_LaunchApp1 = 0xB6,
	IE_LaunchApp2 = 0xB7,
	IE_LaunchMail = 0xB4,
	IE_LaunchMediaSelect = 0xB5,

	IE_LButton = 0x01,				// Left mouse button.
	IE_RButton = 0x02,				// Right mouse button.
	IE_MButton = 0x04,				// Middle mouse button.
	IE_XButton1 = 0x05,				// X button 1.
	IE_XButton2 = 0x06,				// X button 2.

	IE_LControl = 0xA2,
	IE_LMenu = 0xA4,
	IE_LShift = 0xA0,
	IE_LWin = 0x5B,

	IE_RControl = 0xA3,
	IE_RMenu = 0xA5,
	IE_RShift = 0xA1,
	IE_RWin = 0x5C,
	IE_Scroll = 0x91,				// Scroll lock.
	IE_Sleep = 0x5F,
	IE_PrtScreen = 0x2C,

	IE_Up = 0x26,
	IE_Down = 0x28,
	IE_Left = 0x25,
	IE_Right = 0x27,

	IE_MediaNextTrack = 0xB0,
	IE_MediaPrevTrack = 0xB1,
	IE_MediaStop = 0xB2,
	IE_MediaPlayPause = 0xB3,
	IE_ModeChange = 0x1F,
	IE_PageUp = 0x21,
	IE_PageDown = 0x22,
	IE_NonConvert = 0x1D,
	IE_NumLock = 0x90,
	IE_Pause = 0x13,
	IE_Print = 0x2A,

	IE_VolumeDown = 0xAE,
	IE_VolumeUp = 0xAf,
	IE_VolumeMute = 0xAD,
};


// Determines at what point the bound input will call it's bound function.
enum EInputMode
{
	Pressed = 0x00000001,		// Calls the bound function when the corosponding key is pressed.
	Released = 0x00000002,		// Calls the bound function when the corosponding key is released.
	Continuous = 0x00000004,	// Calls the bound function when the corosponding key is held.
	Toggle = 0x00000008,		// Calls the bound function when the corosponding key is pressed / released.
	All = 0x00000016			// Calls teh bound functoin when the corosponding key is pressed / held / released.
};


// The core information for a bound axis input.
struct SAxisKeyInfo
{
public:
	/// Properties

	// The key bound to this input.
	uint Key;

	// The value this input will return when pressed.
	float Value{ 1.0f };

	// The axis this input is currently at.
	float Axis{ 0.0f };

	// Determines how quickly the key will reach the max.
	float Strength{ 1.0f };

	// Should control be held to activate this input.
	bool UseControl{ false };

	// Should shift be held to activate this input.
	bool UseShift{ false };
};


// The core information for a bound action input.
struct SActionKeyInfo
{
public:
	/// Properties

	// The key bound to this input.
	uint Key;

	// What point this input will call the bound function.
	EInputMode InputMode;

	// Should control be held to activate this input.
	bool UseControl{ false };

	// Should shift be held to activate this input.
	bool UseShift{ false };

	// Represents if this button is currently pressed.
	bool Pressed{ false };
};


// The storage container for an axis input.
struct SAxisKey
{
public:
	/// Properties

	// A list of keys that are bound to this input.
	std::vector<SAxisKeyInfo> Keys;

	// The function to call.
	std::function<void(float)> Function;


	/// Constructors

	// Constructor, Default.
	SAxisKey() {}

	// Constructor, Initiates the input with a bound function.
	SAxisKey(std::function<void(float)> Delegate)
		:Function{ Delegate }
	{}


	/// Functions

	// Gets the current axis values of all bound keys.
	inline float GetValue() const
	{
		float Result{ 0.0f };
		for (uint i = 0; i < Keys.size(); ++i)
		{
			Result += Keys[i].Axis;
		}
		return TMath::Clamp(-1.0f, 1.0f, Result);
	}
};


// The storage container for an action input.
struct SActionKey
{
public:
	/// Properties

	// A list of keys that are bound to this input.
	std::vector<SActionKeyInfo> Keys;

	// The function to call.
	std::function<void(EInputMode)> Function;


	/// Constructors

	// Constructor, Default.
	SActionKey() {}

	// Constructor, Initiates the input with a bound function.
	SActionKey(std::function<void(EInputMode)> Delegate)
		:Function{ Delegate }
	{}
};


// Manages all the bound inputs in the game.
// Note: Functions must be added to the inputs in order for them to work.
// Note: Functions are bound as shown:
// std::bind(&ClassName::FunctionName, this, std::placeholders::_1);
class CInputManager
{
private:
	/// Properties

	// TODO: Remove?
	// Allows the bound inputs to be detected.
	//bool Enable{ true };

	// A reference to the current message.
	MSG Message;

	IDirectInput8* Input;

	IDirectInputDevice8* KeyboardDevice;


	// Determines if control is currently being pressed.
	bool ControlPressed{ false };

	// Determines if shift is currently being pressed.
	bool ShiftPressed{ false };

	// A list of all the axis bound keys.
	std::map<std::string, SAxisKey> AxisBinds;

	// A list of all the action bound keys.
	std::map<std::string, SActionKey> ActionBinds;


public:
	/// Constructors

	// Constructor, Default.
	CInputManager(class CWindow* Window);

	// Destructor.
	~CInputManager();


	/// Functions

	// Updates the current event and updates all inputs.
	void Update();

	// Binds a key to an axis input to a specified function.
	// @param Name - The key type used to get the input.
	// @param Key - The key button used to bind to the input.
	// @param Delegate - The function this key will call (Note: If this is a second bound key to the same name, this is ignored).
	// @param Axis - The value this input will output to the function when passed.
	// @param UseControl - Should the key require control to be held.
	// @param UseShift - Should the key require shift to be held.
	void BindAxis(std::string Name, uint Key, std::function<void(float)> Delegate, float Axis = 1.0f, bool UseControl = false, bool UseShift = false);

	// Binds a key to an axis input to a specified function.
	// @param Name - The key type used to get the input.
	// @param Key - The key button used to bind to the input.
	// @param Axis - The value this input will output to the function when passed.
	// @param UseControl - Should the key require control to be held.
	// @param UseShift - Should the key require shift to be held.
	void BindAxis(std::string Name, uint Key, float Axis = 1.0f, bool UseControl = false, bool UseShift = false);

	// Binds a key to an action input to a specified function.
	// @param Name - The key type used to get the input.
	// @param InputMode - The mode this input uses to call the bound function.
	// @param Key - The key button used to bind to the input.
	// @param Delegate - The function this key will call (Note: If this is a second bound key to the same name, this is ignored).
	// @param UseControl - Should the key require control to be held.
	// @param UseShift - Should the key require shift to be held.
	void BindAction(std::string Name, EInputMode InputMode, uint Key, std::function<void(EInputMode)> Delegate, bool UseControl = false, bool UseShift = false);

	// Binds a key to an action input to a specified function.
	// @param Name - The key type used to get the input.
	// @param InputMode - The mode this input uses to call the bound function.
	// @param Key - The key button used to bind to the input.
	// @param UseControl - Should the key require control to be held.
	// @param UseShift - Should the key require shift to be held.
	void BindAction(std::string Name, EInputMode InputMode, uint Key, bool UseControl = false, bool UseShift = false);

	// Binds a key to an action input to a specified function.
	// The key is read from a file input.
	// @param Name - The key type used to get the input.
	// @param InputMode - The mode this input uses to call the bound function.
	// @param Data = The key data read from a file.
	// @param Delegate - The function this key will call (Note: If this is a second bound key to the same name, this is ignored).
	//void BindAction(std::string Name, EInputMode InputMode, SInputData InputData, std::function<void(float)> Delegate);

private:

	// Calls all the axis input's bound functions.
	void AxisUpdate();
	
	// Checks if the axis input is pressed (includes the control / shift presses).
	// @param Key - The key used to access the input.
	// @param Index - The index the input key is located at.
	// @param KeyDown - Represents if the key is currently being pressed.
	void RegisterAxis(std::string Key, uint Index, bool KeyDown);

	// Checks if the action input is pressed (includes the control / shift presses).
	// @param Key - The key used to access the input.
	// @param Index - The index the input key is located at.
	void RegisterAction(std::string Key, uint Index);

	// Calls the bound function on the specified axis input.
	// @param Key - The key used to access the input.
	// @param Index - The index the input key is located at.
	// @param KeyDown - Represents if the key is currently being pressed.
	void CallAxis(std::string Key, uint Index, bool KeyDown);

	// Calls the bound function on the specified action input.
	// @param Key - The key used to access the input.
	// @param Index - The index the input key is located at.
	void CallAction(std::string Key, uint Index);


public:
	/// Getters

	// Gets a reference of the current message.
	inline MSG GetMsg() const { return Message; }
};