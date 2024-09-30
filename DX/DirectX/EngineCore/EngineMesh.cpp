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
		MsgBoxAssert("메시 생성에 실패 했습니다.");
		return;
	}

}

void UEngineMesh::InputAssmbler1Setting()
{
#ifdef DEBUG
	if (nullptr == VertexBuffer) 
	{
		MsgBoxAssert("버텍스 버퍼가 세팅되지 않은 메시 입니다." + GetName());
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
		MsgBoxAssert("인덱스 버퍼가 세팅되지 않은 메시입니다." + GetName());
		return;
	}
#endif
	IndexBuffer->Setting();

	// 삼각형으로 그려라
	GEngine->GetDirectXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}
