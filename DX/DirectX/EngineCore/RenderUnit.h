#pragma once

class UEngineMesh;
class URenderUnit
{
public:
	void RenderingSetting();
private:

	std::shared_ptr<UEngineMesh> Mesh;
};

