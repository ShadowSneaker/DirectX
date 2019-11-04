#include "InputManager.h"
#include <debugapi.h>
#include "../../Graphics/Window.h"


CInputManager::CInputManager(class CWindow* Window)
{
	HRESULT HR;
	
	HR = DirectInput8Create(Window->GetHandle(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input, NULL);
	if (FAILED(HR)) DebugBreak();

	HR = Input->CreateDevice(GUID_SysKeyboard, &KeyboardDevice, NULL);
	if (FAILED(HR)) DebugBreak();

	HR = KeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(HR)) DebugBreak();

	HR = KeyboardDevice->SetCooperativeLevel(Window->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(HR)) DebugBreak();

	HR = KeyboardDevice->Acquire();
	if (FAILED(HR)) DebugBreak();
}


CInputManager::~CInputManager()
{
	if (KeyboardDevice)
	{
		KeyboardDevice->Unacquire();
		KeyboardDevice->Release();
	}

	if (Input) Input->Release();
}


void CInputManager::AxisUpdate()
{
	for (auto i = AxisBinds.begin(); i != AxisBinds.end(); ++i)
	{
		i->second.Function(i->second.GetValue());
	}
}


void CInputManager::Update()
{
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}


	HRESULT HR;
	HR = KeyboardDevice->GetDeviceState(sizeof(ActionBinds), &ActionBinds);
	if (FAILED(HR))
	{
		if ((HR == DIERR_INPUTLOST) || (HR == DIERR_NOTACQUIRED))
		{
			KeyboardDevice->Acquire();
		}
	}
	

	if (Message.message == WM_KEYDOWN)
	{
		switch (Message.wParam)
		{
		case VK_LCONTROL:
		case VK_RCONTROL:
			ControlPressed = true;
			break;


		case VK_LSHIFT:
		case VK_RSHIFT:
			ShiftPressed = true;
			break;
		}
	}
	else if (Message.message == WM_KEYUP)
	{
		switch (Message.wParam)
		{
		case VK_LCONTROL:
		case VK_RCONTROL:
			ControlPressed = false;
			break;


		case VK_LSHIFT:
		case VK_RSHIFT:
			ShiftPressed = false;
			break;
		}
	}


	for (auto i = AxisBinds.begin(); i != AxisBinds.end();  ++i)
	{
		for (uint j = 0; j < i->second.Keys.size(); ++j)
		{
			if (Message.message == WM_KEYDOWN)
			{
				if (Message.wParam == i->second.Keys[j].Key)
				{
					RegisterAxis(i->first, j, true);
				}
			}
			else if (Message.message == WM_KEYUP)
			{
				if (Message.wParam == i->second.Keys[j].Key)
				{
					RegisterAxis(i->first, j, false);
				}
			}
		}
	}


	for (auto i = ActionBinds.begin(); i != ActionBinds.end(); ++i)
	{
		for (uint j = 0; j < i->second.Keys.size(); ++j)
		{
			if (Message.message == WM_KEYDOWN)
			{
				if (Message.wParam == i->second.Keys[j].Key)
				{
					RegisterAction(i->first, j);
				}


				switch (i->second.Keys[j].InputMode)
				{
				case EInputMode::Continuous:
				case EInputMode::Toggle:
				case EInputMode::All:
					if (i->second.Keys[j].Pressed)
					{
						i->second.Function(EInputMode::Continuous);
					}
					break;
				}
			}
			else if (Message.message == WM_KEYUP)
			{
				if (Message.wParam == i->second.Keys[j].Key)
				{
					switch (i->second.Keys[j].InputMode)
					{
					case EInputMode::Released:
					case EInputMode::Toggle:
					case EInputMode::All:
						if (i->second.Keys[j].Pressed)
						{
							i->second.Function(EInputMode::Released);
						}
						break;
					}

					i->second.Keys[j].Pressed = false;
				}
			}
		}
	}

	AxisUpdate();
}


void CInputManager::BindAxis(std::string Name, uint Key, std::function<void(float)> Delegate, float Axis, bool UseControl, bool UseShift)
{
	if (!AxisBinds.count(Name))
	{
		AxisBinds.insert(std::pair<std::string, SAxisKey>(Name, SAxisKey{ Delegate }));
	}
	BindAxis(Name, Key, Axis, UseControl, UseShift);
}


