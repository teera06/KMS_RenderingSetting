#pragma once

class UEngineVertexShader;
class UEngineRasterizer;
class UEngineMaterial
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

	// ���ؽ� ���̴�
	void SetVertexShader(std::string_view _Name);
	void VertexShaderSetting();

	void SetRasterizer(std::string_view _Name);
	void RasterizerSetting();

private:
	// ���ؽ� ���̴�
	std::shared_ptr<UEngineVertexShader> VertexShader = nullptr;

	// �����Ͷ�����
	std::shared_ptr< UEngineRasterizer> Rasterizer = nullptr;

};

