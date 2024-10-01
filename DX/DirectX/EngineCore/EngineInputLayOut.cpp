#include "PreCompile.h"
#include "EngineInputLayOut.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"
#include "EngineShader.h"

#include "EngineCore.h"

UEngineInputLayOut::UEngineInputLayOut()
{
}

UEngineInputLayOut::~UEngineInputLayOut()
{
}

void UEngineInputLayOut::ResCreate(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader)
{
	if (nullptr == _Buffer)
	{
		MsgBoxAssert("��ǲ���̾ƿ��� ���鶧 ���۰� nullptr");
	}

	UVertexLayOutInfo* Ptr = _Buffer->LayOutInfoPtr;
	std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc = Ptr->Descs;

	if (nullptr == _Shader)
	{
		MsgBoxAssert("��ǲ���̾ƿ��� ���鶧 ���̴��� nullptr ");
	}

	ID3DBlob* VertexShaderCodeBlob = _Shader->ShaderCodeBlob;

	HRESULT Result = GEngine->GetDirectXDevice()->CreateInputLayout(
		&Desc[0],
		static_cast<UINT>(Desc.size()),
		VertexShaderCodeBlob->GetBufferPointer(),
		VertexShaderCodeBlob->GetBufferSize(),
		&LayOut
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("��ǲ ���̾ƿ� ������ ����");
		return;
	}


}

void UEngineInputLayOut::Setting()
{
#ifdef DEBUG
	if (nullptr == LayOut)
	{
		MsgBoxAssert("��������� ���� ��ǲ���̾ƿ��� �����Ҽ��� �����ϴ�.");
	}
#endif // DEBUG
	GEngine->GetDirectXContext()->IASetInputLayout(LayOut);
}
