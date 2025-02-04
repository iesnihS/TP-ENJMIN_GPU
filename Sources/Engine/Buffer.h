#pragma once

using Microsoft::WRL::ComPtr;

template <typename TVertex>
class VertexBuffer
{
	ComPtr<ID3D11Buffer> buffer;

public:
	std::vector<TVertex> vertices;
	VertexBuffer() {};

	uint32_t PushVertex(TVertex vertex)
	{
		vertices.push_back(vertex);
		return vertices.size() - 1;
	}

	void Create(DeviceResources* device)
	{
		CD3D11_BUFFER_DESC desc(sizeof(TVertex) * vertices.size(), D3D11_BIND_VERTEX_BUFFER);

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = vertices.data();

		device->GetD3DDevice()->CreateBuffer(&desc, &initData, buffer.ReleaseAndGetAddressOf());
	}

	void UpdateBuffer(DeviceResources* device)
	{
		device->GetD3DDeviceContext()->UpdateSubresource(buffer.Get(), 0, nullptr_t, &data, 0, 0);
	}

	void Apply(DeviceResources* device, int slot = 0)
	{
		ID3D11Buffer* vbs[] = { buffer.Get() }; //Vertex BufferS
		const uint32_t strides [] = {sizeof(TVertex)}; //tableau car il peut y avoir plusieurs buffer
		const uint32_t  offsets[] = { 0 };
		device->GetD3DDeviceContext()->IASetVertexBuffers(slot, 1, vbs, strides, offsets);
	}
};


class IndexBuffer
{
	ComPtr<ID3D11Buffer> buffer;

public:
	std::vector<uint32_t> indices;
	IndexBuffer() {};
	void Create(DeviceResources* device)
	{
		CD3D11_BUFFER_DESC desc(sizeof(uint32_t) * indices.size(), D3D11_BIND_INDEX_BUFFER);

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = indices.data();

		device->GetD3DDevice()->CreateBuffer(&desc, &initData, buffer.ReleaseAndGetAddressOf());
	}

	size_t Size()
	{
		return indices.size();
	}

	void Apply(DeviceResources* device)
	{
		device->GetD3DDeviceContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT,0);
	}

	void PushTriangle(uint32_t a, uint32_t b, uint32_t c)
	{
		indices.push_back(a);
		indices.push_back(b);
		indices.push_back(c);
	}
};

template <typename TData>
class ConstantBuffer
{
	ComPtr<ID3D11Buffer> buffer;

public :
	TData data;
	ConstantBuffer() {};
	void Create(DeviceResources* device)
	{
		CD3D11_BUFFER_DESC desc(sizeof(data), D3D11_BIND_CONSTANT_BUFFER);
		device->GetD3DDevice()->CreateBuffer(&desc, nullptr, buffer.ReleaseAndGetAddressOf());
	}

	void UpdateBuffer(DeviceResources* device)
	{
		device->GetD3DDeviceContext()->UpdateSubresource(buffer.Get(), 0, nullptr, &data, 0, 0);
	}

	void ApplyToVS(DeviceResources* device, int slot = 0)
	{
		ID3D11Buffer* cbs[] = { buffer.Get()};
		device->GetD3DDeviceContext()->VSSetConstantBuffers(slot, 1, cbs);
	}
};