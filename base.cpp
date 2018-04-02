#include "stdafx.h"
#include "base.h"

int Random(int n)
{
	srand( (unsigned)GetTickCount( ));
	return rand()%n;
}
//////////////////////////////////////////////////////////////////
CCell::CCell(bool exist,COLORREF color)
:m_exist(exist),m_color(color)
{
}

void CCell::DrawCell(HDC hdc,int cellsize)
{  
	int l=m_column*cellsize;
	int t=m_row*cellsize;
	int r=(m_column+1)*cellsize;
	int b=(m_row+1)*cellsize;
	DrawRect (hdc,l+1, t+1, r-1, b-1);
	DrawRect (hdc,l+3, t+3, r-3, b-3);
}
void CCell::DrawRect(HDC hdc,int l, int t, int r, int b)
{
	MoveToEx (hdc, l, t, NULL);
	LineTo (hdc, r, t);
	LineTo (hdc, r, b);
	LineTo (hdc, l, b);
	LineTo (hdc, l,t);

}
/////////////////////////////////////////////////////////////////////
CPlate::CPlate(int length, int width,int cellsize):m_length(length),m_width(width),m_cellsize(cellsize)
{

	m_pPlate=new CCell*[m_length];

	for(int i=0;i<m_length;i++)
	{
		m_pPlate[i]=new CCell[m_width];
	}
	for(int i=0;i<m_length;i++)
		for(int j=0;j<m_width;j++)
		{
			m_pPlate[i][j].m_row=i;
			m_pPlate[i][j].m_column=j;
			m_pPlate[i][j].m_exist=false;
			m_pPlate[i][j].m_color=0x00ffffff;

		}

}
CPlate::~CPlate()
{
	for (int i = 0; i < m_length; i++)
	{
		delete [] m_pPlate[i];
	}
	delete [] m_pPlate;
}

void CPlate::GetPlate(int &length,int &width,int &cellsize,CCell **&pPlate)
{
	length=m_length;
	width=m_width;
	cellsize=m_cellsize;
	pPlate=m_pPlate;

}
void CPlate::Draw(HDC hdc)
{
	for(int i=0;i<m_length;i++)
		for(int j=0;j<m_width;j++)
		{
			if(m_pPlate[i][j].m_exist==true)
			{
				m_pPlate[i][j].DrawCell(hdc,m_cellsize);
			}
		}


}
bool CPlate::OutBound()
{
	for(int i=0;i<m_width;i++)
	{

		if(m_pPlate[0][i].m_exist==true)
		{
			return true;
		}		
	}
	return false;
}



/////////////////////////////////////////////////////////////////////////////////

CBlockPlate::CBlockPlate(int length,int width,int cellsize):CPlate(length,width,cellsize){}

void CBlockPlate::UpDate(HDC hdc)
{	
	int i,j;
	bool flag=false;
	for(i=m_length-1;i>=0;i--)
	{

		for(j=m_width-1;j>=0;j--)
		{
			if(m_pPlate[i][j].m_exist!=true)
			{
				break;					
			}
			if(j==0)
			{
				flag=true;
			}
		}	
		if(flag)
		{
			flag=false;

			int n=m_width-1;
			for(int m=i;m>0;m--){
				n=m_width-1;
				for(;n>=0;n--)
				{
					m_pPlate[m][n]=m_pPlate[m-1][n];
					m_pPlate[m][n].m_row++;
				}
			}
			i++;
		}

	}
	Draw(hdc);

}
//////////////////////////////////////////////////////////////////////////////////
CShape::CShape(CPlate &plate,int number):m_cPlate(plate),m_number(number)
{   
	m_state=0;
	plate.GetPlate(m_length,m_width,m_cellsize,m_pPlate);
}


bool CShape::TestLeftBound()
{
	for(int i=0;i<m_number;i++){
		if(m_pPlate[(m_pShape+i)->m_row][(m_pShape+i)->m_column-1].m_exist==true||(m_pShape+i)->m_column==0)
		{return false;}

	}
	return true;
}
bool CShape::TestRightBound()
{

	for(int i=0;i<m_number;i++){
		if(m_pPlate[(m_pShape+i)->m_row][(m_pShape+i)->m_column+1].m_exist==true||(m_pShape+i)->m_column+1==m_width)
		{return false;}

	}
	return true;

}
bool CShape::TestDownBound()
{
	for(int i=0;i<m_number;i++)
	{
		if((m_pShape+i)->m_row==m_length-1||m_pPlate[(m_pShape+i)->m_row+1][(m_pShape+i)->m_column].m_exist==true)
		{
			return false;
		}

	}
	return true;
}
bool CShape::TestUpBound()
{
	for(int i=0;i<m_number;i++)
	{
		if((m_pShape+i)->m_row==0||m_pPlate[(m_pShape+i)->m_row-1][(m_pShape+i)->m_column].m_exist==true)
		{
			return false;
		}

	}
	return true;

}
bool CShape::UpMove()
{
	if(TestUpBound()){
		int n=m_number;
		for(int i=0;i<m_number;i++)
		{
			m_pShape[i].m_row--;
		}
		return true;
	}
	return false;

}

