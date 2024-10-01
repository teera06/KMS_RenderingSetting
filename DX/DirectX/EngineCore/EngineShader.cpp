#include "PreCompile.h"
#include "EngineShader.h"
#include "EngineVertexShader.h"
#include "EngineShaderResources.h"

void UEngineShader::AutoCompile(UEngineDirectory _Dir)
{
	std::vector<UEngineFile> Files = _Dir.GetAllFile({ ".fx","hlsi" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FullPath = Files[i].GetFullPath();
		std::string AllShaderCode = Files[i].GetString();

		{
			size_t ShaderEntryEnd = AllShaderCode.find("_Vs(");

			if (std::string::npos != ShaderEntryEnd)
			{
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_VS";

				UEngineVertexShader::Load(FullPath.c_str(), EntryName);
			
			}
		}

		{
			size_t ShaderEntryEnd = AllShaderCode.find("_PS(");

			if (std::string::npos != ShaderEntryEnd)
			{
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_PS";

				UEngineVertexShader::Load(FullPath.c_str(), EntryName);

			}
		}
	}
}

UEngineShader::UEngineShader()
{
}

UEngineShader::~UEngineShader()
{
}

void UEngineShader::ShaderResCheck()
{
	Resource->sh
}
