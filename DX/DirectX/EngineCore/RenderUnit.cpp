#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"

void URenderUnit::RenderingSetting()
{
	// 버텍스 버퍼 세팅
	Mesh->InputAssmbler1Setting();


	// 인덱스 버퍼 세팅
	Mesh->InputAssmbler2Setting();
}
