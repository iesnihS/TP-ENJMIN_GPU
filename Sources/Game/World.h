#pragma once

#include "Chunk.h"
 class World
 {
	 std::vector<Chunk> displayingChunks;
	 uint32_t GetFlat3DArrayIndex(uint32_t &x, uint32_t &y, uint32_t &z, uint32_t &size);
	 uint32_t GetNeighboringArrayIndex(Vector3 dir,uint32_t ind, uint32_t size);
	public:
		uint32_t sizeY;
		World(uint32_t size);
		void GenerateWorld(DeviceResources* device);
		void DrawWorld(DeviceResources* device);
 };