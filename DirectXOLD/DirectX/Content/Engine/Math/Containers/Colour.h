#pragma once
#include "../MathValues.h"


// Holds the information for a standard colour.
struct SColour
{
public:
	/// Properties

	// The colour's red property.
	uint8 R;

	// The colour's green property.
	uint8 G;

	// The colour's blue property.
	uint8 B;

	// The colour's alpha property.
	uint8 A;


public:
	/// Constructors

	// Constructor, Default.
	SColour()
		:R{ 0 }, G{ 0 }, B{ 0 }, A{ 0 }
	{}

	// Constructor, Initialises every component.
	SColour(uint8 InR, uint8 InG, uint8 InB, uint8 InA = 1)
		:R{ InR }, G{ InG }, B{ InB }, A{ InA }
	{}


	/// Statics

	// Returns the colour red.
	static inline SColour Red() { return SColour{ 255, 0, 0 }; }

	// Returns the colour green.
	static inline SColour Green() { return SColour{ 0, 255, 0 }; }

	// Returns the colour blue.
	static inline SColour Blue() { return SColour{ 0, 0, 255 }; }

	// Returns the colour purple.
	static inline SColour Purple() { return SColour{ 128, 0, 128 }; }

	// Returns the colour magenta.
	static inline SColour Magenta() { return SColour{ 255, 0, 255 }; }

	// Returns the colour yellow.
	static inline SColour Yellow() { return SColour{ 255, 255, 0 }; }

	// Returns the colour black
	static inline SColour Black() { return SColour{ 0, 0, 0 }; }

	// Returns the colour white
	static inline SColour White() { return SColour{ 255, 255, 255 }; }

	// Returns the colour cyan.
	static inline SColour Cyan() { return SColour{ 0, 200, 255 }; }

	// Returns the colour orange.
	static inline SColour Orange() { return SColour{ 255, 128, 0 }; }

	// Returns the colour pink.
	static inline SColour Pink() { return SColour{ 255, 128, 255 }; }
};