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

// 인풋어셈블러 1과 인풋어셈블러 2의 리소스들을 만들어내는 이니셜라이즈
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

		// 삼각형을 어떻게 그릴지에 대한 순서
		std::vector<UINT> IndexData = { 0,1,2,0,2,3 };

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect"); // 메시 종류

		{
			VertexData[0] = { {-1.0f, 1.0f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {1.0f, 1.0f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {1.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} };

			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("FullRect", VertexData);
		}

		UEngineMesh::Create("FullRect", "FullRect","Rect"); // 메시 종류
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
		// MIN_MAG_MIP 나보다 클때든 작을때는 
		// MIP 나보다 작을때
		// MAG 나보다 클때
		// MIN 확대할때
		// 언제나 POINT로 샘플링히라
		// POINT 보간을 하지 않고 색깔을 추출해라.
		// Liner 는 보간을 하고 추출해라.

		Desc.Filter= D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;

		// 밉맵의 개념에 대해서 이해
		Desc.MipLODBias = 0.0f; // 보간하지 않는다.
		Desc.MaxAnisotropy = 1;
		// 특정 값의 비교를 통해서 색깔을 출력해야할 때 여러곳에서 사용되는 옵션
		// 이건 그냥 무조건 비교하지 말고 출력

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
		Desc.MipLODBias = 0.0f; // 보간하지 않는다.
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		UEngineSampler::Create("LINEAR", Desc);
	}

}

void RasterizerInit()
{
	// 레스터라이저 세팅
	{
		D3D11_RASTERIZER_DESC Desc = {};

		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		// 선으로 그려라

		// 앞면이건 뒤면이건 다 그려라.
		// 우리 외적으로 앞
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
	// 깊이 버퍼의 z값을 저장한다. -> float

	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.DepthFunc= D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	Desc.StencilEnable = false;

	UEngineDepthStencil::Create("EngineBase", Desc);

}

void BlendInit()
{
	CD3D11_BLEND_DESC Desc = {};

	// true 투명처리가 투명이 됨
	// 이게 연산량이 높아서 false 처리

	Desc.AlphaToCoverageEnable = false;

	//SV_Target0 0번 타겟에 출력
	// false==0번 세팅으로 모두 통일
	// true==각기 넣어준 세팅 0번 세팅으로 모두 통일

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
	MeshInit(); // 버텍스 버퍼, 인데스버퍼 세팅
	ShaderInit(); // 쉐이더 컴파일
	MaterialInit(); // 머티리얼 세팅
	SamplerInit(); // 샘플러 
	RasterizerInit(); // 레스터라이저 
	Depth_StencilInit(); // 깊이
	BlendInit(); // 블랜드

	EngineTexturLoad(); // 엔진 테스트 텍스처 로드

	// 랜더 타켓 
	UEngineRenderTarget::RenderTargetInit();
}

