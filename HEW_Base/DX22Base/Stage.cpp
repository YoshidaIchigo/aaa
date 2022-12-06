#include "Stage.h"
#include"Geometory.h"
const int STAGE_BLOCK_NUM = 1;
Stage::Stage()
	:m_pBlocks(nullptr)
	,m_pBlockNum(STAGE_BLOCK_NUM)
{
	m_pBlocks = new Info[STAGE_BLOCK_NUM];
	//for (int i = 0; i < m_pBlockNum; i++)
	//{
	//	m_pBlocks[i].pos = { 0.0f, 0.0f, 0.0f };
	//	m_pBlocks[i].rot = { 0.0f, 0.0f, 0.0f };
	//	m_pBlocks[i].size = { 1.0f, 1.0f, 1.0f };
	//}

	m_pBlocks[0].pos = { 0.0f, 0.0f, 0.0f };
	m_pBlocks[0].size = { 20.0f, 1.0f, 20.0f };

	//m_pBlocks[1].pos = { 3.5f, 1.0f, 0.0f };
	//m_pBlocks[1].size = { 2.0f, 1.0f, 4.0f };

	//m_pBlocks[2].pos = { 3.5f, 1.5f, 3.0f };
	//m_pBlocks[2].size = { 2.0f, 2.0f, 2.0f };

	//m_pBlocks[3].pos = { -1.0f, 1.5f, 2.0f };
	//m_pBlocks[3].size = { 7.0f, 2.0f, 4.0f };

	//m_pBlocks[4].pos = { -1.5f, 2.0f, 5.5f };
	//m_pBlocks[4].size = { 6.0f, 5.0f, 3.0f };

	//m_pBlocks[5].pos = { 3.0f, 3.0f, 5.5f };
	//m_pBlocks[5].size = { 1.0f, 1.0f, 1.0f };

	//m_pBlocks[6].pos = { -3.5f, 2.5f, 4.0f };
	//m_pBlocks[6].size = { 2, 2.0f*sqrtf(2), 2.0f*sqrtf(2) };
	//m_pBlocks[6].rot = { 3.14f/4.0f, 0.0f, 0.0f };
	//for (int i = 0; i < 7; i++)
	//{
	//	m_pBlocks[i].pos.x += 4.5f;
	//	m_pBlocks[i].pos.y += 0.5f;
	//	m_pBlocks[i].pos.z += 4.0f;
	//}
}

Stage::~Stage()
{
	delete[] m_pBlocks;
}

void Stage::Draw()
{
	for (int i = 0; i < m_pBlockNum; i++)
	{
		SetGeometoryTranslate(m_pBlocks[i].pos);
		SetGeometoryRotation(m_pBlocks[i].rot);
		SetGeometoryScaling(m_pBlocks[i].size);
		DrawBox();
	}
}
