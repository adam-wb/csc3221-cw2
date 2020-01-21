// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include <random>

#include "Piece.h"

// Default constructor
Piece::Piece() {
	xPosition = 0;
	yPosition = 0;
}

// Initialise with some starting coordinates
Piece::Piece(double initalX, double initialY) {
	xPosition = initalX;
	yPosition = initialY;
}

Piece::~Piece() {

}

void Piece::move(double x, double y) {
	xPosition = x;
	yPosition = y;
}

double Piece::getXPosition() const {
	return xPosition;
}

double Piece::getYPosition() const {
	return yPosition;
}

double Piece::getRandomDistance(double min, double max) {
	// Gets a double value between min and max
	double d = (double)rand() / RAND_MAX;
	return min + d * (max - min);
}

Piece::Type Piece::getType() const {
	return type;
}

Piece::Shape Piece::getShape() const {
	return shape;
}

std::ostream& Piece::print(std::ostream& outStream) const {
	outStream << "Location : (" << xPosition << "," << yPosition << ")";
	return outStream;
}


// Calls virtual print function for polymorphism
std::ostream& operator<<(std::ostream& outStream, const Piece& piece) {
	return piece.print(outStream);
}	
