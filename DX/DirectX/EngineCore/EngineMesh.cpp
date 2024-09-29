#include "PreCompile.h"
#include "EngineMesh.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"

UEngineMesh::UEngineMesh()
{
}

UEngineMesh::~UEngineMesh()
{
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
