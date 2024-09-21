#pragma once
#include <string>
#include <map>
#include <list>
#include "EngineBase/PathObject.h"
// 설명 :
template<typename ResType>
class UEngineResources : public UPathObject
{
public:
	// constrcuter destructer
	UEngineResources() {}
	~UEngineResources() {}

	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;


	inline static std::shared_ptr<ResType> FindRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == NameResources.contains(UpperName))
		{
			return nullptr;
		}

		return NameResources[UpperName];
	}

	inline static std::shared_ptr<ResType> CreateResUnName()
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		UnNameResources.push_back(NewRes);
		return NewRes;
	}

protected:

private:

	static std::map<std::string, std::shared_ptr<ResType>> NameResources;

	static std::list<std::shared_ptr<ResType>> UnNameResources;

	std::map<std::string, ResType*> Resources;
};

// 템플릿 static 변수를 선언하는 방법을 배워야 한다.
template<typename ResTYpe>
std::map<std::string, std::shared_ptr<ResTYpe>> UEngineResources<ResTYpe>::NameResources;

template<typename ResType>
std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;