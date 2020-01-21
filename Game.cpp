// Adam Barron
// 160212899
// CSC3221 Project 2 - Ultimate Chess
// 25/11/2019

#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"

#include <vector>
#include <cmath>
#include <ctime>
#include <iterator>

using namespace std;

// Global variables
// Side length of the grid
const int GRID_EDGE_LENGTH = 10;
// Maximum distance a piece can move per turn
const int MAX_MOVE_DISTANCE = 1;
// Number of moves each piece makes
const int NUM_ITERS = 100;
// Vector to store pieces
vector<Piece*> pieces;
// Capture counts for each piece type
int rookCaptures = 0;
int bishopCaptures = 0;
int queenCaptures = 0;

// Implicit function declarations
void movePieces();
bool collision(Piece* p);
bool collisionTypeDecider(Piece* p1, Piece* p2);
bool collisionSquareSquare(const Rook* p1, const Rook* p2);
bool collisionCircleCircle(const CircularPiece* p1, const CircularPiece* p2);
bool collisionSquareCircle(const Rook* p1, const CircularPiece* p2);
void updateScores(const Piece* p);

// Create and initialise pieces, and run the core game loop
int main() {
	// Game parameters check
	if (NUM_ITERS < 1)
		throw invalid_argument("Need to run for at least one iteration");
	if (GRID_EDGE_LENGTH <= 0)
		throw invalid_argument("Grid length must be greater than 0");

	// Seed rng for this game instance
	srand(time(NULL));

	// Initialise pieces w/ different coordinates
	// Randomly generate integer coordinates around the grid
	// Number of pieces
	const int NUM_PIECES = 15;
	int coordArrayX [NUM_PIECES];
	int coordArrayY [NUM_PIECES];
	for (int i = 0; i < NUM_PIECES; i++) {
		coordArrayX[i] = rand() % ((2 * GRID_EDGE_LENGTH) + 1) + (-GRID_EDGE_LENGTH);
		coordArrayY[i] = rand() % ((2 * GRID_EDGE_LENGTH) + 1) + (-GRID_EDGE_LENGTH);
	}

	// 5 rooks
	Piece* r1 = new Rook(coordArrayX[0], coordArrayY[0]);
	Piece* r2 = new Rook(coordArrayX[1], coordArrayY[1]);
	Piece* r3 = new Rook(coordArrayX[2], coordArrayY[2]);
	Piece* r4 = new Rook(coordArrayX[3], coordArrayY[3]);
	Piece* r5 = new Rook(coordArrayX[4], coordArrayY[4]);

	// 5 bishops
	Piece* b1 = new Bishop(coordArrayX[5], coordArrayY[5]);
	Piece* b2 = new Bishop(coordArrayX[6], coordArrayY[6]);
	Piece* b3 = new Bishop(coordArrayX[7], coordArrayY[7]);
	Piece* b4 = new Bishop(coordArrayX[8], coordArrayY[8]);
	Piece* b5 = new Bishop(coordArrayX[9], coordArrayY[9]);

	// 5 queens
	Piece* q1 = new Queen(coordArrayX[10], coordArrayY[10]);
	Piece* q2 = new Queen(coordArrayX[11], coordArrayY[11]);
	Piece* q3 = new Queen(coordArrayX[12], coordArrayY[12]);
	Piece* q4 = new Queen(coordArrayX[13], coordArrayY[13]);
	Piece* q5 = new Queen(coordArrayX[14], coordArrayY[14]);

	// Add all pieces to vector
	pieces.push_back(r1);
	pieces.push_back(r2);
	pieces.push_back(r3);
	pieces.push_back(r4);
	pieces.push_back(r5);
	pieces.push_back(b1);
	pieces.push_back(b2);
	pieces.push_back(b3);
	pieces.push_back(b4);
	pieces.push_back(b5);
	pieces.push_back(q1);
	pieces.push_back(q2);
	pieces.push_back(q3);
	pieces.push_back(q4);
	pieces.push_back(q5);

	////DEBUG: Uncomment to see starting positions
	//cout << "STARTING POSITIONS" << endl;
	//for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++) {
	//	cout << **it << endl;
	//}

	// Core game loop
	cout << "GAME STARTED!" << endl;

	for (int i = 0; i < NUM_ITERS; i++) {
		if (pieces.size() == 1) {
			// End the game if only one piece remains
			cout << "Only one piece remaining!" << endl;
			break;
		}
		movePieces();

		//// DEBUG: Uncomment for pieces remaining and their locations after each iteration
		//cout << "ITERATION " << i+1 << " REMAINING PIECES" << endl;
		//for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++) {
		//	cout << **it << endl;
		//}

	}

	// Game over
	cout << "GAME OVER!" << endl;;
	// Print pieces
	for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++) {
		cout << "Remaining pieces:" << endl 
			<< **it << endl;
	}
	// Print scores
	cout << "Final scores:" << endl
		<< "Rook captures: " << rookCaptures << endl
		<< "Bishop captures: " << bishopCaptures << endl
		<< "Queen captures: " << queenCaptures << endl;

	return 0;
}

