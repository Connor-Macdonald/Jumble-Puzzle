#pragma once

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class BadJumbleException
{
public:
	BadJumbleException(const string& msg);
	string what() const;

private:
	string message;
};

class JumblePuzzle
{
public:
	// Default constructor
	JumblePuzzle();
	// Constructor to build puzzle based on hidden and difficulty
	JumblePuzzle(const string& hidden, const string& difficulty);
	// Deep copy of puzzle
	JumblePuzzle(const JumblePuzzle& puzzle);

	// Deconstructor
	virtual ~JumblePuzzle();

	// Deep copy using equals operator
	JumblePuzzle& operator=(const JumblePuzzle& puzzle);

	// Pointer to copy of puzzle
	char** getJumble() const; 
	// Size of puzzle
	int getSize() const; 
	// Start row of hidden word
	int getRowPos() const; 
	// Start column of hidden word
	int getColPos() const; 
	// Direction (n,e,s,w) of hidden word
	char getDirection() const;

private:
	char** jumblePuzzle;
	int size;
	int row;
	int column;
	char direction; 
};
