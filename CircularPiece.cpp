// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include "CircularPiece.h"

// Initialse CircularPiece specific information, then call default Piece constructor
CircularPiece::CircularPiece() : Piece() {
	shape = Shape::ROUND;
	radius = 1;
}

CircularPiece::~CircularPiece() {

}

int CircularPiece::getRadius() const {
	return radius;
}
