#include "pch.h"
#include "Cube.h"


Cube::Cube(BlockId id, Vector3 pos) : blockId(id)
{
	posInChunk = pos;
}

void Cube::Generate(VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib, bool* neighboringBlocks)
{
	BlockData data = BlockData::Get(blockId);

	if(!neighboringBlocks[5]) //back face
		PushFace(posInChunk + Vector3( -0.5f, -0.5f, 0.5f ),  Vector3::Up, Vector3::Right, data.texIdSide,vb, ib);
	if(!neighboringBlocks[0])//left face
		PushFace(posInChunk + Vector3(0.5f, -0.5f, 0.5f ),  Vector3::Up, Vector3::Forward, data.texIdSide,vb, ib);
	if (!neighboringBlocks[1])//down face
		PushFace(posInChunk + Vector3(-0.5f, 0.5f, 0.5f), Vector3::Forward, Vector3::Right, data.texIdTop, vb, ib);

	if (!neighboringBlocks[2])//front face
	PushFace(posInChunk + Vector3(0.5f, -0.5f,-0.5f ),  Vector3::Up, Vector3::Left, data.texIdSide,vb, ib);
	if (!neighboringBlocks[3])//right face
	PushFace(posInChunk + Vector3(-0.5f, -0.5f,-0.5f ),  Vector3::Up, Vector3::Backward, data.texIdSide,vb, ib);
	if (!neighboringBlocks[4])//up face
	PushFace(posInChunk + Vector3(-0.5f, -0.5f,-0.5f ),  Vector3::Backward, Vector3::Right, data.texIdBottom,vb, ib);
}

Vector4 ToVec4(Vector3 v)
{
	return Vector4(v.x, v.y, v.z, 1.0f);
}

void Cube::PushFace(Vector3 pos, Vector3 up, Vector3 right, int texId, VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib)
{
	float x1 = (texId % 16)/16.f;
	float x2 = x1 + 1 / 16.f;
	float y1 = floor(texId/16.)/16.;
	float y2 = y1 + 1/16.f;

	uint32_t a = vb->PushVertex({ ToVec4(pos),{x1, y2}});
	uint32_t b = vb->PushVertex({ ToVec4(pos+up),{x1, y1}});
	uint32_t c = vb->PushVertex({ ToVec4(pos+right),{x2, y2}});
	uint32_t d = vb->PushVertex({ ToVec4(pos+up+right),{x2, y1}});

	ib->PushTriangle(a, b, c);
	ib->PushTriangle(c, b, d);
}
