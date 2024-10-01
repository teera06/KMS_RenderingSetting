#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

void EngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == IsConstantBuffer(UpperName))
	{
		MsgBoxAssert("존재하지도 않는 상수 버퍼에 세팅하려고 했습니다." + UpperName);
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
			MsgBoxAssert(Setter.Res->GetName() + "의 바이트 크기가 다릅니다." + std::to_string(Setter.BufferSize) + "Vs" + std::to_string(_Size));
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
	// 상수 버퍼 세팅

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + "상수버퍼에 세팅을 해주지 않았습니다. ");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}

void UEngineStructuredBufferSetter::PushData(const void* _Data, UINT _Size)
{

}
