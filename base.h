#ifndef SHUAI_BASE_BLOCK
#define SHUAI_BASE_BLOCK
#include "stdafx.h"
using namespace std;
///////////////////////////////////////////////////////////////////////
//////画布和形状由Cell组成
class CCell
{
public:
	CCell(bool exist=false,COLORREF color=0x000000ff);

	void DrawCell(HDC hdc,int cellsize);
	void DrawRect(HDC hdc,int l, int t, int r, int b);

public:

	int m_row;
	int m_column;

	COLORREF m_color;
	bool m_exist;
};
////////////////////////////////////////////////////////////////////
/////////画布负责更新背景
class CPlate
{
public:
	CPlate(int length,int width,int m_cellsize);
	~CPlate();

public:
	void GetPlate(int &length,int &width,int &m_cellsize,CCell **&pPlate);
	void Draw(HDC hdc);
	bool OutBound();


public:
	 virtual void UpDate(HDC hdc)=0;
    
protected:
	CCell **m_pPlate;
protected:	
	int m_length;
	int m_width;
	int m_cellsize;

};
//////////////////////////////////////////////////////////////////////////
class CBlockPlate:public CPlate
{
public:

	CBlockPlate(int length=21,int width=12,int m_cellsize=20);
	void UpDate(HDC hdc);

};

///////////////////////////////////////////////////////////////////////////
//////////shape抽象基类
class CShape
{
public:
	CShape(CPlate &plate,int m_number);

public:
	virtual void Draw(HDC hdc)=0;
	virtual void ChangeShape(int n=1)=0;
	virtual void Initialize()=0;

public:
	bool UpMove();
	bool LeftMove();
	bool RightMove();
	bool DownMove();
	bool RapidMove();
	void SetPlate();


protected:
	bool TestUpBound();
	bool TestLeftBound();
	bool TestRightBound();
	bool TestDownBound();

protected:
	const int m_number;
	int m_length;
	int m_width;
	int m_state;
   int m_cellsize;
	CCell *m_pShape;
	CPlate &m_cPlate;
	CCell **m_pPlate;
   

};
////////////////////////////////////////////////////////////////
class CL:public CShape
{
 public:

	CL(CPlate &plate,int number=4);
	~CL();
public:
   void Draw(HDC hdc);
   void ChangeShape(int n=1);
   void Initialize();


};
//////////////////////////////////////////////////////////////////////
class CS:public CShape
{
public:
	CS(CPlate &plate,int number=4);
	~CS();
public:
   void Draw(HDC hdc);
   void ChangeShape(int n=1);
   void Initialize();
};
/////////////////////////////////////////////////////////////////////
class CI:public CShape
{
public:
	CI(CPlate &plate,int number=4);
	~CI();
public:
   void Draw(HDC hdc);
   void ChangeShape(int n=1);
   void Initialize();
};
//////////////////////////////////////////////////////////////////////
class CSquare:public CShape
{
public:
	CSquare(CPlate &plate,int number=4);
	~CSquare();
public:
   void Draw(HDC hdc);
   void ChangeShape(int n=1);
   void Initialize();
};
/////////////////////////////////////////////////////////////////////
class CT:public CShape
{
public:
	CT(CPlate &plate,int number=4);
	~CT();
public:
   void Draw(HDC hdc);
   void ChangeShape(int n=1);
   void Initialize();
};
///////////////////////////////////////////////////////////////////////
/////////产生随机数
int Random(int n);
#endif