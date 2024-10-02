#pragma once

class UEngineVertexShader;
class UEngineRasterizer;
class UEnginePixelShader;

class UEngineMaterial : public UEngineResources<UEngineMaterial>
{
public:
	// constrcuter destructer
	UEngineMaterial();
	~UEngineMaterial();

	// delete Function
	__declspec(dllimport) UEngineMaterial(const UEngineMaterial& _Other) = delete;
	__declspec(dllimport) UEngineMaterial(UEngineMaterial&& _Other) noexcept = delete;
	__declspec(dllimport) UEngineMaterial& operator=(const UEngineMaterial& _Other) = delete;
	__declspec(dllimport) UEngineMaterial& operator=(UEngineMaterial&& _Other) noexcept = delete;


	static std::shared_ptr<UEngineMaterial> Create(std::string_view _Name)
	{
		return CreateResName("", _Name);
	}

	// 버텍스 쉐이더
	void SetVertexShader(std::string_view _Name);
	void VertexShaderSetting();

	// 레스터라이저
	void SetRasterizer(std::string_view _Name);
	void RasterizerSetting();


	// 픽셀 쉐이더
	void SetPixeShader(std::string_view _Name);
	void PixelShaderSetting();

private:
	// 버텍스 쉐이더
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;

	// 레스터라이저
	std::shared_ptr< UEngineRasterizer> Rasterizer = nullptr;

	// 픽셀 쉐이더
	std::shared_ptr<UEnginePixelShader> PixelShader = nullptr;
};

