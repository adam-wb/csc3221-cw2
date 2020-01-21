// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include "Bishop.h"

// Initialise Bishop specific properties, then call CircularPiece default constructor
Bishop::Bishop() : CircularPiece() {
	type = Type::BISHOP;
}

// As above, but need to call CircularPiece default constructor AND Piece constructor with starting coordinates
Bishop::Bishop(double initialX, double initialY) : CircularPiece(), Piece(initialX, initialY) {
	type = Type::BISHOP;
}

Bishop::~Bishop() {

}

void Bishop::randomMove(double min, double max) {
	double distance = getRandomDistance(min, max);
	// Gets 0 or 1
	int choice = rand() % 2;
	// Move diagonally
	if (choice == 0) {
		// Move >^ or < and down
		move(xPosition + distance, yPosition + distance);
	}
	else {

		// Move > and down or <^
		move(xPosition + distance, yPosition - distance);
	}
}

// Print Bishop specific information, then call base class method
std::ostream& Bishop::print(std::ostream& outStream) const {
	outStream << "Type: Bishop\n";
	Piece::print(outStream);
	return outStream;
}