// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include "Queen.h"

// Initialise queen specific properties, then call Piece default constructor
Queen::Queen() : CircularPiece() {
	type = Type::QUEEN;
}

// As above, but need to call CircularPiece default constructor AND Piece constructor with starting coordinates
Queen::Queen(double initialX, double initialY) : CircularPiece(), Piece(initialX, initialY) {
	type = Type::QUEEN;
}

Queen::~Queen() {

}

void Queen::randomMove(double min, double max) {
	double distance = getRandomDistance(min, max);
	// Gets 0 or 1
	int choice = rand() % 2;
	// Move horizontally/vertically
	if (choice == 0) {
		// See rook movement
		choice = rand() % 2;
		if (choice == 0) {
			// Move ^ or down
			move(xPosition, yPosition + distance);
		}
		else {
			// Move > or <
			move(xPosition + distance, yPosition);
		}
	}
	// Move diagonally
	else {
		// See bishop movement
		choice = rand() % 2;
		if (choice == 0) {
			// Move >^ or < and down
			move(xPosition + distance, yPosition + distance);
		}
		else {
			// Move > and down or <^
			move(xPosition + distance, yPosition - distance);
		}
	}
}

std::ostream& Queen::print(std::ostream& outStream) const {
	outStream << "Type: Queen\n";
	Piece::print(outStream);
	return outStream;
}