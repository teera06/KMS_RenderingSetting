#pragma once

class UEngineMaterial;
class UEngineBlend : public UEngineResources<UEngineBlend>
{
	friend UEngineMaterial;
public:
	// constrcuter destructer
	UEngineBlend();
	~UEngineBlend();

	// delete Function
	UEngineBlend(const UEngineBlend& _Other) = delete;
	UEngineBlend(UEngineBlend&& _Other) noexcept = delete;
	UEngineBlend& operator=(const UEngineBlend& _Other) = delete;
	UEngineBlend& operator=(UEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineBlend> Create(std::string_view _Name, const D3D11_BLEND_DESC& _Info)
	{
		std::shared_ptr<UEngineBlend> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

private:
	ID3D11BlendState* State = nullptr;

	// ���� ���Ŀ� ������ ���� �ʰڴ�.
	// 
	float4 Factor = float4::Zero;

	// ���� ��� �κп� ���� ����� ����
	// ����� ������ ������ ���� ���̰� 

	UINT Mask= 0xFFFFFFFF;


	void ResCreate(const D3D11_BLEND_DESC& _Info);

	void Setting();
};

