#include "PreCompile.h"
#include "EngineMesh.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineCore.h"

UEngineMesh::UEngineMesh()
{
}

UEngineMesh::~UEngineMesh()
{
}

void UEngineMesh::IndexDraw()
{

	GEngine->GetDirectXContext()->DrawIndexed(IndexBuffer->Count, 0, 0);
}

void UEngineMesh::DrawIndexedInstanced(int _InstancingCount)
{
	GEngine->GetDirectXContext()->DrawIndexedInstanced(IndexBuffer->Count, _InstancingCount,0, 0,0);
}

void UEngineMesh::ResCreate(std::string_view _VertexName, std::string_view _IndexName)
{
	VertexBuffer = UEngineVertexBuffer::FindRes(_VertexName);
	IndexBuffer = UEngineIndexBuffer::FindRes(_IndexName);

	if (nullptr == VertexBuffer || nullptr == IndexBuffer)
	{
		MsgBoxAssert("�޽� ������ ���� �߽��ϴ�.");
		return;
	}

}

void UEngineMesh::InputAssmbler1Setting()
{
#ifdef DEBUG
	if (nullptr == VertexBuffer) 
	{
		MsgBoxAssert("���ؽ� ���۰� ���õ��� ���� �޽� �Դϴ�." + GetName());
		return;
	}
#endif // DEBUG
	VertexBuffer->Setting();
}

void UEngineMesh::InputAssmbler2Setting()
{
#ifdef _DEBUG
	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("�ε��� ���۰� ���õ��� ���� �޽��Դϴ�." + GetName());
		return;
	}
#endif
	IndexBuffer->Setting();

	// �ﰢ������ �׷���
	GEngine->GetDirectXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}
