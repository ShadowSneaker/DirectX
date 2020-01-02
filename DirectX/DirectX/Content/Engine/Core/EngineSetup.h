#pragma once
#include "../World/World.h"



// Initiates the core engine systems.
class CEngineSetup
{
private:
	/// Properties

	// A reference to the created DirectX Object.
	//CDirectXSetup* DirectXSetup;

	// A reference to the world.
	CWorld* World;



public:
	/// Constructors
	
	// Constructor, Default.
	CEngineSetup(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CEngineSetup();



	/// Functions

	// Startups the game.
	void Startup();
};