// Move all the pieces on the board
void movePieces() {
	for (int i = 0; i < pieces.size(); i++) {
		// Move piece a random distance
		(pieces[i])->randomMove(-MAX_MOVE_DISTANCE, MAX_MOVE_DISTANCE);

		// If movement is out of bounds, move in the opposite direction
		if (pieces[i]->getXPosition() > GRID_EDGE_LENGTH) {
			pieces[i]->move(GRID_EDGE_LENGTH - (pieces[i]->getXPosition() - GRID_EDGE_LENGTH), pieces[i]->getYPosition());
		}
		else if (pieces[i]->getXPosition() < -GRID_EDGE_LENGTH) {
			pieces[i]->move(-GRID_EDGE_LENGTH - (pieces[i]->getXPosition() + GRID_EDGE_LENGTH), pieces[i]->getYPosition());
		}
		if (pieces[i]->getYPosition() > GRID_EDGE_LENGTH) {
			pieces[i]->move(pieces[i]->getXPosition(), GRID_EDGE_LENGTH - (pieces[i]->getYPosition() - GRID_EDGE_LENGTH));
		}
		else if (pieces[i]->getYPosition() < -GRID_EDGE_LENGTH) {
			pieces[i]->move(pieces[i]->getXPosition(), -GRID_EDGE_LENGTH - (pieces[i]->getXPosition() + GRID_EDGE_LENGTH));
		}

		// Check for collisions
		if (collision(pieces[i]))
			// Deleting from the vector moves elements down to fill the gap
			// and reduces pieces.size() by 1
			// Therefore need to increment index to make sure no piece moves twice
			i++;
	}
}

// Check for and resolve any collisions
bool collision(Piece* p) {
	// Minimum distance to investigate collision
	const int CHECK_THRESHOLD = 4;
	// Track index for removing pieces after a collision
	int currentIndex = 0;
	for (vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++) {
		// Cannot collide with self
		if (p == *it)
			return false;
		// If pieces are close together
		if (abs(p->getXPosition() - (*it)->getXPosition()) <= CHECK_THRESHOLD && abs(p->getYPosition() - (*it)->getYPosition()) <= CHECK_THRESHOLD) {
			// Check if they have collided
			if (collisionTypeDecider(p, *it)) {
				cout << "Collision detected! " << endl << *p << endl << "Collided with" << endl << **it << endl;
				// Increment the appropriate score counter
				updateScores(p);
				// Remove the piece we collided with from the board
				// Memory management
				// Delete the object
				delete* it;
				// Dereference the pointer
				*it = nullptr;
				// Remove from the vector
				pieces.erase(pieces.begin() + currentIndex);
				return true;
			}
		}
		currentIndex++;
	}
	return false;
}

