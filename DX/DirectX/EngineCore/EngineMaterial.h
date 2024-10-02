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

	// ���ؽ� ���̴�
	void SetVertexShader(std::string_view _Name);
	void VertexShaderSetting();

	// �����Ͷ�����
	void SetRasterizer(std::string_view _Name);
	void RasterizerSetting();


	// �ȼ� ���̴�
	void SetPixeShader(std::string_view _Name);
	void PixelShaderSetting();

private:
	// ���ؽ� ���̴�
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;

	// �����Ͷ�����
	std::shared_ptr< UEngineRasterizer> Rasterizer = nullptr;

	// �ȼ� ���̴�
	std::shared_ptr<UEnginePixelShader> PixelShader = nullptr;
};

