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
		MsgBoxAssert("인풋에이아웃을 만들때 버퍼가 nullptr");
	}

	UVertexLayOutInfo* Ptr = _Buffer->LayOutInfoPtr;
	std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc = Ptr->Descs;

	if (nullptr == _Shader)
	{
		MsgBoxAssert("인풋레이아웃을 만들때 쉐이더가 nullptr ");
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
		MsgBoxAssert("인풋 레이아웃 생성에 실패");
		return;
	}


}

void UEngineInputLayOut::Setting()
{
#ifdef DEBUG
	if (nullptr == LayOut)
	{
		MsgBoxAssert("만들어지지 않은 인풋레이아웃을 세팅할수는 없습니다.");
	}
#endif // DEBUG
	GEngine->GetDirectXContext()->IASetInputLayout(LayOut);
}
