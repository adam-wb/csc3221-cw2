// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 18/11/2019

#pragma once
#include "CircularPiece.h"
class Bishop :
	public virtual CircularPiece
{
public:
	// Constructors
	Bishop();
	Bishop(double initialX, double initialY);

	// Destructors
	virtual ~Bishop();

	// Member functions
	virtual void randomMove(double min, double max);
	virtual std::ostream& print(std::ostream& outStream) const;

};

