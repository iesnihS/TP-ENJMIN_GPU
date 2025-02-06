#pragma once

#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"
#include "Block.h"

using namespace DirectX::SimpleMath;
class Cube
{
	void PushFace(Vector3 pos, Vector3 up, Vector3 right, int texId, VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib);
public :
	Vector3 posInChunk;
	BlockId blockId;
	Cube(BlockId id, Vector3 pos = Vector3::Zero);
	void Generate(VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib, bool* neighboringBlocks);
	

};