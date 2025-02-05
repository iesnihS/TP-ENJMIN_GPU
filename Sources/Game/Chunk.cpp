#include "pch.h"
#include "Chunk.h"


Chunk::Chunk(BlockId id, Vector3 pos) : blockId(id)
{
	model = Matrix::CreateTranslation(pos);
}

void Chunk::Generate(VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib)
{
	BlockData data = BlockData::Get(blockId);
	PushFace({ -0.5f, -0.5f, 0.5f }, Vector3::Up, Vector3::Right, data.texIdSide,vb, ib);
	PushFace({ 0.5f, -0.5f, 0.5f }, Vector3::Up, Vector3::Forward, data.texIdSide,vb, ib);
	PushFace({ 0.5f, -0.5f,-0.5f }, Vector3::Up, Vector3::Left, data.texIdSide,vb, ib);

	PushFace({ -0.5f, -0.5f,-0.5f }, Vector3::Up, Vector3::Backward, data.texIdSide,vb, ib);
	PushFace({ -0.5f,  0.5f, 0.5f }, Vector3::Forward, Vector3::Right, data.texIdTop,vb, ib);
	PushFace({ -0.5f, -0.5f,-0.5f }, Vector3::Backward, Vector3::Right, data.texIdBottom,vb, ib);
}

void Chunk::Draw(DeviceResources* device)
{
	
}

Vector4 ToVec4(Vector3 v)
{
	return Vector4(v.x, v.y, v.z, 1.0f);
}

void Chunk::PushFace(Vector3 pos, Vector3 up, Vector3 right, int texId, VertexBuffer<VertexLayout_PositionUV>* vb, IndexBuffer* ib)
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
