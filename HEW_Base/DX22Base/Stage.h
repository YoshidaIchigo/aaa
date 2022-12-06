#pragma once
#include<DirectXMath.h>
#include"Geometory.h"
class Stage
{
public:
	Stage();
	~Stage();
	void Draw();
private:
	Info* m_pBlocks;
	int m_pBlockNum;

};

