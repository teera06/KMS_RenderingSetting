#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineInputLayOut.h"

void URenderUnit::RenderingSetting()
{
	// 버텍스 버퍼 세팅
	Mesh->InputAssmbler1Setting();
	// 인풋 레이아웃
	LayOut->Setting();

	// 버텍스 쉐이더 
	Material->VertexShaderSetting();

	// 인덱스 버퍼 세팅
	Mesh->InputAssmbler2Setting();

	// 레스터라이저 세팅
	Material->RasterizerSetting();

	// 픽셀 쉐이더 세팅
	Material->PixelShaderSetting();

	// OutPut Merger -> DepthStencil 세팅
	Material->DepthStencilSetting();

	// OutPUt Merger -> 블랜드 세팅
	Material->BlendSetting();
}
