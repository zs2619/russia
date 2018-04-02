#include "stdafx.h"
#include "CShapeFactory.h"
void CShapeFactory::AddShape(CShape *shape)
{

	m_shape.push_back(shape);

}
CShape* CShapeFactory::RandomShape()
{
	int n=(int)m_shape.size();

	return  m_shape[Random(n)];

}
