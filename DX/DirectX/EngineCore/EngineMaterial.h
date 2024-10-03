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

	// ���ؽ� ���̴�
	void SetVertexShader(std::string_view _Name);
	void VertexShaderSetting();

	// �����Ͷ�����
	void SetRasterizer(std::string_view _Name);
	void RasterizerSetting();


	// �ȼ� ���̴�
	void SetPixeShader(std::string_view _Name);
	void PixelShaderSetting();

	// OutPut Merger-> ����
	void SetBlend(std::string_view _Nmae);
	void BlendSetting();

	// OutPut Merger -> DepthStencil
	void SetDepthStencil(std::string_view _Name);
	void DepthStencilSetting();

private:

	// ���ؽ� ���̴�
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;

	// �����Ͷ�����
	std::shared_ptr< UEngineRasterizer> Rasterizer = nullptr;

	// �ȼ� ���̴�
	std::shared_ptr<UEnginePixelShader> PixelShader = nullptr;

	// OutPut Merger-> ����
	std::shared_ptr<UEngineBlend> Blend = nullptr;

	// OutPut Merger -> DepthStencil
	std::shared_ptr<UEngineDepthStencil> DepthStencil = nullptr;




};

