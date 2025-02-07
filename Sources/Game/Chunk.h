#pragma once
#include "Block.h"
#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"

#define CHUNK_SIZE 6

struct ModelData
{
	Matrix model; //world space
};
class Chunk
{
	
	Matrix model;
	VertexBuffer<VertexLayout_PositionUV> vb;
	IndexBuffer ib;
	ConstantBuffer<ModelData> modelb;
	Vector3 dimension = { CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE };
	BlockId data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	bool HaveNeighboringBlock(Vector3& nPos, Vector3 dir, Chunk** neighboringChunks);
	public:
		Vector3 pos;
		Chunk(Vector3 pos);
		void InitChunk(uint32_t sizeY);
		void InitChunkWithBlock(BlockId id);
		void GenerateChunk(Chunk** neighboringChuck, DeviceResources* device);
		void DrawChunk(DeviceResources* device);
};