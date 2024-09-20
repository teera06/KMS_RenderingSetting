#pragma once
#include <string>
#include <map>
#include "EngineBase/PathObject.h"
// Ό³Έν :
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

protected:

private:
	std::map<std::string, ResType*> Resources;
};

