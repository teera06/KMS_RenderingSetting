#include "PreCompile.h"
#include "SamCore.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include "ServerGameMode.h"
#include "EngineBase/EngineTime.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineFont.h>

std::shared_ptr<UEngineNet> USamCore::Net = nullptr;

USamCore::USamCore() 
{
}

USamCore::~USamCore() 
{
}

void USamCore::Initialize()
{
	UEngineFont::Load("±Ã¼­");

	{
		std::map<int, int> Test;
		for (int i = 0; i < 1000; i++)
		{
			Test[i] = i;
		}
		UEngineTime Time;
		Time.TimeCheckStart();
		std::map<int, int>::iterator FindIter = Test.find(999);
		Time.TimeCheck();
		double dTime = Time.GetDeltaTime();
		float fTime = static_cast<float>(Time.GetDeltaTime());
		int a = 0;
	}

	{
		std::vector<int> Test;
		for (int i = 0; i < 1000; i++)
		{
			Test.push_back(i);
		}
		UEngineTime Time;
		Time.TimeCheckStart();

		for (int i = 0; i < 1000; i++)
		{
			if (999 == Test[i])
			{
				break;
			}
		}
		Time.TimeCheck();

		double dTime = Time.GetDeltaTime();
		double fTime = static_cast<float>(Time.GetDeltaTime());
		int a = 0;
	}

	/*{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);

		for (UEngineFile File : Files)
		{
			UEngineSprite::ThreadSafeLoad(File.GetFullPath());
		}
	}*/


	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->CreateLevel<AServerGameMode>("ServerLevel");
	GEngine->ChangeLevel("PlayLevel");


}