#ifndef LRUBUFFERPOOL_H
#define LRUBUFFERPOOL_H

#include "BufferPoolADT.h"
#include "fstream"
#include "constants.h"
#include "BufferBlock.h"



class LRUBufferpool : public BufferPoolADT
{
private:
	int blknum,
		blksize;
	char * data;
	BufferBlock* blocks;
	fstream input;
	void shift(int a)
	{
		BufferBlock temp = blocks[a];
		for (int i = a; i > 0; i--)
		{
			blocks[i] = blocks[(i - 1)];
		}

		blocks[0] = temp;

	}

public:
	LRUBufferpool() {}
	LRUBufferpool(string filename, int poolSize = 5, int blockSize = 4096)
	{

		blknum = poolSize;
		blksize = blockSize;
		blocks = new BufferBlock[poolSize];
		data = new char[blockSize];

		input.open(filename.c_str(), fstream::in | fstream::binary);
		input.seekg(0, fstream::beg);
		for (int i = 0; i < poolSize; i++)
		{
			input.read(data, blockSize);
			blocks[i].setBlock(data);
			blocks[i].setID(i);
		}


	}
	~LRUBufferpool()
	{
		input.close();
	}


	void getBytes(char* space, int sz, int pos)
	{
		int locator = pos / (blksize);
		int spos = pos % (blksize);
		bool found = false;
		for (int i = 0; i < blknum; i++)
		{
			if (blocks[i].getID() == locator)
			{
				found = true;
				blocks[i].getData(spos, sz, space);
				shift(i);
				break;
			}
		}
		if (found == false)
		{
			input.seekg(blksize*locator);
			input.read(data, blksize);
			blocks[(blknum - 1)].setBlock(data);
			blocks[blknum - 1].getData(spos, sz, space);
			blocks[blknum - 1].setID(locator);
			shift((blknum - 1));

		}

	}


	void printBufferBlockOrder()
	{
		cout << "My Buffer block order from most recently used to LRU is: " << endl;
		for (int i = 0; i < blknum; i++)
		{
			cout << blocks[i].getID() << ", ";
		}
		cout << endl;

	}



	int getLRUBlockID()
	{

		return blocks[4].getID();
	}
};

#endif