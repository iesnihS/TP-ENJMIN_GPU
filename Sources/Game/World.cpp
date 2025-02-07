#include "pch.h"
#include "World.h"

World::World(uint32_t sizeY) : size(sizeY)
{
}

void World::GenerateWorld(DeviceResources* device)
{
	for(int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			for (int z = 0; z < size; z++)
			{
				Chunk& chunk = displayingChunks.emplace_back(Vector3(x*CHUNK_SIZE,y * CHUNK_SIZE,z * CHUNK_SIZE));
				chunk.InitChunk(size);
			}
		}
	}
	Chunk* neighboringChunks[6] = { nullptr };
	for(int iterateDisplay =0; iterateDisplay < displayingChunks.size(); iterateDisplay++)
	{
		Chunk& chunk = displayingChunks[iterateDisplay];
		
		int iR = GetNeighboringArrayIndex(Vector3::Left, iterateDisplay, size);
		if (iR >= 0 && iR < displayingChunks.size())
		{
			neighboringChunks[0] = &displayingChunks[iR];
			neighboringChunks[0]->InitChunkWithBlock(TNT);
		}
	}

	for(auto& chunk : displayingChunks)
	{
		chunk.GenerateChunk(neighboringChunks, device);
	}
}
uint32_t World::GetFlat3DArrayIndex(uint32_t& x, uint32_t& y, uint32_t& z, uint32_t& size)
{
	return x + y * size + z * size * size;
}

uint32_t World::GetNeighboringArrayIndex(Vector3 dir, uint32_t ind, uint32_t size)
{
	if (dir.x > 0 && (ind + 1) % (size) != 0)
	{
		return ind + 1;
	}
	else if (dir.x < 0 && ind != 0)
	{
		return ind - 1;
	}

	return -1;
}

void World::DrawWorld(DeviceResources* device)
{
	for(Chunk& chunk : displayingChunks)
	{
		chunk.DrawChunk(device);
	}
}

