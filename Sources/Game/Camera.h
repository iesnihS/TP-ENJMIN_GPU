#pragma once

#include "../Engine/Buffer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera {
	float fov;
	float nearPlane = 0.01f;
	float farPlane = 500.0f;

	float scrollValue = 0;

	Vector3 camPos = Vector3(0, 0, 2);
	Quaternion camRot = Quaternion();
	Matrix projection;
	Matrix view;

	struct MatrixData {
		Matrix mView;
		Matrix mProjection;
	};
	ConstantBuffer<MatrixData>* cbCamera = nullptr;
public:
	Camera(float fov, float aspectRatio);
	~Camera();

	void UpdateAspectRatio(float aspectRatio);
	void Update(float dt, DirectX::Keyboard::State kb, DirectX::Mouse* ms);

	void ApplyCamera(DeviceResources* deviceRes);
};