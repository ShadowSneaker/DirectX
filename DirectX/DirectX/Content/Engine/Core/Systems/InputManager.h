#pragma once
#include "../../Math/MathStatics.h"
#include "FileReader.h"

#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <Windows.h>

#include <vector>
#include <functional>
#include <map>
#include <thread>
#include <mutex>


// A list of all valid key inputs.
enum EKey
{
	IE_Escape = 0x01,
	IE_1 = 0x02,
	IE_2 = 0x03,
	IE_3 = 0x04,
	IE_4 = 0x05,
	IE_5 = 0x06,
	IE_6 = 0x07,
	IE_7 = 0x08,
	IE_8 = 0x09,
	IE_9 = 0x0A,
	IE_0 = 0x0B,

	IE_Minus  = 0x0C,
	IE_Equals = 0x0D,
	IE_Back   = 0x0E,
	IE_Tab    = 0x0F,

	IE_Q = 0x10,
	IE_W = 0x11,
	IE_E = 0x12,
	IE_R = 0x13,
	IE_T = 0x14,
	IE_Y = 0x15,
	IE_U = 0x16,
	IE_I = 0x17,
	IE_O = 0x18,
	IE_P = 0x19,

	IE_LBracket = 0x1A,
	IE_RBracket = 0x1B,
	IE_Return   = 0x1C,
	IE_LControl = 0x1D,

	IE_A = 0x1E,
	IE_S = 0x1F,
	IE_D = 0x20,
	IE_F = 0x21,
	IE_G = 0x22,
	IE_H = 0x23,
	IE_J = 0x24,
	IE_K = 0x25,
	IE_L = 0x26,

	IE_Semicolon  = 0x27,
	IE_Apostrophe = 0x28,
	IE_Grave      = 0x29,
	IE_LShift     = 0x2A,
	IE_Backslash  = 0x2B,
	
	IE_Z = 0x2C,
	IE_X = 0x2D,
	IE_C = 0x2E,
	IE_V = 0x2F,
	IE_B = 0x30,
	IE_N = 0x31,
	IE_M = 0x32,

	IE_Comma    = 0x32,
	IE_Period   = 0x34,
	IE_Slash    = 0x35,
	IE_RShift   = 0x36,
	IE_Multiply = 0x37,
	IE_LMenu    = 0x38,
	IE_Space    = 0x39,
	IE_CapsLock = 0x3A,

	IE_F1  = 0x3B,
	IE_F2  = 0x3C,
	IE_F3  = 0x3D,
	IE_F4  = 0x3E,
	IE_F5  = 0x3F,
	IE_F6  = 0x40,
	IE_F7  = 0x41,
	IE_F8  = 0x42,
	IE_F9  = 0x43,
	IE_F10 = 0x44,

	IE_NumLock    = 0x45,
	IE_ScrollLock = 0x46,
	IE_Numpad7    = 0x47,
	IE_Numpad8    = 0x48,
	IE_Numpad9    = 0x49,
	IE_Subtract   = 0x4A,
	IE_Numpad4    = 0x4B,
	IE_Numpad5    = 0x4C,
	IE_Numpad6    = 0x4D,
	IE_Add        = 0x4E,
	IE_Numpad1    = 0x4F,
	IE_Numpad2    = 0x50,
	IE_Numpad3    = 0x51,
	IE_Numpad0    = 0x52,
	IE_Decimal    = 0x53,

	IE_F11 = 0x57,
	IE_F12 = 0x58,
	IE_F13 = 0x64,
	IE_F14 = 0x65,
	IE_F15 = 0x66,

	IE_Kana       = 0x70,
	IE_Convert    = 0x79,
	IE_NonConvert = 0x7B,
	IE_Yen        = 0x7D,

	IE_NumpadEquals = 0x8D,
	IE_Circumflex   = 0x90,
	IE_At		    = 0x91,
	IE_Colon	    = 0x92,
	IE_Underline    = 0x93,
	IE_Kanji        = 0x94,
	IE_Stop         = 0x95,
	IE_AX           = 0x96,
	IE_Unlabeled    = 0x97,
	IE_NumPadEnter  = 0x9C,
	IE_RControl     = 0x9D,
	IE_NumPadComma  = 0xB3,
	IE_Divide       = 0xB5,
	IE_SYSRQ        = 0xB7,
	IE_RMenu        = 0xB8,
	IE_Pause        = 0xC5,
	IE_Home         = 0xC7,
	IE_Up           = 0xC8,
	IE_Prior        = 0xC9,
	IE_Left         = 0xCB,
	IE_Right        = 0XCD,
	IE_End          = 0xCF,
	IE_Down         = 0xD0,
	IE_Next         = 0xD1,
	IE_Insert       = 0xD2,
	IE_Delete       = 0xD3,
	IE_LWin         = 0xDB,
	IE_RWin         = 0xDC,
	IE_Apps         = 0xDD,
	IE_Power        = 0xDE,
	IE_Sleep        = 0xDF,
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
	CInputManager();

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