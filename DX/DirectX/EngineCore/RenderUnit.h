#pragma once
#include "EngineStruct.h"


class UEngineInputLayOut;
class UEngineMesh;
class UEngineMaterial;
class UEngineShaderResources;
class UEngineShader;

class URenderUnit
{
public:
	URenderUnit();
	virtual ~URenderUnit();

	std::shared_ptr<UEngineShaderResources> Resources;

	std::shared_ptr<UEngineMesh> GetMesh()
	{
		return Mesh;
	}

	std::shared_ptr<UEngineMaterial> GetMaterial()
	{
		return Material;
	}

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	virtual void MaterialSettingEnd() {}

	void RenderingSetting();
	void ResCopy(UEngineShader* _Shader);

	virtual bool Render(float _DeltaTime);

	void Update(float _DeltaTime);

	void ResetTime()
	{
		BaseValue.AccTime = 0.0f;
	}
private:
	FBaseRenderValue BaseValue;

	std::shared_ptr<UEngineInputLayOut> LayOut=nullptr;
	std::shared_ptr<UEngineMesh> Mesh=nullptr;
	std::shared_ptr<UEngineMaterial> Material=nullptr;
};

