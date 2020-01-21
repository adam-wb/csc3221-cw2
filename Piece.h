// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 18/11/2019

#pragma once
#include <iostream>
class Piece {
public:
	// Constructors
	Piece();
	Piece(double initalX, double initialY);

	// Destructor
	virtual ~Piece();

	// Enums
	// Shape of piece
	enum class Shape {
		ROUND,
		SQUARE
	};
	// Type of piece
	enum class Type {
		ROOK,
		BISHOP,
		QUEEN
	};

	// Member Functions
	void move(double x, double y);
	virtual void randomMove(double min, double max) = 0;
	double getXPosition() const;
	double getYPosition() const;
	Type getType() const;
	Shape getShape() const;

	// Output operator
	friend std::ostream& operator<<(std::ostream& outStream, const Piece& piece);
	// Virtual function for output operator to call
	virtual std::ostream& print(std::ostream& outStream) const;

protected:
	// Data representation
	double xPosition, yPosition;
	Type type;
	Shape shape;

	// Member functions
	double getRandomDistance(double min, double max);

};

