#include "pch.h"
#include "World.h"
#include "Chunk.h"

World::World()
{
}

void World::GenerateWorld(DeviceResources* device)
{
	for(int x = 0; x < dimension.x; x++)
	{
		for (int y = 0; y < dimension.y; y++)
		{
			for (int z = 0; z < dimension.z; z++)
			{
				Chunk chunk = Chunk(BlockId::GRASS, Vector3(x, y, z)); 
				chunk.Generate(&vb, &ib);
				data[x][y][z] = chunk.blockId;
			}
		}
	}
	vb.Create(device);
	ib.Create(device);
	modelb.Create(device);
}

void World::DrawWorld(DeviceResources* device)
{
	modelb.ApplyToVS(device);
	vb.Apply(device, 0);
	ib.Apply(device);
	for (int x = 0; x < dimension.x; x++)
	{
		for (int y = 0; y < dimension.y; y++)
		{
			for (int z = 0; z < dimension.z; z++)
			{
				modelb.data.model = Matrix::CreateTranslation({(float)x,(float)y,(float)z}).Transpose();
				modelb.UpdateBuffer(device);
				device->GetD3DDeviceContext()->DrawIndexed(ib.Size(), 0, 0);
			}
		}
	}
	
	
}
