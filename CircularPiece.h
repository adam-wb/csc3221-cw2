// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 18/11/2019

#pragma once
#include "Piece.h"
class CircularPiece :
	public virtual Piece
{
public:
	// Constructors
	CircularPiece();

	// Destructor
	virtual ~CircularPiece();

	// Member functions
	int getRadius() const;

protected:
	// Data
	int radius;
};

