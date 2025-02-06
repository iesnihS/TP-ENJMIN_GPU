#include "pch.h"
#include "World.h"

World::World(uint32_t sizeY) : sizeY(sizeY)
{
}

void World::GenerateWorld(DeviceResources* device)
{
	for(int x = 0; x < sizeY; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int z = 0; z < sizeY; z++)
			{
				Chunk& chunk = displayingChunks.emplace_back(Vector3(x*CHUNK_SIZE,y * CHUNK_SIZE,z * CHUNK_SIZE));
				chunk.InitChunk(sizeY);
			}
		}
	}

	for(int iterateDisplay =0; iterateDisplay < displayingChunks.size(); iterateDisplay++)
	{
		Chunk& chunk = displayingChunks[iterateDisplay];
		Chunk*  neighboringChunks[6] = {nullptr};
		int iR = GetNeighboringArrayIndex(Vector3::Right, iterateDisplay, displayingChunks.size());
		if (iR >= 0 && iR < displayingChunks.size())
			neighboringChunks[0] = &displayingChunks[0];
		chunk.GenerateChunk(neighboringChunks, device);
	}
}
uint32_t World::GetFlat3DArrayIndex(uint32_t& x, uint32_t& y, uint32_t& z, uint32_t& size)
{
	return x + y * size + z * size * size;
}

uint32_t World::GetNeighboringArrayIndex(Vector3 dir, uint32_t ind, uint32_t size)
{
	if (dir.x > 0)
	{
		return ind + 1;
	}
	return 0;
}

void World::DrawWorld(DeviceResources* device)
{
	for(Chunk& chunk : displayingChunks)
	{
		chunk.DrawChunk(device);
	}
}

