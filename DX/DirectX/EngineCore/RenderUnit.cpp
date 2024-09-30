#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

void URenderUnit::RenderingSetting()
{
	// 버텍스 버퍼 세팅
	Mesh->InputAssmbler1Setting();

	// 버텍스 쉐이더 
	Material->VertexShaderSetting();

	// 인덱스 버퍼 세팅
	Mesh->InputAssmbler2Setting();
}
