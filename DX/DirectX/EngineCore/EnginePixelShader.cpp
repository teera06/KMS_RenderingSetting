#include "PreCompile.h"
#include "EnginePixelShader.h"
#include "EngineCore.h"

UEnginePixelShader::UEnginePixelShader()
{
	Type = EShaderType::Pixel;
}

UEnginePixelShader::~UEnginePixelShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
	}
}

void UEnginePixelShader::ResLoad(std::string_view _EntryPoint, UINT _High, UINT _Low)
{
	EntryName = _EntryPoint;

	std::string Path = GetPath();
	const char* PathPtr = Path.c_str();
	std::wstring WPath = UEngineString::AnsiToUniCode(PathPtr);
	const wchar_t* WPathPtr = WPath.c_str();

	CONST D3D_SHADER_MACRO* pDefines = nullptr;

	ID3DInclude* pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	const char* pEntrypoint = _EntryPoint.data();

	// 앞쪽이 
	std::string Version = "ps_" + std::to_string(_High) + "_" + std::to_string(_Low);

	// 쉐이더도 버전이 있습니다.
	// 저는 5_0으로 하려고 합니다.
	const char* Target = Version.c_str();

	int Flag0 = 0;

#ifdef _DEBUG
	// 오타난거 아님 D3D10
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	// 나중에 행렬을 쉐이더에 알려줄때 행렬이 전치되서 들어가는걸
	// 막는거야 눈에 보이는데로 들어갑니다.
	// 전치되는 이유 나도 모름.
	// 메모리 정렬이 그래픽카드가 역순이라고 합니다.
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	int Flag1 = 0;

	HRESULT Result = D3DCompileFromFile(
		WPathPtr,
		pDefines,
		pInclude,
		pEntrypoint,
		Target,
		Flag0,
		Flag1,
		&ShaderCodeBlob,
		&ErrorCodeBlob
	);
	// ErrorCodeBlob에러에 대한 내용이 여기 담긴다.

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(ErrorCodeBlob->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GEngine->GetDirectXDevice()->CreatePixelShader(
		ShaderCodeBlob->GetBufferPointer(),
		ShaderCodeBlob->GetBufferSize(),
		nullptr,
		&ShaderPtr
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 생성에 실패했습니다.");
		return;
	}

	ShaderResCheck();
}
