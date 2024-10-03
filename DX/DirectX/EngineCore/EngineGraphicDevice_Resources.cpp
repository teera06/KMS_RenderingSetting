#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineShader.h"
#include "EngineSampler.h"
#include "EngineRasterizer.h"
#include "EngineDepthStencil.h"
#include "EngineBlend.h"
#include "EngineTexture.h"

#include "EngineRenderTarget.h"

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



void ShaderInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineShader");
	UEngineShader::AutoCompile(Dir);
}

void MaterialInit()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
		Mat->SetPixeShader("ImageShader.fx");
		Mat->SetVertexShader("ImageShader.fx");
	}
}

void SamplerInit()
{
	// POINT
	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		// MIP MAP
		// MIN_MAG_MIP ������ Ŭ���� �������� 
		// MIP ������ ������
		// MAG ������ Ŭ��
		// MIN Ȯ���Ҷ�
		// ������ POINT�� ���ø�����
		// POINT ������ ���� �ʰ� ������ �����ض�.
		// Liner �� ������ �ϰ� �����ض�.

		Desc.Filter= D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;

		// �Ӹ��� ���信 ���ؼ� ����
		Desc.MipLODBias = 0.0f; // �������� �ʴ´�.
		Desc.MaxAnisotropy = 1;
		// Ư�� ���� �񱳸� ���ؼ� ������ ����ؾ��� �� ���������� ���Ǵ� �ɼ�
		// �̰� �׳� ������ ������ ���� ���

		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		UEngineSampler::Create("POINT", Desc);
	}

	// LINEAR
	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.MipLODBias = 0.0f; // �������� �ʴ´�.
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		UEngineSampler::Create("LINEAR", Desc);
	}

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

	UEngineDepthStencil::Create("EngineBase", Desc);

}

void BlendInit()
{
	CD3D11_BLEND_DESC Desc = {};

	// true ����ó���� ������ ��
	// �̰� ���귮�� ���Ƽ� false ó��

	Desc.AlphaToCoverageEnable = false;

	//SV_Target0 0�� Ÿ�ٿ� ���
	// false==0�� �������� ��� ����
	// true==���� �־��� ���� 0�� �������� ��� ����

	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask= D3D11_COLOR_WRITE_ENABLE_ALL;

	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	UEngineBlend::Create("EngineBase", Desc);
}

void EngineTexturLoad()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineResources");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);

	for (UEngineFile& File : Files)
	{
		UEngineTexture::Load(File.GetFullPath());
	}
}

void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit(); // ���ؽ� ����, �ε������� ����
	ShaderInit(); // ���̴� ������
	MaterialInit(); // ��Ƽ���� ����
	SamplerInit(); // ���÷� 
	RasterizerInit(); // �����Ͷ����� 
	Depth_StencilInit(); // ����
	BlendInit(); // ����

	EngineTexturLoad(); // ���� �׽�Ʈ �ؽ�ó �ε�

	// ���� Ÿ�� 
	UEngineRenderTarget::RenderTargetInit();
}

