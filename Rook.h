// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 18/11/2019

#pragma once
#include "Piece.h"
class Rook :
	public virtual Piece
{
public:
	// Constructors
	Rook();
	Rook(double initialX, double initialY);

	// Destructor
	virtual ~Rook();

	// Member Functions
	int getLength() const;
	virtual void randomMove(double min, double max);
	virtual std::ostream& print(std::ostream& outStream) const;

private:
	// Data representation
	int length;
};

