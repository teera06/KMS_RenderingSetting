#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineShader.h"
#include "EngineRasterizer.h"


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



}

void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit(); // 버텍스 버퍼, 인데스버퍼 세팅
	ShaderInit(); // 쉐이더 컴파일
	RasterizerInit(); // 레스터라이저 


}