bool CShape:: LeftMove()
{
	if(TestLeftBound()){
		int n=m_number;
		for(int i=0;i<m_number;i++)
		{
			m_pShape[i].m_column--;
		}
		return true;
	}
	return false;
}
bool CShape::RightMove()
{
	if(TestRightBound()){
		int n=m_number;
		for(int i=0;i<m_number;i++)
		{
			m_pShape[i].m_column++;
		}
		return true;
	}
	return false;
}
bool CShape::DownMove()
{
	if(TestDownBound()){
		int n=m_number;
		for(int i=0;i<m_number;i++)
		{
			m_pShape[i].m_row++;
		}
		return true;
	}
	return false;
}
bool CShape::RapidMove()
{



	return false;
}
void CShape::SetPlate()
{
	int m,n;
	for(int i=0;i<m_number;i++)
	{
		m=m_pShape[i].m_row;
		n=(m_pShape+i)->m_column;
		m_pPlate[m][n].m_exist=true;
		m_pPlate[(m_pShape+i)->m_row][(m_pShape+i)->m_column].m_color=0x00ffffff;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
CL::CL(CPlate &plate,int number):CShape(plate,number)
{
	m_pShape=new CCell[m_number];  

}
CL::~CL()
{
	delete []m_pShape;                                        ////¨ˆ¨ˆ      
}                                                            //¨ˆ
                                                             //¨ˆ

void CL::ChangeShape(int n)
{
	CCell shape[4]={m_pShape[0],m_pShape[1],m_pShape[2],m_pShape[3]};
	for(int i=0;i<n;i++){
		if(shape[1].m_row>shape[0].m_row)
			if(shape[1].m_column<shape[0].m_column)
				shape[1].m_row-=2;
			else
				shape[1].m_column-=2;
		else
			if(shape[1].m_column>shape[0].m_column)
				shape[1].m_row+=2;
			else
				shape[1].m_column+=2;

		for(int m=2;m<4;m++){
			if(shape[m].m_row==shape[0].m_row)
				if(shape[m].m_column<shape[0].m_column)
				{shape[m].m_row-=1;shape[m].m_column+=1;}
				else
				{shape[m].m_row+=1;shape[m].m_column-=1;}
			else
				if(shape[m].m_row>shape[0].m_row)
				{shape[m].m_row-=1;shape[m].m_column-=1;}
				else
				{shape[m].m_row+=1;shape[m].m_column+=1;}
		}

	}
	int c=0;
	for(int m=0;m<m_number;m++){
		if(!((shape+m)->m_column<0||(shape+m)->m_column>m_width-1||(shape+m)->m_row>m_length-1||(shape+m)->m_row<0||m_pPlate[(shape+m)->m_row][(shape+m)->m_column].m_exist==true))
		{
          c++;			
		}	
	
	}	
	if(c==4){
		m_pShape[0]=shape[0];
		m_pShape[1]=shape[1];
		m_pShape[2]=shape[2];
		m_pShape[3]=shape[3];
		}
	/*if(m_pShape[0].m_row==m_pShape[2].m_row&&m_pShape[0].m_row==m_pShape[3].m_row&&m_pShape[0].m_row<m_pShape[1].m_row)
	{
		for(int i=0;i<m_number;i++)
		{
			m_pShape[i].m_row--;
		}
	}*/
}

void CL::Initialize()
{
	m_pShape[0].m_column=m_width/2-1;      m_pShape[0].m_row=1;             //
	m_pShape[1].m_column=m_width/2-2;    m_pShape[1].m_row=0;            // ¨ˆ¨ˆ¨ˆ
	m_pShape[2].m_column=m_width/2-2;    m_pShape[2].m_row=1;            //     ¨ˆ	
	m_pShape[3].m_column=m_width/2;      m_pShape[3].m_row=1;
	if(1== Random(2))
	{
		m_pShape[1].m_column+=2;  
	}
	m_state=Random(m_number);
	if(m_state!=0)
		ChangeShape(m_state);
}

void CL::Draw(HDC hdc)
{
	for(int i=0;i<m_number;i++)
	{
		(m_pShape+i)->DrawCell(hdc,m_cellsize);
	} 
}
////////////////////////////////////////////////////////////////////////////////
CT::CT(CPlate &plate,int number):CShape(plate,number)
{
	m_pShape=new CCell[m_number];  

}
CT::~CT()
{                                                           //   
	delete []m_pShape;                                        ////¨ˆ¨ˆ¨ˆ     
}                                                         //     ¨ˆ
void CT::Draw(HDC hdc)
{
	for(int i=0;i<m_number;i++)
	{
		(m_pShape+i)->DrawCell(hdc,m_cellsize);
	} 
}
void CT::ChangeShape(int n)
{
	CCell shape[4]={m_pShape[0],m_pShape[1],m_pShape[2],m_pShape[3]};
	for(int i=0;i<n;i++)
	{
		if(shape[2].m_row<shape[0].m_row)                  //     ¨ˆ
		{	                                                  ////¨ˆ¨ˆ  
			shape[1].m_row--;shape[1].m_column++;             //    ¨ˆ
			shape[2].m_row++;shape[2].m_column++;
			shape[3].m_row++;shape[3].m_column--;

			break;
		}
		if(shape[2].m_row>shape[0].m_row)
		{	
			shape[1].m_row++;shape[1].m_column--;
			shape[2].m_row--;shape[2].m_column--;
			shape[3].m_row--;shape[3].m_column++;

			break;
		}
		if(shape[2].m_column>shape[0].m_column)
		{	
			shape[1].m_row++;shape[1].m_column++;
			shape[2].m_row++;shape[2].m_column--;
			shape[3].m_row--;shape[3].m_column--;

			break;
		}
		if(shape[2].m_column<shape[0].m_column)
		{	
			shape[1].m_row--;shape[1].m_column--;
			shape[2].m_row--;shape[2].m_column++;
			shape[3].m_row++;shape[3].m_column++;

			break;
		}


	}
	int c=0;
	for(int m=0;m<m_number;m++){
		if(!((shape+m)->m_column<0||(shape+m)->m_column>m_width-1||(shape+m)->m_row>m_length-1||(shape+m)->m_row<0||m_pPlate[(shape+m)->m_row][(shape+m)->m_column].m_exist==true))
		{
			c++;			
		}	

	}	
	if(c==4){
		m_pShape[0]=shape[0];
		m_pShape[1]=shape[1];
		m_pShape[2]=shape[2];
		m_pShape[3]=shape[3];
	}
}
void CT::Initialize()
{
	m_pShape[0].m_column=m_width/2-1;    m_pShape[0].m_row=1;             //
	m_pShape[1].m_column=m_width/2-2;    m_pShape[1].m_row=1;            //    ¨ˆ
	m_pShape[2].m_column=m_width/2-1;    m_pShape[2].m_row=0;            ////¨ˆ¨ˆ¨ˆ
	m_pShape[3].m_column=m_width/2;      m_pShape[3].m_row=1;          ///      
	m_state=Random(m_number);
	if(m_state!=0)
		ChangeShape(m_state);
}

//////////////////////////////////////////////////////////////////////////////////
CS::CS(CPlate &plate,int number):CShape(plate,number)
{	
	m_pShape=new CCell[m_number]; 
}
CS::~CS()
{
	delete []m_pShape;   
}
void CS::Draw(HDC hdc)
{
	for(int i=0;i<m_number;i++)
	{
		(m_pShape+i)->DrawCell(hdc,m_cellsize);
	}

}
void CS::ChangeShape(int n)
{
	CCell shape[4]={m_pShape[0],m_pShape[1],m_pShape[2],m_pShape[3]};
	if(shape[0].m_column==shape[1].m_column&&shape[0].m_row<shape[3].m_row)
	{
		shape[1].m_row++;shape[1].m_column++;
		shape[2].m_row--;shape[2].m_column++;
		if(shape[3].m_row>shape[0].m_row)
		{
			shape[3].m_row-=2;
			
		}
		else
		{
			shape[3].m_column+=2;
			
		}
	}
	else
	{	
		if(shape[3].m_column<shape[0].m_column)
		{
			shape[1].m_row--;shape[1].m_column--;
			shape[2].m_row--;shape[2].m_column++;
			shape[3].m_column+=2;

		}
		else
		{
			shape[1].m_row++;shape[1].m_column++;
			shape[2].m_row++;shape[2].m_column--;
			shape[3].m_column-=2;
	
		}


	}
	int c=0;
	for(int m=0;m<m_number;m++){
		if(!((shape+m)->m_column<0||(shape+m)->m_column>m_width-1||(shape+m)->m_row>m_length-1||(shape+m)->m_row<0||m_pPlate[(shape+m)->m_row][(shape+m)->m_column].m_exist==true))
		{
			c++;			
		}	

	}	
	if(c==4){
		m_pShape[0]=shape[0];
		m_pShape[1]=shape[1];
		m_pShape[2]=shape[2];
		m_pShape[3]=shape[3];
	}






}
void CS::Initialize()
{
	m_pShape[0].m_column=m_width/2-1;    m_pShape[0].m_row=1;             //
	m_pShape[1].m_column=m_width/2-1;    m_pShape[1].m_row=0;            //    ¨ˆ   ¨ˆ¨ˆ
	m_pShape[2].m_column=m_width/2-2;    m_pShape[2].m_row=1;            ////¨ˆ¨ˆ	    ¨ˆ¨ˆ
	m_pShape[3].m_column=m_width/2-2;    m_pShape[3].m_row=2;            //  ¨ˆ       
	if(1== Random(2))                                               //
	{                                                             //  ¨ˆ       ¨ˆ¨ˆ
		m_pShape[1].m_row+=2;                                        //  ¨ˆ¨ˆ   ¨ˆ¨ˆ 
		m_pShape[3].m_row-=2;                                       //     ¨ˆ   
	}
	m_state=Random(2);
	if(m_state!=0)
		ChangeShape();


}

///////////////////////////////////////////////////////////////////////////////////
CSquare::CSquare(CPlate &plate,int number):CShape(plate,number)
{
	m_pShape=new CCell[m_number];  
}
CSquare::~CSquare()
{
	delete []m_pShape; 
}
void CSquare::Draw(HDC hdc)
{
	for(int i=0;i<m_number;i++)
	{
		(m_pShape+i)->DrawCell(hdc,m_cellsize);               ////¨ˆ¨ˆ
	}                                                     ///¨ˆ¨ˆ
}
void CSquare::ChangeShape(int n)
{

}
void CSquare::Initialize()
{
	m_pShape[0].m_column=m_width/2-1;    m_pShape[0].m_row=0;            
	m_pShape[1].m_column=m_width/2-2;    m_pShape[1].m_row=0;            
	m_pShape[2].m_column=m_width/2-1;    m_pShape[2].m_row=1;            
	m_pShape[3].m_column=m_width/2-2;    m_pShape[3].m_row=1;             
}
/////////////////////////////////////////////////////////////////////////////////

CI::CI(CPlate &plate,int number):CShape(plate,number)
{
	m_pShape=new CCell[m_number];  
}
CI::~CI()
{
	delete []m_pShape; 
}
void CI::Draw(HDC hdc)
{
	for(int i=0;i<m_number;i++)
	{
		(m_pShape+i)->DrawCell(hdc,m_cellsize);
	}
}
void CI::ChangeShape(int n)
{
	CCell shape[4]={m_pShape[0],m_pShape[1],m_pShape[2],m_pShape[3]};
	for(int i=0;i<n;i++)
	{
		if(shape[1].m_row==shape[0].m_row)
		{
			shape[1].m_row++;shape[1].m_column--;
			shape[2].m_row--;shape[2].m_column++;
			shape[3].m_row-=2;shape[3].m_column+=2;


		}
		else{
			shape[1].m_row--;shape[1].m_column++;
			shape[2].m_row++;shape[2].m_column--;
			shape[3].m_row+=2;shape[3].m_column-=2;

		}
	}
	int c=0;
	for(int m=0;m<m_number;m++){
		if(!((shape+m)->m_column<0||(shape+m)->m_column>m_width-1||(shape+m)->m_row>m_length-1||(shape+m)->m_row<0||m_pPlate[(shape+m)->m_row][(shape+m)->m_column].m_exist==true))
		{
			c++;			
		}	

	}	
	if(c==4){
		m_pShape[0]=shape[0];
		m_pShape[1]=shape[1];
		m_pShape[2]=shape[2];
		m_pShape[3]=shape[3];
	}

}
void CI::Initialize()
{
	m_pShape[0].m_column=m_width/2-1;    m_pShape[0].m_row=1;             // ¨ˆ¨ˆ¨ˆ¨ˆ 
	m_pShape[1].m_column=m_width/2;     m_pShape[1].m_row=1;               
	m_pShape[2].m_column=m_width/2-2;    m_pShape[2].m_row=1;              
	m_pShape[3].m_column=m_width/2-3;    m_pShape[3].m_row=1;              

	m_state=Random(2);
	if(m_state!=0)
		ChangeShape(m_state);
}

//////////////////////////////////////////////////////////////////////////////////
