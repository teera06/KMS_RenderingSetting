#pragma once

class UEngineInputLayOut;
class UEngineMesh;
class UEngineMaterial;

class URenderUnit
{
public:
	void RenderingSetting();
private:

	std::shared_ptr<UEngineInputLayOut> LayOut=nullptr;
	std::shared_ptr<UEngineMesh> Mesh=nullptr;
	std::shared_ptr<UEngineMaterial> Material=nullptr;
};

