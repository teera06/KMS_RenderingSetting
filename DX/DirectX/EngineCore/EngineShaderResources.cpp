#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

void EngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == IsConstantBuffer(UpperName))
	{
		MsgBoxAssert("���������� �ʴ� ��� ���ۿ� �����Ϸ��� �߽��ϴ�." + UpperName);
		return;
	}

	for(std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair:ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (false == ResMap.contains(UpperName))
		{
			continue;
		}
		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (Setter.BufferSize != _Size)
		{
			MsgBoxAssert(Setter.Res->GetName() + "�� ����Ʈ ũ�Ⱑ �ٸ��ϴ�." + std::to_string(Setter.BufferSize) + "Vs" + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

bool EngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for(std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair :ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return true;
		}
	}

	return false;
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

void UEngineStructuredBufferSetter::PushData(const void* _Data, UINT _Size)
{

}
