#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"

void URenderUnit::RenderingSetting()
{
	// ���ؽ� ���� ����
	Mesh->InputAssmbler1Setting();


	// �ε��� ���� ����
	Mesh->InputAssmbler2Setting();
}
