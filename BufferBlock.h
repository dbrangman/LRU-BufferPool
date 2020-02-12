#ifndef BUFFERBLOCK_H
#define BUFFERBLOCK_H

#include "BufferBlockADT.h"

class BufferBlock : public BufferblockADT
{
private:
	int blockID;
	char* block;
	int blocksz;

public:
	BufferBlock()
	{
		blocksz = BLOCKSIZE;
		block = new char[BLOCKSIZE];
	}
	BufferBlock(char* data, int sz = 4096)
	{
		blocksz = sz;
		block = new char[sz];
		for (int i = 0; i < sz; i++)
			block[i] = data[i];

	}
	~BufferBlock() {

	}

	void getData(int pos, int sz, char* data)
	{
		for (int i = 0, j = pos; j < (pos + sz) && i < blocksz; i++, j++)
		{
			data[i] = block[j];
		}
	}


	void setID(int id)
	{
		blockID = id;
	}


	int getID() const
	{
		return blockID;
	}


	int getBlocksize() const
	{
		return blocksz;
	}


	char* getBlock() const
	{
		return block;
	}


	void setBlock(char* blk)
	{
		for (int i = 0; i < blocksz; i++)
			block[i] = blk[i];
	}
};

#endif