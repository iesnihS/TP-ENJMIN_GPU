#include "pch.h"
#include "Chunk.h"
#include "Cube.h"

bool Chunk::HaveNeighboringBlock(Vector3& nPos,Vector3 dir, Chunk** neighboringChunks)
{
	Vector3 newPos = nPos + dir;
	if (dir.z > 0 && neighboringChunks[0] != nullptr && nPos.z == CHUNK_SIZE -1)
	{
		BlockId& id = neighboringChunks[0]->data[0][0][0];
		return /*id == EMPTY ? false : */true;
	}
	if (newPos.x >= dimension.x || newPos.y >= dimension.y || newPos.z >= dimension.z ||
		newPos.x <0|| newPos.y <0|| newPos.z <0||
		data[(int)newPos.x][(int)newPos.y][(int)newPos.z] == BlockId::EMPTY)
		return false;
	return true;
}

Chunk::Chunk(Vector3 pos) :pos(pos),model(Matrix::CreateTranslation(pos)) //"pincette" sinon il l'initialise avant d'entrée dans le constructeur
{
}

void Chunk::InitChunkWithBlock(BlockId id)
{
	for (int x = 0; x < dimension.x; x++)
	{
		for (int y = 0; y < dimension.y; y++)
		{
			for (int z = 0; z < dimension.z; z++)
			{
				data[x][y][z] = id;
			}
		}
	}
}

void Chunk::InitChunk(uint32_t sizeY)
{
	for(int x = 0; x < dimension.x; x++)
	{
		for (int y = 0; y < dimension.y; y++)
		{
			for (int z = 0; z < dimension.z; z++)
			{
				BlockId id;
				int posY = pos.y + y;
				if (posY == sizeY * CHUNK_SIZE - 1)
					id = BlockId::GRASS;
				else if (posY == 0)
					id = BEDROCK;
				else if (posY == 2)
					id = BlockId::EMPTY;
				else if (posY >= dimension.y - dimension.y / 3.f)
					id = BlockId::DIRT;
				else
					id = BlockId::STONE;
				
				data[x][y][z] = id;
			}
		}
	}
}

void Chunk::GenerateChunk(Chunk** neighboringChuck, DeviceResources* device)
{
	for (int x = 0; x < dimension.x; x++)
	{
		for (int y = 0; y < dimension.y; y++)
		{
			for (int z = 0; z < dimension.z; z++)
			{
				BlockId id = data[x][y][z];
				if (id == BlockId::EMPTY)
					continue;
				Vector3 pos = { (float)x, (float)y, (float)z };
				Cube cube = Cube(id, pos);
				bool neighboringBlock[6] = {
					HaveNeighboringBlock(pos , Vector3::Right, neighboringChuck),
					HaveNeighboringBlock(pos , Vector3::Up, neighboringChuck),
					HaveNeighboringBlock(pos , Vector3::Forward, neighboringChuck),
											 
					HaveNeighboringBlock(pos , Vector3::Left, neighboringChuck),
					HaveNeighboringBlock(pos , Vector3::Down, neighboringChuck),
					HaveNeighboringBlock(pos , Vector3::Backward, neighboringChuck) };
				cube.Generate(&vb, &ib, neighboringBlock);
			}
		}
	}

	vb.Create(device);
	ib.Create(device);
	modelb.Create(device);
}

void Chunk::DrawChunk(DeviceResources* device)
{
	modelb.ApplyToVS(device);
	vb.Apply(device, 0);
	ib.Apply(device);
	modelb.data.model = model.Transpose();
	modelb.UpdateBuffer(device);
	device->GetD3DDeviceContext()->DrawIndexed(ib.Size(), 0, 0);
}
