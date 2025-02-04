#pragma once

#include "../Engine/Buffer.h"
#include "../Engine/VertexLayout.h"

using namespace DirectX::SimpleMath;
class Cube
{
	VertexBuffer<VertexLayout_PositionUV> vb;
	IndexBuffer ib;
	void PushFace(Vector3 pos, Vector3 up, Vector3 right);
public :
	Matrix model;

	Cube(Vector3 pos = Vector3::Zero);
	void Generate(DeviceResources* device);
	void Draw(DeviceResources* device);
	

};