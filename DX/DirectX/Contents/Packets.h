#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

// ���� ������ ��� ����

// ������ ������Ʈ�� ����� �־�.
// ������ ������Ʈ�� ����� �־�� �Ѵ�.
enum ServerObjectType
{
	Player,
	Bomb,
};

enum EContentPacket
{
	ActorUpdatePacket = 99,
};

// �츮�� �ּ� 16����Ʈ�� �־�� �����Ҽ� �ִ�.
// 16����Ʈ �̻� �Դٰ� �ص�
// �׺��� �� ū ��Ŷ�鵵 �ִ�.

// �ּ� 16����Ʈ�� �־�� �ϰ� + 32
// ���� :

#define GENERATED_PACKET_BODY() static const EContentPacket Type = EContentPacket::ActorUpdatePacket;

class UActorUpdatePacket : public UEngineProtocol
{
public: 
	static const EContentPacket Type = EContentPacket::ActorUpdatePacket;
public: 
	UActorUpdatePacket()
	{ 
		SetType(EContentPacket::ActorUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;


		int a = 0;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
	}

public:
	float4 Pos = float4::Zero;
	std::string SpriteName; // ?? ����
};

