#pragma once
#include "../../Math/MathValues.h"


// Holes the information to display a colour.
struct SColour
{
public:
	/// Properties

	// The colour's red property.
	float R;

	// The colour's green property.
	float G;

	// The colour's blue property.
	float B;

	// The colour's alpha property.
	float A;



public:
	/// Constructors

	// Constructor, Default.
	SColour()
		:R{ 1.0f }, G{ 1.0f }, B{ 1.0f }, A{ 1.0f }
	{}

	// Constructor, Initiates all components.
	SColour(float InR, float InG, float InB, float InA = 1.0f)
		:R{ InG }, G{ InG }, B{ InB }, A{ InA }
	{}


	/// Statics

	// Returns the colour red.
	static inline SColour Red() { return SColour{ 1.0f, 0.0f, 0.0f }; }

	// Returns the colour green.
	static inline SColour Green() { return SColour{ 0.0f, 1.0f, 0.0f }; }

	// Returns the colour blue.
	static inline SColour Blue() { return SColour{ 0.0f, 0.0f, 1.0f }; }

	// Returns the colour purple.
	static inline SColour Purple() { return SColour{ 0.5f, 0.0f, 1.0f }; }

	// Returns the colour magenta.
	static inline SColour Magenta() { return SColour{ 1.0f, 0.0f, 1.0f }; }

	// Returns the colour yellow.
	static inline SColour Yellow() { return SColour{ 1.0f, 1.0f, 0.0f }; }

	// Returns the colour black.
	static inline SColour Black() { return SColour{ 0.0f, 0.0f, 0.0f }; }

	// Returns the colour dark gray.
	static inline SColour DarkGray() { return SColour{ 0.2f, 0.2f, 0.2f }; }

	// Returns the colour gray.
	static inline SColour Gray() { return SColour{ 0.5f, 0.5f, 0.5f }; }

	// Returns the colour silver.
	static inline SColour Silver() { return SColour{ 0.9f, 0.9f, 0.9f }; }

	// Returns the colour white.
	static inline SColour White() { return SColour{ 1.0f, 1.0f, 1.0f }; }

	// Returns the colour cyan.
	static inline SColour Cyan() { return SColour{ 0.0f, 1.0f, 1.0f }; }

	// Returns the colour orange.
	static inline SColour Orange() { return SColour{ 1.0f, 0.5f, 0.0f }; }

	// Returns the colour pink.
	static inline SColour Pink() { return SColour{ 1.0f, 0.8f, 0.9f }; }

	// Returns the colour brown.
	static inline SColour Brown() { return SColour{ 0.4f, 0.2f, 0.0f }; }

	// Returns the colour lime.
	static inline SColour Lime() { return SColour{ 0.0f, 1.0f, 0.5f }; }

	// Returns the colour gold.
	static inline SColour Gold() { return SColour{ 0.8f, 0.8f, 0.0f }; }

	// Returns the colour clear.
	static inline SColour Clear() { return SColour{ 1.0f, 1.0f, 1.0f, 0.5f }; }

};