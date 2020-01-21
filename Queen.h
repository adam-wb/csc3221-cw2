#pragma once
#include "CircularPiece.h"
class Queen :
	public virtual CircularPiece
{
public:
	// Constructors
	Queen();
	Queen(double initialX, double initialY);

	// Destructor
	virtual ~Queen();

	virtual void randomMove(double min, double max);
	std::ostream& print(std::ostream& outStream) const;

};

