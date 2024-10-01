#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

void EngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	//if(false==)
}

bool EngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for(std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair :ConstantBuffers)
	{

	}
}

void UEngineConstantBufferSetter::Setting()
{
	// ��� ���� ����

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + "������ۿ� ������ ������ �ʾҽ��ϴ�. ");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}