void CInputManager::BindAxis(std::string Name, uint Key, float Axis, bool UseControl, bool UseShift)
{
	bool Contains{ false };
	for (uint i = 0; i < AxisBinds[Name].Keys.size(); ++i)
	{
		if (AxisBinds[Name].Keys[i].Key == Key)
		{
			Contains = true;
			break;
		}
	}

	if (!Contains)
	{
		AxisBinds[Name].Keys.push_back(SAxisKeyInfo{ Key, Axis, 0.0f, 1.0f, UseControl, UseShift });
	}
}


void CInputManager::BindAction(std::string Name, EInputMode InputMode, uint Key, std::function<void(EInputMode)> Delegate, bool UseControl, bool UseShift)
{
	if (!ActionBinds.count(Name))
	{
		ActionBinds.insert(std::pair<std::string, SActionKey>(Name, SActionKey{ Delegate }));
	}
	BindAction(Name, InputMode, Key, UseControl, UseShift);
}


void CInputManager::BindAction(std::string Name, EInputMode InputMode, uint Key, bool UseControl, bool UseShift)
{
	ActionBinds[Name].Keys.push_back(SActionKeyInfo{ Key, InputMode, UseControl, UseShift, false });
}


/*void CInputManager::BindAction(std::string Name, EInputMode InputMode, SInputData Data, std::function<void(EInputMode)> Delegate)
{
	uint Key{ GetKeyNameText(Data) };
	if (!ActionBinds.count(Name))
	{
		ActionBinds.insert(std::pair<std::string, SActionKey>(Name, SActionKey{ Delegate }));
	}

	bool Contains{ false };
	for (uint i = 0; i < ActionBinds[Name].Keys.size(); ++i)
	{
		if (ActionBinds[Name].Keys[i].Key == Key)
		{
			Contains = true;
			break;
		}
	}

	if (!Contains)
	{
		ActionBinds[Name].Keys.push_back(SActionKeyInfo{ Key, InputMode, Data.Control, Data.Shift, false });
	}
}*/


void CInputManager::RegisterAxis(std::string Key, uint Index, bool KeyDown)
{
	// If both are on/off.
	if ((AxisBinds[Key].Keys[Index].UseControl == ControlPressed) && (AxisBinds[Key].Keys[Index].UseShift == ShiftPressed))
	{
		CallAxis(Key, Index, KeyDown);
	}
	// If only control on.
	else if ((AxisBinds[Key].Keys[Index].UseControl && ControlPressed) && (!AxisBinds[Key].Keys[Index].UseShift && !ShiftPressed))
	{
		CallAxis(Key, Index, KeyDown);
	}
	// If only shift on.
	else if ((AxisBinds[Key].Keys[Index].UseShift && ShiftPressed) && (!AxisBinds[Key].Keys[Index].UseControl && !ControlPressed))
	{
		CallAxis(Key, Index, KeyDown);
	}
	// If none on.
	else
	{
		CallAxis(Key, Index, false);
	}
}


void CInputManager::RegisterAction(std::string Key, uint Index)
{
	// If both are on/off.
	if ((ActionBinds[Key].Keys[Index].UseControl == ControlPressed) && (ActionBinds[Key].Keys[Index].UseShift == ShiftPressed))
	{
		CallAction(Key, Index);
	}
	// If only control on.
	else if ((ActionBinds[Key].Keys[Index].UseControl && ControlPressed) && (!ActionBinds[Key].Keys[Index].UseShift && !ShiftPressed))
	{
		CallAction(Key, Index);
	}
	// If only shift on.
	else if ((ActionBinds[Key].Keys[Index].UseShift && ShiftPressed) && (!ActionBinds[Key].Keys[Index].UseControl && !ControlPressed))
	{
		CallAction(Key, Index);
	}
	// If none on.
	else
	{
		CallAction(Key, Index);
	}
}


void CInputManager::CallAxis(std::string Key, uint Index, bool KeyDown)
{
	if (KeyDown)
	{
		AxisBinds[Key].Keys[Index].Axis = AxisBinds[Key].Keys[Index].Value;
	}
	else
	{
		AxisBinds[Key].Keys[Index].Axis = 0.0f;
	}
}


void CInputManager::CallAction(std::string Key, uint Index)
{
	switch (ActionBinds[Key].Keys[Index].InputMode)
	{
	case EInputMode::Pressed:
	case EInputMode::Toggle:
	case EInputMode::All:
		if (!ActionBinds[Key].Keys[Index].Pressed)
		{
			ActionBinds[Key].Function(EInputMode::Pressed);
		}
	}
	ActionBinds[Key].Keys[Index].Pressed = true;
}