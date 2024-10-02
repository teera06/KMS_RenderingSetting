#pragma once

class UEngineBlend : public UEngineResources<UEngineBlend>
{
public:
	// constrcuter destructer
	UEngineBlend();
	~UEngineBlend();

	// delete Function
	UEngineBlend(const UEngineBlend& _Other) = delete;
	UEngineBlend(UEngineBlend&& _Other) noexcept = delete;
	UEngineBlend& operator=(const UEngineBlend& _Other) = delete;
	UEngineBlend& operator=(UEngineBlend&& _Other) noexcept = delete;

private:
	ID3D11BlendState* State = nullptr;

	// ���� ���Ŀ� ������ ���� �ʰڴ�.
	// 
	float4 Factor = float4::Zero;

	// ���� ��� �κп� ���� ����� ����
	// ����� ������ ������ ���� ���̰� 

	UINT Mask= 0xFFFFFFFF;


	void ResCreate(const D3D11_BLEND_DESC& _Info);
};

