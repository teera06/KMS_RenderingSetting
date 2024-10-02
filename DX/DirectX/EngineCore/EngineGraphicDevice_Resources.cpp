#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineShader.h"
#include "EngineRasterizer.h"


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

void MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
		Mat->SetPixeShader("ImageShader.fx");
		Mat->SetVertexShader("ImageShader.fx");
	}
}

void ShaderInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineShader");
	UEngineShader::AutoCompile(Dir);
}

void RasterizerInit()
{
	// �����Ͷ����� ����
	{
		D3D11_RASTERIZER_DESC Desc = {};

		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		// ������ �׷���

		// �ո��̰� �ڸ��̰� �� �׷���.
		// �츮 �������� ��
		//

		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;


		Desc.AntialiasedLineEnable = TRUE;
		Desc.DepthClipEnable = TRUE;

		UEngineRasterizer::Create("EngineBase", Desc);
	}


	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.AntialiasedLineEnable = TRUE;
		Desc.DepthClipEnable = TRUE;
		UEngineRasterizer::Create("Debug", Desc);
	}
}

void Depth_StencilInit()
{
	D3D11_DEPTH_STENCIL_DESC Desc = { 0, };

	Desc.DepthEnable = true;
	// ���� ������ z���� �����Ѵ�. -> float

	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.DepthFunc= D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	Desc.StencilEnable = false;



}

void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit(); // ���ؽ� ����, �ε������� ����
	ShaderInit(); // ���̴� ������
	RasterizerInit(); // �����Ͷ����� 


}

