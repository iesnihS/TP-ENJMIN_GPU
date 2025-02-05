#pragma once

#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"
#include "Block.h"

using namespace DirectX::SimpleMath;
class Chunk
{
	std::vector<BlockId> blocksId;
	VertexBuffer<VertexLayout_PositionUV> vb;
	IndexBuffer ib;
	void PushFace(Vector3 pos, Vector3 up, Vector3 right, int texId);
public :
	Matrix model;

	Chunk(Vector3 pos = Vector3::Zero);
	void Generate(DeviceResources* device);
	void Draw(DeviceResources* device);
	

};