// Work out which collision detection logic to use
bool collisionTypeDecider(Piece* p1, Piece* p2) {
	// If piece 1 is square
	if (p1->getShape() == Piece::Shape::SQUARE) {
		// If piece 2 is square
		if (p2->getShape() == Piece::Shape::SQUARE) {
			return collisionSquareSquare(dynamic_cast<Rook*>(p1), dynamic_cast<Rook*>(p2));
		}
		// Piece 2 is circular
		else {
			return collisionSquareCircle(dynamic_cast<Rook*>(p1), dynamic_cast<CircularPiece*>(p2));
		}
	}
	// Piece 1 is circular
	// If piece 2 is square
	else if (p2->getShape() == Piece::Shape::SQUARE) {
		return collisionSquareCircle(dynamic_cast<Rook*>(p2), dynamic_cast<CircularPiece*>(p1));
	}
	// Piece 2 is circular
	else {
		return collisionCircleCircle(dynamic_cast<CircularPiece*>(p1), dynamic_cast<CircularPiece*>(p2));
	}
}

// Resolve a collision between two squares
bool collisionSquareSquare(const Rook* p1, const Rook* p2) {

	//// DEBUG: Uncomment to see type of collision being investigated
	//cout << "SQUARE-SQUARE COLLISION CHECK..." << endl;

	// If any edges overlap, collision
	return (p1->getXPosition() < p2->getXPosition() + p2->getLength() &&
		p1->getXPosition() + p1->getLength() > p2->getXPosition() &&
		p1->getYPosition() < p2->getYPosition() + p2->getLength() &&
		p1->getYPosition() + p1->getLength() > p2->getYPosition());
}

// Resolve a collision between two circles
bool collisionCircleCircle(const CircularPiece* p1, const CircularPiece* p2) {

	//// DEBUG: Uncomment to see type of collision being investigated
	//cout << "CIRCLE-CIRCLE COLLISION CHECK..." << endl;
	
	// If distances between the two centres is less than the radii, collision
	return ((pow(p2->getXPosition() - p1->getXPosition(), 2)) + (pow(p1->getYPosition() - p2->getYPosition(), 2)) 
		<= pow(p1->getRadius() + p2->getRadius(), 2));
}

// Resolve a collision between a square and a circle
bool collisionSquareCircle(const Rook* p1, const CircularPiece* p2) {

	//// DEBUG: Uncomment to see type of collision being investigated
	//cout << "SQUARE-CIRCLE COLLISION CHECK..." << endl;

	// Find two edges of square closest to circle
	double closestX = p2->getXPosition();
	double closestY = p2->getYPosition();
	// Left
	if (p1->getXPosition() > p2->getXPosition()) {
		closestX = p1->getXPosition();
	}
	// Right
	else if (p1->getXPosition() + p1->getLength() < p2->getXPosition()) {
		closestX = p1->getXPosition() + p1->getLength();
	}
	// Top
	if (p1->getYPosition() > p2->getYPosition()) {
		closestY = p1->getYPosition();
	}
	// Bottom
	else if (p1->getYPosition() + p1->getLength() < p2->getYPosition()) {
		closestY = p1->getYPosition() + p1->getLength();
	}
	// Calculate distance from these edges to the circle
	double distance = sqrt((pow((p2->getXPosition() - closestX), 2)) + pow((p2->getYPosition() - closestY), 2));
	// Check if there was a collision
	if (distance <= p2->getRadius())
		return true;
	return false;
}

// Update the score counter for the type of piece that made a capture
void updateScores(const Piece* p) {
	switch (p->getType()) {
		case Piece::Type::ROOK : 
			rookCaptures++;
			break;
		case Piece::Type::BISHOP : 
			bishopCaptures++;
			break;
		case Piece::Type::QUEEN :
			queenCaptures++;
			break;
	}
}