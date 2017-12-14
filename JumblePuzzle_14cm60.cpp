#include "JumblePuzzle_14cm60.h"

JumblePuzzle::JumblePuzzle()
{
	jumblePuzzle = NULL;
	row = 0;
	column = 0;
	size = 0;
	direction = 0;
}

JumblePuzzle::JumblePuzzle(const string & hidden, const string & difficulty)
{
	srand(time(0));
	int dir = rand() % 4;
	string dirPossible = "nesw";
	direction = dirPossible[dir];

	int length = hidden.length();
	if (length < 3 || length > 10) {
		throw BadJumbleException("Incorrect word size, should be between 3 and 10 letters long.");
	}

	if (difficulty == "easy") {
		size = 2 * length;
	}
	else if (difficulty == "medium") {
		size = 3 * length;
	}
	else if (difficulty == "hard") {
		size = 4 * length;
	}
	else {
		throw BadJumbleException("Difficulty: " + difficulty + "  Invalid. \nDifficulty must be \"easy\", \"medium\", or \"hard\"");
	}

	
	jumblePuzzle = new char*[size];

	for (int i = 0; i<size; i++)
		jumblePuzzle[i] = new char[size];
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++)
			jumblePuzzle[i][j] = rand() % 26 + 'a';
	}
	bool wordFit = false;
	do {
		row = rand() % (size - 1);
		column = rand() % (size - 1);
		if (dir == 0 && (row - length)>0) {
			wordFit = true;
			for (int i = 0; i < length; i++) {
				jumblePuzzle[row - i][column] = hidden[i];
			}
		}
		else if (dir == 2 && (row + length)<size) {
			wordFit = true;
			for (int i = 0; i < length; i++) {
				jumblePuzzle[row + i][column] = hidden[i];
			}
		}
		else if (dir == 1 && (column + length)<size) {
			wordFit = true;
			for (int i = 0; i < length; i++) {
				jumblePuzzle[row][column + i] = hidden[i];
			}
		}
		else if (dir == 3 && (row - length)>0) {
			wordFit = true;
			for (int i = 0; i < length; i++) {
				jumblePuzzle[row][column-i] = hidden[i];
			}
		}

	} while (!wordFit);
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle & puzzle)
{
	direction = puzzle.getDirection();
	size = puzzle.getSize();
	row = puzzle.getRowPos();
	column = puzzle.getColPos();
	jumblePuzzle = puzzle.getJumble();
}

JumblePuzzle::~JumblePuzzle()
{
	for (int i = 0; i < size; i++) {
		delete[] jumblePuzzle[i];
	}
	delete[] jumblePuzzle;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& puzzle)
{
	if (this != &puzzle) {
		for (int i = size - 1; i >= 0; i--) {
			delete[] jumblePuzzle[i];
		}
		delete[] jumblePuzzle;

		direction = puzzle.getDirection();
		size = puzzle.getSize();
		row = puzzle.getRowPos();
		column = puzzle.getColPos();
		if (puzzle.getJumble()) {
			jumblePuzzle = new char*[size];
			for (int i = 0; i < size; i++)
				jumblePuzzle[i] = new char[size];
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++)
					jumblePuzzle[i][j] = puzzle.getJumble()[i][j];
			}
		}
	}
	return *this;
}

BadJumbleException::BadJumbleException(const string & msg)
{
	message = msg + '\n';
}

string BadJumbleException::what() const
{
	return message;
}

char ** JumblePuzzle::getJumble() const
{
	char** newJumble = new char*[size];
	for (int i = 0; i < size; i++)
		newJumble[i] = new char[size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			newJumble[i][j] = jumblePuzzle[i][j];
	}
	return newJumble;
}

int JumblePuzzle::getSize() const
{
	return size;
}

int JumblePuzzle::getRowPos() const
{
	return row;
}

int JumblePuzzle::getColPos() const
{
	return column;
}

char JumblePuzzle::getDirection() const
{
	return direction;
}
