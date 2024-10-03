#pragma once

class UEngineVertexShader;
class UEngineRasterizer;
class UEnginePixelShader;
class UEngineBlend;
class UEngineDepthStencil;

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

	std::shared_ptr<UEngineVertexShader> GetVertexShader()
	{
		return VertexShader;
	}
	std::shared_ptr<UEnginePixelShader> GetPixelShader()
	{
		return PixelShader;
	}
	std::shared_ptr<UEngineRasterizer> GetRasterizer()
	{
		return Rasterizer;
	}

	std::shared_ptr<UEngineBlend> GetBlend()
	{
		return Blend;
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

	// OutPut Merger-> 블랜드
	void SetBlend(std::string_view _Nmae);
	void BlendSetting();

	// OutPut Merger -> DepthStencil
	void SetDepthStencil(std::string_view _Name);
	void DepthStencilSetting();

private:

	// 버텍스 쉐이더
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;

	// 레스터라이저
	std::shared_ptr< UEngineRasterizer> Rasterizer = nullptr;

	// 픽셀 쉐이더
	std::shared_ptr<UEnginePixelShader> PixelShader = nullptr;

	// OutPut Merger-> 블랜드
	std::shared_ptr<UEngineBlend> Blend = nullptr;

	// OutPut Merger -> DepthStencil
	std::shared_ptr<UEngineDepthStencil> DepthStencil = nullptr;




};

