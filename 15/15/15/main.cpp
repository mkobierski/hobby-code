#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class Vertex
{
	public:
/*		Vertex()
		{
			cout << "Contructing Vertex." << endl;
			_bEnabled = true;
		} */
	
		Vertex(int nX = 0, int nY = 0)
		{
//			cout << "Constructing Vertex at (x, y): (" 
//				 << nX << ", " << nY << ")." << endl;
			_bEnabled = true;
			_nX = nX;
			_nY = nY;
		}
		
		Vertex(Vertex* v)
		{
//			cout << "Contructing Vertex at from pV at (x, y): (" 
//				 << v->nX() << ", " << v->nY() << ")." << endl;
			_bEnabled = true;
			_nX = v->nX();
			_nY = v->nY();
		}
		
		~Vertex()
		{
//			cout << "Destructing Vertex" << endl;
		}
		
		void setX(int x)
		{
			_nX = x;
		}
		
		void setY(int y)
		{
			_nY = y;
		}
		
		int nX()
		{
			return _nX;
		}
		
		int nY()
		{
			return _nY;
		}
		
		int setOn()
		{
			_bEnabled = true;
		}
		
		int setOff()
		{
			_bEnabled = false;
		}
		
		bool bEnabled()
		{
			return _bEnabled;
		}
		
	protected:
		int _nX, _nY;
		bool _bEnabled;
};

class LSegment;

class Grid
{
	public:
		Grid (int nDimension);
		~Grid();
		int findPath();
		void resetCol(int x);
		void markNextV();
		int calcNumOfPaths();
		int vertexOn(int x, int y);
		int nDimension();
		int displayNumPaths();
		
	protected:
		LSegment* _lSegments;
		Vertex** _vertexPoints;
		int _nDimension;
		unsigned long long _nNumOfPaths;
		
		bool allPathsFound();

};

class LSegment
{
	public:
	
/*		LSegment()
		{
			cout << "Constructing LSegment" << endl;
				 
			_startingVertex = new Vertex(0, 0);
			_grid = 0;
			nID = nNoOfSegments++;
		} */
	
		LSegment(int nX = 0, int nY = 0, Grid* g = 0)
		{
//			cout << "Constructing LSegment starting at (x, y): ("
//				 << nX << ", " << nY << ")." << endl;
				 
			_startingVertex = new Vertex(nX, nY);
			_grid = g;
			nID = nNoOfSegments++;
			nDirection = -1;
		}
		
		void init(int nX, int nY, Grid* g)
		{
//			cout << "Initializing LSegment starting at (" 
//				 << nX << ", " << nY << ")." << endl;
			
			if(_startingVertex)
			{
				delete _startingVertex;
			}
			_startingVertex = new Vertex(nX, nY);
			_grid = g;
			nDirection = nextDirn();
		
		}
			
		
		LSegment(Vertex* startingVertex, Grid* g)
		{
//			cout << "Constructing LSegment from pV starting at (x, y): ("
//				 << startingVertex->nX() << ", " 
//				 << startingVertex->nY() << ")." << endl;
				 
			_startingVertex = new Vertex(startingVertex);
			_grid = g;
			nID = nNoOfSegments++;
			nDirection = nextDirn();
		}
		
		~LSegment()
		{
//			cout << "Destructing LSegment id: " << nID << endl;
			nNoOfSegments--;
			delete _startingVertex;
			_startingVertex = 0;
			
		}
		
		int getnDirection()
		{
			return nDirection;
		}
		
	
	protected:		
		Vertex* _startingVertex;
		Vertex* _endingVertex;
		Grid* _grid;
		int nDirection; //0 is horizontal, 1 is vertical
		int nID;
		static int nNoOfSegments;
		
		int nextDirn()
		{
			if(_startingVertex->nX() == _grid->nDimension())
			{
				return 1;
			}
			if(!(_grid->vertexOn(_startingVertex->nX() + 1, _startingVertex->nY())))
			{
				return 1;
			}
			return 0;
		}
};

int LSegment::nNoOfSegments = 0;


