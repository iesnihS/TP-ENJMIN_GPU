#pragma once

#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"
#include "Block.h"

using namespace DirectX::SimpleMath;
class Chunk
{
	void PushFace(Vector3 pos, Vector3 up, Vector3 right, int texId, VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib);
public :
	Matrix model;
	BlockId blockId;
	Chunk(BlockId id, Vector3 pos = Vector3::Zero);
	void Generate(VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib);
	void Draw(DeviceResources* device);
	

};