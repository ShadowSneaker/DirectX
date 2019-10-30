#pragma once
#include "../World/World.h"


class CEngineSetup
{
private:
	/// Properties

	// A reference to the created DirectX Object.
	//CDirectXSetup* DirectXSetup;

	CWorld* World;


public:
	/// Constructors
	
	// Constructor, Default.
	CEngineSetup(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CEngineSetup();


	/// Functions

	void Startup();
};