Grid::Grid (int nDimension)
{
	_nDimension = nDimension;
	
	
	
//		_vertexPoints = new Vertex[_nDimension + 1][_nDimension + 1];
	_vertexPoints = new Vertex*[nDimension + 1];
	for(int i = 0; i < nDimension + 1; i++)
	{
		_vertexPoints[i] = new Vertex[nDimension + 1];
	}
	
	_lSegments = new LSegment[2*nDimension];
	
	for(int i = 0, j = 0; j < (nDimension + 1);)
	{
		_vertexPoints[i][j].setX(i);
		_vertexPoints[i][j].setY(j);
		if (i >= nDimension)
		{
			i = 0;
			j++;
		}
		else
		{
			i++;
		}
	}
	
}

Grid::~Grid()
{
	for(int i = 0; i < _nDimension + 1; i++)
	{
		delete []_vertexPoints[i];
	}
	delete []_vertexPoints;

	delete []_lSegments;

	
	_vertexPoints = 0;
	_lSegments = 0;
}

int Grid::findPath() //while tracking highest rightmost point
{
	int x, y, nLSegCt;
	x = y = nLSegCt = 0;
	while(nLSegCt < _nDimension * 2)
	{
		_lSegments[nLSegCt].init(x, y, this);
		if( _lSegments[nLSegCt].getnDirection() == 0) //horizontal
		{
			x++;
		}
		else //vertical
		{
			y++;
		}
		nLSegCt++;
	}
	return 1;
}

void Grid::resetCol(int x)
{
	for(int i = 0; i <= _nDimension; i++)
	{
		_vertexPoints[x][i].setOn();
	}
}

void Grid::markNextV()
{
	int x, y;
	x = y = _nDimension;
	bool bFound = false;
	while(!bFound && x >= 0 && y >= 0)
	{
		for (int i = 0; i < x; i++)
		{
			if(y== _nDimension && _vertexPoints[i][y-1].bEnabled() == false)
			{
				x = i;
			}
		}
		if(y == _nDimension && _vertexPoints[x][y-1].bEnabled() == false)
		{
			resetCol(x);
			x--;
		}
		else
		{
			bool bAboveRowDis = false;
			if(y == 0)
			{
				bAboveRowDis = true;
			}
			else
			{
				for(int i = x; i > 0; i--)
				{
					if(_vertexPoints[i][y-1].bEnabled() == false)
					{
						bAboveRowDis = true;
					}
				}
			}
			if(bAboveRowDis)
			{
				_vertexPoints[x][y].setOff();
				bFound = true;
			}
			else
			{
				y--;
			}
		}
	}			
}

int Grid::calcNumOfPaths()
{
//	long long loopcount = 0;
	_nNumOfPaths = 0;
	do
	{
//		if(findPath())
//		{
//			_nNumOfPaths++;
//		}
		
		_nNumOfPaths++;
		markNextV();
		
//		loopcount++;
		
		if(!(_nNumOfPaths%10))
		{
			cout << "n. ";
			cout.width(13);
			cout << _nNumOfPaths << "  ";
			if(!(_nNumOfPaths % 40))
			{
				cout << endl;
			}
		}
		

		
	} while(!allPathsFound() /*&& loopcount < 2000000000*/);
//	_nNumOfPaths++; //There is one more path left to find...
					//    ... it isn't calculated.
}

int Grid::vertexOn(int x, int y)
{
	return _vertexPoints[x][y].bEnabled();
}

int Grid::nDimension()
{
	return _nDimension;
}

int Grid::displayNumPaths()
{
	cout << "The " << _nDimension << "x" << _nDimension
		 << " grid has " << _nNumOfPaths << " possible paths."
		 << endl;
}


bool Grid::allPathsFound()
{
	if(vertexOn(0,0))
	{
		return 0;
	}
	return 1;
}
		




int main (int argc, char *argv[])
{
	cout << "Making someGrid in main" << endl;
	Grid someGrid(20);
	cout << "Calculating Paths in main" << endl;
	someGrid.calcNumOfPaths();
	cout << endl << "Displaying Paths in main" << endl;
	someGrid.displayNumPaths();
	
	
	return 0;
}

