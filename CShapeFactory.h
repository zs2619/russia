#ifndef SHUAI_BASE_BLOCK_CShapeFactory
#define SHUAI_BASE_BLOCK_CShapeFactory
#include "stdafx.h"
#include "base.h"
///////////////////////////////////
/////////Ëæ»ú²úÉúshape
class CShapeFactory
{
public:
	
	void AddShape(CShape *shape);
	CShape* RandomShape();
private:
	vector<CShape*> m_shape;
};
#endif