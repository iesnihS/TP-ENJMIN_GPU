#include "pch.h"
#include "Cube.h"


Cube::Cube(Vector3 pos)
{
	model = Matrix::CreateTranslation(pos);
}

void Cube::Generate(DeviceResources* device)
{
	PushFace({ -0.5f, -0.5f, 0.5f}, Vector3::Up,Vector3::Right);
	PushFace({ 0.5f, -0.5f, 0.5f }, Vector3::Up, Vector3::Forward);
	PushFace({0.5f, -0.5f, -0.5f }, Vector3::Up, Vector3::Left);
	
	PushFace({-0.5f, -0.5f, -0.5f}, Vector3::Up, Vector3::Backward);
	PushFace({ -0.5f, 0.5f, 0.5f }, Vector3::Forward, Vector3::Right);
	PushFace({ -0.5f, -0.5f, -0.5f }, Vector3::Backward, Vector3::Right);
	vb.Create(device);
	ib.Create(device);
}

void Cube::Draw(DeviceResources* device)
{
	vb.Apply(device, 0);
	ib.Apply(device);
	device->GetD3DDeviceContext()->DrawIndexed(ib.Size(), 0, 0);
}

Vector4 ToVec4(Vector3 v)
{
	return Vector4(v.x, v.y, v.z, 1.0f);
}

void Cube::PushFace(Vector3 pos, Vector3 up, Vector3 right)
{
	uint32_t a = vb.PushVertex({ ToVec4(pos),{0,0} });
	uint32_t b = vb.PushVertex({ ToVec4(pos+right),{0,1} });
	uint32_t c = vb.PushVertex({ ToVec4(pos+up),{1,0} });
	uint32_t d = vb.PushVertex({ ToVec4(pos+up+right),{1,1} });

	ib.PushTriangle(a, b, c);
	ib.PushTriangle(c, b, d);
}
