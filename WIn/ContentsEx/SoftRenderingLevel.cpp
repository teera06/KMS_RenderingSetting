#include "SoftRenderingLevel.h"
#include <EnginePlatform\EngineInput.h>
#include <EnginePlatform\EngineWindow.h>
#include <EngineCore\EngineCore.h>
#include "BackGroundMap.h"

USoftRenderingLevel::USoftRenderingLevel() 
{
}

USoftRenderingLevel::~USoftRenderingLevel() 
{
}

// �ϳ��ϳ��� ���� ���
FTransform PlayerTransform;

FTransform CameraTransform;


float Speed = 500.0f;
float RotSpeed = 360.0f;


void USoftRenderingLevel::BeginPlay()
{
	ULevel::BeginPlay();

	PlayerTransform.SetScale({100, 100, 100});

	CameraTransform.SetPosition({ 0, 0, -1000 });
}

void USoftRenderingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	PlayerControl(_DeltaTime);
	CameraControl(_DeltaTime);

}

void USoftRenderingLevel::PlayerControl(float _DeltaTime)
{
	// �Է��� �ϰ� 
	if (UEngineInput::IsPress(VK_NUMPAD8))
	{
		PlayerTransform.AddRotation(FVector(0.0f, 0.0f, 1.0f) * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_NUMPAD7))
	{
		PlayerTransform.AddRotation(FVector(0.0f, 0.0f, -1.0f) * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_NUMPAD5))
	{
		PlayerTransform.AddRotation(FVector(0.0f, 1.0f, 0.0f) * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_NUMPAD4))
	{
		PlayerTransform.AddRotation(FVector(0.0f, -1.0f, 0.0f) * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_NUMPAD2))
	{
		PlayerTransform.AddRotation(FVector(1.0f, 0.0f, 0.0f) * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_NUMPAD1))
	{
		PlayerTransform.AddRotation(FVector(-1.0f, 0.0f, 0.0f) * RotSpeed * _DeltaTime);
	}

	FMatrix RotationMat, RotationXMat, RotationYMat, RotationZMat;
	RotationXMat.RotationXDeg(PlayerTransform.GetRotation().X);
	RotationYMat.RotationYDeg(PlayerTransform.GetRotation().Y);
	RotationZMat.RotationZDeg(PlayerTransform.GetRotation().Z);
	RotationMat = RotationXMat * RotationYMat * RotationZMat;

	if (UEngineInput::IsPress('Q'))
	{
		PlayerTransform.AddPosition(RotationMat.UpVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress('E'))
	{
		PlayerTransform.AddPosition(RotationMat.DownVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress('W'))
	{
		PlayerTransform.AddPosition(RotationMat.ForwardVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress('S'))
	{
		PlayerTransform.AddPosition(RotationMat.BackVector() * Speed * _DeltaTime);
	}


	if (UEngineInput::IsPress('A'))
	{
		PlayerTransform.AddPosition(RotationMat.LeftVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress('D'))
	{
		PlayerTransform.AddPosition(RotationMat.RightVector() * Speed * _DeltaTime);
	}

}
void USoftRenderingLevel::CameraControl(float _DeltaTime)
{
	FMatrix RotationMat, RotationXMat, RotationYMat, RotationZMat;
	RotationXMat.RotationXDeg(CameraTransform.GetRotation().X);
	RotationYMat.RotationYDeg(CameraTransform.GetRotation().Y);
	RotationZMat.RotationZDeg(CameraTransform.GetRotation().Z);
	RotationMat = RotationXMat * RotationYMat * RotationZMat;


	if (UEngineInput::IsPress(VK_LEFT))
	{
		CameraTransform.AddPosition(RotationMat.LeftVector() * RotSpeed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		CameraTransform.AddPosition(RotationMat.RightVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		CameraTransform.AddPosition(RotationMat.UpVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		CameraTransform.AddPosition(RotationMat.DownVector() * Speed * _DeltaTime);
	}

	if (UEngineInput::IsPress('O'))
	{
		CameraTransform.AddRotation({0.0f, 360.0f * _DeltaTime, 0.0f});
	}

	if (UEngineInput::IsPress('P'))
	{
		CameraTransform.AddRotation({ 0.0f, 360.0f * _DeltaTime, 0.0f });
	}



}
void USoftRenderingLevel::Render(float _DeltaTime)
{
	//{
	//	FVector TestPos = { 4, 0, 0 };

	//	FMatrix TestView;

	//	TestView.View({ 1, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 });

	//	FVector Result = TestPos* TestView;

	//	int a = 0;
	//}


	//FVector PlayerPos = { 0, 0, 0 };
	//FVector MonsterPos = { 0, -1, 0 };

	//FVector PlayerForward = {0, 1, 0};
	//FVector MonsterDir = PlayerPos - MonsterPos;

	//// ���������� ����
	//// �������� ���� �𸥴�.
	//FVector Result = FVector::Cross3D(PlayerForward, MonsterDir);

	ULevel::Render(_DeltaTime);

	std::shared_ptr<UWindowImage> Image = GEngine->MainWindow.GetBackBufferImage();
	HDC DC = Image->GetImageDC();


	// ������ ������ ���鶧�� ������ ������ �������� ������ �Ѵ�.
	// �⺻������ �̳༮�� FBX�����̳� �Ž�����
	std::vector<std::vector<FVector>> Mesh;

	Mesh.resize(2);
	// �޸�

	std::vector<FVector> PivotVector0 = { {-0.5f, -0.5f, -0.5f }, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f} };
	std::vector<FVector> PivotVector1 = { {-0.5f, -0.5f, -0.5f }, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f} };

	// �ո� �޸��� �����Ϸ��� �⺻������ ����� ����� �߿��ϴ�.
	// �� ��ü�� ����� ��İ� ���� �׸��� ����?
	// �޸�
	Mesh[0] = { {-0.5f, -0.5f, 0.0f }, {-0.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f} };
	Mesh[1] = { {-0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f} , {0.5f, -0.5f, 0.0f} };

	//// �ո�
	//float Angle = 180.0f;
	//Mesh[2] = { FVector::VectorRotationYToDeg(Mesh[0][0], Angle), FVector::VectorRotationYToDeg(Mesh[0][1], Angle), FVector::VectorRotationYToDeg(Mesh[0][2], Angle) };
	//Mesh[3] = { FVector::VectorRotationYToDeg(Mesh[1][0], Angle), FVector::VectorRotationYToDeg(Mesh[1][1], Angle), FVector::VectorRotationYToDeg(Mesh[1][2], Angle) };

	//// ����
	//Angle = 90.0f;
	//Mesh[4] = { FVector::VectorRotationYToDeg(Mesh[0][0], Angle), FVector::VectorRotationYToDeg(Mesh[0][1], Angle), FVector::VectorRotationYToDeg(Mesh[0][2], Angle) };
	//Mesh[5] = { FVector::VectorRotationYToDeg(Mesh[1][0], Angle), FVector::VectorRotationYToDeg(Mesh[1][1], Angle), FVector::VectorRotationYToDeg(Mesh[1][2], Angle) };

	//Angle = -90.0f;
	//Mesh[6] = { FVector::VectorRotationYToDeg(Mesh[0][0], Angle), FVector::VectorRotationYToDeg(Mesh[0][1], Angle), FVector::VectorRotationYToDeg(Mesh[0][2], Angle) };
	//Mesh[7] = { FVector::VectorRotationYToDeg(Mesh[1][0], Angle), FVector::VectorRotationYToDeg(Mesh[1][1], Angle), FVector::VectorRotationYToDeg(Mesh[1][2], Angle) };

	//Angle = 90.0f;
	//Mesh[8] = { FVector::VectorRotationXToDeg(Mesh[0][0], Angle), FVector::VectorRotationXToDeg(Mesh[0][1], Angle), FVector::VectorRotationXToDeg(Mesh[0][2], Angle) };
	//Mesh[9] = { FVector::VectorRotationXToDeg(Mesh[1][0], Angle), FVector::VectorRotationXToDeg(Mesh[1][1], Angle), FVector::VectorRotationXToDeg(Mesh[1][2], Angle) };

	//Angle = -90.0f;
	//Mesh[10] = { FVector::VectorRotationXToDeg(Mesh[0][0], Angle), FVector::VectorRotationXToDeg(Mesh[0][1], Angle), FVector::VectorRotationXToDeg(Mesh[0][2], Angle) };
	//Mesh[11] = { FVector::VectorRotationXToDeg(Mesh[1][0], Angle), FVector::VectorRotationXToDeg(Mesh[1][1], Angle), FVector::VectorRotationXToDeg(Mesh[1][2], Angle) };


	std::vector<std::vector<FVector>> RenderingMesh = Mesh;

	// ũ���̰��� => ���庯ȯ
	// ���� �����Ѵٸ� 
	// ũ��	// ����	// �̵�	// ����	// �θ�
	// �̼����� ���Ѿ� ��ȯ�� �˴ϴ�.
	FMatrix World;
	{
		FMatrix ScaleMat;
		ScaleMat.Scale(PlayerTransform.GetScale());

		FMatrix RotationMat, RotationXMat, RotationYMat, RotationZMat;
		RotationXMat.RotationXDeg(PlayerTransform.GetRotation().X);
		RotationYMat.RotationYDeg(PlayerTransform.GetRotation().Y);
		RotationZMat.RotationZDeg(PlayerTransform.GetRotation().Z);
		RotationMat = RotationXMat * RotationYMat * RotationZMat;


		FMatrix PositionMat;
		PositionMat.Position(PlayerTransform.GetPosition());
		World = ScaleMat * RotationMat * PositionMat;
	}
	//              ũ          ��           ��


	FMatrix View;
	{
		FMatrix CameraRotationMat, CameraRotationXMat, CameraRotationYMat, CameraRotationZMat;
		CameraRotationXMat.RotationXDeg(CameraTransform.GetRotation().X);
		CameraRotationYMat.RotationYDeg(CameraTransform.GetRotation().Y);
		CameraRotationZMat.RotationZDeg(CameraTransform.GetRotation().Z);
		CameraRotationMat = CameraRotationXMat * CameraRotationYMat * CameraRotationZMat;

		View.View(CameraTransform.GetPosition(), CameraRotationMat.ForwardVector(), CameraRotationMat.UpVector());
	}
	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0]
	// [0][0][0][1]

	// ��������� ������̴�.

	FMatrix Projection;
	{
		// Projection.OrthographicLH(1280.0f, 640.0f, 1.0f, 1000.0f);
		Projection.PerspectiveFovDeg(60.0f, 1280.0f, 720.0f, 1.0f, 1000.0f);
	}

	FMatrix ViewPort;
	{
		ViewPort.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	
	float4x4 WorldViewProjection = World * View * Projection;

	// ũ�⺯ȯ
	// RenderingMesh[0][0].x == -0.5 * 100
	for (size_t TriCount = 0; TriCount < RenderingMesh.size(); TriCount++)
	{
		for (size_t VertexCount = 0; VertexCount < RenderingMesh[TriCount].size(); VertexCount++)
		{
			// ������ 3���� ��ȯ�� �Ƿ���
			float4 CheckVector = RenderingMesh[TriCount][VertexCount];

			RenderingMesh[TriCount][VertexCount] *= WorldViewProjection;

			//// ���������϶��� �̹� ���ֵ��� -1~1�� ���������� �������� �̵�����?

			//CheckVector *= World;
			//CheckVector *= View;
			//CheckVector *= Projection;

			float CurZ = RenderingMesh[TriCount][VertexCount].W;

			RenderingMesh[TriCount][VertexCount] /= CurZ;
			RenderingMesh[TriCount][VertexCount].W = 1.0f;

			CheckVector /= CurZ;

			int a = 0;

		}
	}

	// ���� ���⼭ ���Ұ̴ϴ�.
	for (size_t TriCount = 0; TriCount < RenderingMesh.size(); TriCount++)
	{
		for (size_t VertexCount = 0; VertexCount < RenderingMesh[TriCount].size(); VertexCount++)
		{
			// ������ 3���� ��ȯ�� �Ƿ���
			RenderingMesh[TriCount][VertexCount] *= ViewPort;
		}
	}


	std::vector < std::vector<POINT>> WinApiPoints;
	WinApiPoints.resize(RenderingMesh.size());
	for (size_t TriCount = 0; TriCount < RenderingMesh.size(); TriCount++)
	{
		WinApiPoints[TriCount].resize(RenderingMesh[TriCount].size());
		for (size_t VertexCount = 0; VertexCount < RenderingMesh[TriCount].size(); VertexCount++)
		{
			WinApiPoints[TriCount][VertexCount] = RenderingMesh[TriCount][VertexCount].ConvertToWinApiPOINT();
		}
	}

	for (size_t TriCount = 0; TriCount < WinApiPoints.size(); TriCount++)
	{
		// ����� �ڿ� �����ϴ� �༮�� �׸��� �ʴ´�.
		//if (0.0f >= RenderingMesh[TriCount][0].Z)
		//{
		//	continue;
		//}

		// �ո鸸 �׸���.

		//float4 Vector1 = RenderingMesh[TriCount][0] - RenderingMesh[TriCount][1];
		//float4 Vector2 = RenderingMesh[TriCount][1] - RenderingMesh[TriCount][2];
		//float4 Cross = float4::Cross3D(Vector1, Vector2);

		//if (0.0f >= Cross.Z)
		//{
		//	continue;
		//}

		POINT& StartPoint = WinApiPoints[TriCount][0];

		Polygon(DC, &StartPoint, 3);
	}


	int a = 0;
}

void USoftRenderingLevel::LevelStart(ULevel* _Level)
{
}

void USoftRenderingLevel::LevelEnd(ULevel* _Level)
{
}