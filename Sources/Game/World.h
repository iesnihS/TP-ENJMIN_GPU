#pragma once
#include "Block.h"
#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"

#define WORLD_SIZE 10
struct ModelData
{
	Matrix model; //world space
};
class World
{
	VertexBuffer<VertexLayout_PositionUV> vb;
	IndexBuffer ib;
	ConstantBuffer<ModelData> modelb;
	Vector3 dimension = { WORLD_SIZE, WORLD_SIZE, WORLD_SIZE };
	BlockId data[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];
	public:
		World();
		void GenerateWorld(DeviceResources* device);
		void DrawWorld(DeviceResources* device);
};