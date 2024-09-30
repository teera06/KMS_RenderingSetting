#include "PreCompile.h"
#include "EngineVertexShader.h"
#include "EngineCore.h"

UEngineVertexShader::UEngineVertexShader()
{
}

UEngineVertexShader::~UEngineVertexShader()
{
}

void UEngineVertexShader::ResLoad(std::string_view _EntryPoint, UINT _High, UINT _Low)
{
	EntryName = _EntryPoint;

	std::string Path = GetPath();
	const char* PathPtr = Path.c_str();
	std::wstring WPath = UEngineString::AnsiToUniCode(PathPtr);
	const wchar_t* WPathPtr = WPath.c_str();

	CONST D3D_SHADER_MACRO* pDefines = nullptr;
	// �ּҰ��� 1�� �����͸� �־���

	ID3DInclude* pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	const char* pEntrypoint = _EntryPoint.data();

	std::string Version = "vs_" + std::to_string(_High) + "_" + std::to_string(_Low);

	// ���̴��� ������ �ִ�.
	// ����ϴ°� 5.0

	const char* Target = Version.c_str();

	int Flag0 = 0;

#ifdef DEBUG

	Flag0 = D3D11_SHADER_DEBUG;
#endif // DEBUG
	// ���߿� ����� ���̴��� �˷��ٶ� ����� ��ġ�Ǽ� ���°� ����
	// �޸� ���� �׷���ī�尡 ����
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

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(ErrorCodeBlob->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GEngine->GetDirectXDevice()->CreateVertexShader(
		ShaderCodeBlob->GetBufferPointer(),
		ShaderCodeBlob->GetBufferSize(),
		nullptr,
		&ShaderPtr
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("���̴� ������ �����߽��ϴ�.");
		return;
	}


}
