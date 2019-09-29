#pragma once
#include "../Graphics/DirectXSetup.h"


class CEngineSetup
{
private:
	/// Properties

	// A reference to the created DirectX Object.
	CDirectXSetup* DirectXSetup;


public:
	/// Constructors
	
	// Constructor, Default.
	CEngineSetup(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CEngineSetup();


	/// Functions

	void MainLoop();
};