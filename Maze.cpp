#include "Maze.h"
#include <iostream>
#include <fstream>
#include <vector>


Maze::Maze()
{
	// Making a test maze by hand to make testing easy without giving away the extra credit of the maze maker.

	mStart = new Cell;
	mStart->mNorth = new Cell;
	mStart->mNorth->mNorth = new Cell;
	mStart->mEast = new Cell;
	mStart->mEast->mEast = new Cell;
	mStart->mEast->mEast->mNorth = new Cell;
	mStart->mEast->mEast->mNorth->mNorth = new Cell;
	mStart->mEast->mEast->mNorth->mNorth->mIsExit = false;
	// This is the big U I drew on the board.
}

Maze::Maze(std::string tFilePath)
{
	std::string rawText = "";
	std::string lineIn = "";
	mWidth = 0;
	mLength = 0;
	std::ifstream inFile;
	/////////////////////////////////
	inFile.open(tFilePath.c_str());
	if (inFile)
	{
		while (!inFile.eof())
		{
			std::getline(inFile, lineIn);
			rawText += lineIn;
			mLength++;

		}
		mWidth = lineIn.length();
		mCellMatrix = std::vector<std::vector<Cell*>>(mLength, std::vector<Cell*>(mWidth, nullptr));
		int row = 0;
		int col = 0;
		for (int i = 0; i < rawText.size(); i++)
		{ // Create Nodes
			if (!(rawText[i] == ' ' || rawText[i] == 'S' || rawText[i] == 'E')) continue;
			if (mWidth > 0) row = i / mWidth;
			col = i % mWidth;
			if (mCellMatrix[row][col] == nullptr) mCellMatrix[row][col] = new Cell();
			if (rawText[i] == 'S') mStart = mCellMatrix[row][col];
			if (rawText[i] == 'E') mCellMatrix[row][col]->mIsExit = true;
		}
		for (row = 0; row < mLength; row++)
		{ // Link nodes and print nodes to console
			for (col = 0; col < mWidth; col++)
			{
				if (mCellMatrix[row][col] == nullptr)
				{
					std::cout << "||";
					continue;
				}
				else if (mCellMatrix[row][col]->mIsExit) std::cout << "EE";
				else std::cout << "  ";
				if (row - 1 >= 0 && mCellMatrix[row - 1][col] != nullptr)//North in bounds
				{
					mCellMatrix[row][col]->mNorth = mCellMatrix[row - 1][col];
				}
				if (row + 1 < mLength && mCellMatrix[row + 1][col] != nullptr)//South in bounds
				{
					mCellMatrix[row][col]->mSouth = mCellMatrix[row + 1][col];
				}
				if (col + 1 < mWidth && mCellMatrix[row][col + 1] != nullptr)//East in bounds
				{
					mCellMatrix[row][col]->mEast = mCellMatrix[row][col + 1];
				}
				if (col - 1 >= 0 && mCellMatrix[row][col - 1] != nullptr)//West in bounds
				{
					mCellMatrix[row][col]->mWest = mCellMatrix[row][col - 1];
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		
	}
	else std::cout << "File Not Found!";
	if (inFile) inFile.close();
}


Maze::~Maze()
{
	for (int row = 0; row < mLength; row++)
	{
		for (int col = 0; col < mWidth; col++)
		{
			if (mCellMatrix[row][col] == nullptr)
			{
				continue;
			}
			delete mCellMatrix[row][col];
		}
	}
}

bool Maze::MazeRecursive(Maze::Cell* tCurrent)
{
	if (tCurrent == nullptr || tCurrent->mProcessed) return false;
	tCurrent->mProcessed = true;
	if (tCurrent->mIsExit
		|| MazeRecursive(tCurrent->mNorth)
		|| MazeRecursive(tCurrent->mSouth)
		|| MazeRecursive(tCurrent->mEast)
		|| MazeRecursive(tCurrent->mWest))
	{
		tCurrent->mOnPath = true;
		return true;
	}
}

void Maze::SolveMaze()
{

	if (MazeRecursive(mStart)) 
	{
		for (int row = 0; row < mLength; row++)
		{
			for (int col = 0; col < mWidth; col++)
			{
				if (mCellMatrix[row][col] == nullptr)
				{
					std::cout << "||";
					continue;
				}
				else if (mCellMatrix[row][col]->mIsExit) std::cout << "EE";
				else if (mCellMatrix[row][col]->mOnPath) std::cout << "~~";
				else std::cout << "  ";
				mCellMatrix[row][col]->mProcessed = false;
			}
			std::cout << std::endl;
		}
		std::cout << "Exit Found! Path:" << std::endl << std::endl;
		Cell* tTempCellPtr = mStart;
		while (!tTempCellPtr->mIsExit)
		{
			if (tTempCellPtr->mNorth != nullptr && tTempCellPtr->mNorth->mOnPath && !tTempCellPtr->mNorth->mProcessed)
			{
				std::cout << "N ";
				tTempCellPtr->mProcessed = true;
				tTempCellPtr = tTempCellPtr->mNorth;
				continue;
			}
			if (tTempCellPtr->mSouth != nullptr && tTempCellPtr->mSouth->mOnPath && !tTempCellPtr->mSouth->mProcessed)
			{
				std::cout << "S ";
				tTempCellPtr->mProcessed = true;
				tTempCellPtr = tTempCellPtr->mSouth;
				continue;
			}
			if (tTempCellPtr->mEast != nullptr && tTempCellPtr->mEast->mOnPath && !tTempCellPtr->mEast->mProcessed)
			{
				std::cout << "E ";
				tTempCellPtr->mProcessed = true;
				tTempCellPtr = tTempCellPtr->mEast;
				continue;
			}
			if (tTempCellPtr->mWest != nullptr && tTempCellPtr->mWest->mOnPath && !tTempCellPtr->mWest->mProcessed)
			{
				std::cout << "W ";
				tTempCellPtr->mProcessed = true;
				tTempCellPtr = tTempCellPtr->mWest;
				continue;
			}
		}
	}
	else std::cout << "No Exit Found";
	
}