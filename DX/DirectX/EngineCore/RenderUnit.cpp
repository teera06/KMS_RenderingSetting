#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

void URenderUnit::RenderingSetting()
{
	// ���ؽ� ���� ����
	Mesh->InputAssmbler1Setting();
	LayOut->

	// ���ؽ� ���̴� 
	Material->VertexShaderSetting();

	// �ε��� ���� ����
	Mesh->InputAssmbler2Setting();
}
