#pragma once
#include <stack>
#include <list>
#include <string>
#include <vector>

class Maze
{
public:
	class Cell
	{
		friend Maze;
		Cell* mNorth = nullptr; 					
		Cell* mSouth = nullptr;
		Cell* mEast = nullptr;
		Cell* mWest = nullptr;
		bool mIsExit = false;
		bool mOnPath = false;
		bool mProcessed = false;
								
	};

private:
	bool MazeRecursive(Cell *tCurrent);
	Cell* mStart;
	int mLength;
	int mWidth;
	std::vector<std::vector<Cell*>> mCellMatrix;

public:
	Maze();
	Maze(std::string tFilePath);
	~Maze();
	void SolveMaze();

};


