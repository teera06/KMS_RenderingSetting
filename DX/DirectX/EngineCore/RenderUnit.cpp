#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineInputLayOut.h"

void URenderUnit::RenderingSetting()
{
	// ���ؽ� ���� ����
	Mesh->InputAssmbler1Setting();
	// ��ǲ ���̾ƿ�
	LayOut->Setting();

	// ���ؽ� ���̴� 
	Material->VertexShaderSetting();

	// �ε��� ���� ����
	Mesh->InputAssmbler2Setting();
}
