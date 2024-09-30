#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineMesh.h"

// ��ǲ����� 1�� ��ǲ����� 2�� ���ҽ����� ������ �̴ϼȶ�����
void MeshInit()
{
	FEngineVertex::Info.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	FEngineVertex::Info.AddInputLayOut("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);

		{
			VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f} };
			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);
		}

		// �ﰢ���� ��� �׸����� ���� ����
		std::vector<UINT> IndexData = { 0,1,2,0,2,3 };

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect"); // �޽� ����

		{
			VertexData[0] = { {-1.0f, 1.0f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {1.0f, 1.0f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {1.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} };

			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("FullRect", VertexData);
		}

		UEngineMesh::Create("FullRect", "FullRect","Rect"); // �޽� ����
	}

	{

	}
}