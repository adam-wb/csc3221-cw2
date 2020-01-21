// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include "Rook.h"

// Initialise Rook specific properties, then call Piece default constructor
Rook::Rook() : Piece() {
	type = Type::ROOK;
	shape = Shape::SQUARE;
	length = 2;
}

// As above, but call Piece constructor with starting coordinates
Rook::Rook(double initialX, double initialY) : Piece(initialX, initialY) {
	type = Type::ROOK;
	shape = Shape::SQUARE;
	length = 2;
}

Rook::~Rook() {

}

int Rook::getLength() const {
	return length;
}

void Rook::randomMove(double min, double max) {
	double distance = getRandomDistance(min, max);
	// Gets 0 or 1
	int choice = rand() % 2;
	// Move horizontally/vertically
	if (choice == 0) {
		// Move ^ or down
		move(xPosition, yPosition + distance);
	}
	else {
		// Move > or <
		move(xPosition + distance, yPosition);	
	}
}

// Print Rook specific information, then call base class method
std::ostream& Rook::print(std::ostream& outStream) const {
	outStream << "Type: Rook\n";
	Piece::print(outStream);
	return outStream;
}
