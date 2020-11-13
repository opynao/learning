#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>
#define LOGF std::cerr << __FUNCTION__ << std::endl

using matrixElement_t = int;
using vMatrix_t = std::vector<std::vector<int>>;
using row_t = int;
using col_t = int;

//--------------------CLASS-INTERFACE-------------------------

class Matrix
{
public:
	Matrix();
	Matrix(row_t,col_t);
	void Reset( row_t, col_t);
	matrixElement_t At (row_t,col_t) const;
	matrixElement_t& At(row_t,col_t);
	row_t GetNumRows() const;
	col_t GetNumColumns() const;
	void matrixInit();
	void Dump(std::ostream& os) const;
	void MatrixInitialization(int num);
	void Input(std::istream&);
private:
	row_t num_rows {};
	col_t num_cols {};
	vMatrix_t vMatrix {};
};

//------------------MEMBER-FUNCTIONS----------------------------

Matrix::Matrix() {}


Matrix::Matrix(row_t nRows,col_t nCols)
	: num_rows {nRows}
	, num_cols {nCols}
{
	if(nRows < 0 || nCols < 0)
		throw std::out_of_range("");
	matrixInit();
}


void Matrix::matrixInit()
{
	if(num_rows < 0 || num_cols < 0)
		throw std::out_of_range("");
	vMatrix.resize(num_cols,{});
	std::for_each(vMatrix.begin(),vMatrix.end(),[this] (decltype(vMatrix)::reference vRows)	{ vRows.resize(num_rows,0); } );
}


void Matrix::Reset(row_t nRows,col_t nCols)
{
	if(nRows < 0 || nCols < 0)
		throw std::out_of_range("");
	num_rows = nRows;
	num_cols = nCols;
	vMatrix.clear();
	matrixInit();
}


matrixElement_t Matrix::At(row_t nRow,col_t nCol) const
{
	if(nCol < 0 || nRow < 0)
		throw std::out_of_range("");
	if(nCol > vMatrix.size() || nRow > vMatrix.at(nCol).size())
		throw std::out_of_range("");
	return vMatrix.at(nCol).at(nRow);
}


matrixElement_t& Matrix::At(row_t nRow, col_t nCol)
{
	if(nCol < 0 || nRow < 0)
		throw std::out_of_range("");
	if(nCol > vMatrix.size() || nRow > vMatrix.at(nCol).size())
		throw std::out_of_range("");
	return vMatrix.at(nCol).at(nRow);
}


row_t Matrix::GetNumRows() const
{
	return num_rows;
}


col_t Matrix::GetNumColumns() const
{
	return num_cols;
}

void Matrix::MatrixInitialization(int num)
{
	for(size_t i = 0; i != num_cols; ++i)
	{
		for(size_t j = 0; j != num_rows; ++j)
			At(j,i) = num;
	}
}


//-------------------------OVERLOADED-OPERATOR-----==-----------------------

bool operator == (const Matrix& lhs,const Matrix& rhs)
{
	row_t rowNumberFirst = lhs.GetNumRows();
	col_t colNumberFirst = lhs.GetNumColumns();
	row_t rowNumberSecond = rhs.GetNumRows();
	col_t colNumberSecond = rhs.GetNumColumns();
	if((rowNumberFirst == 0 || colNumberFirst == 0) && (rowNumberSecond == 0 || colNumberSecond == 0))
		return true;

	bool resultRow = (lhs.GetNumRows() == rhs.GetNumRows());
	bool resultCol = (lhs.GetNumColumns() == rhs.GetNumColumns());
	if(!resultRow || !resultCol)
		return false;
	row_t rowNumber = lhs.GetNumRows();
	col_t colNumber = lhs.GetNumColumns();
	for(size_t i = 0; i != colNumber; ++i)
	{
		for(size_t j = 0; j != rowNumber; ++j)
		{
			if (lhs.At(j,i) != rhs.At(j,i))
				return false;
		}
	}
	return true;
}

//-----------------------OVERLOADED-OPERATOR-+------------------------------------


Matrix operator + (const Matrix& first, const Matrix& second)
{
	row_t rowNumberFirst = first.GetNumRows();
	col_t colNumberFirst = first.GetNumColumns();
	row_t rowNumberSecond = second.GetNumRows();
	col_t colNumberSecond = second.GetNumColumns();
	Matrix empty(0,0);
	if((rowNumberFirst == 0 || colNumberFirst == 0) && (rowNumberSecond == 0 || colNumberSecond == 0))
		return empty;
	bool resultRow = (first.GetNumRows() == second.GetNumRows());
	bool resultCol = (first.GetNumColumns() == second.GetNumColumns());
//	std::stringstream ss;
//	ss << "first = [" << first.GetNumRows() << ", " << first.GetNumColumns() << "]";
//	ss << " second = [" << second.GetNumRows() << ", " << second.GetNumColumns() << "]";
	
	if(!resultRow || !resultCol)
		throw std::invalid_argument("");
	Matrix result(rowNumberFirst,colNumberFirst);
        for(size_t i = 0; i != colNumberFirst; ++i)
	{
		for(size_t j = 0; j != rowNumberFirst; ++j)
			result.At(j,i) = first.At(j,i) + second.At(j,i);
	}
	return result;	
}

//-----------------OVERLOADED-OPERATOR-<<--------------

void Matrix::Dump(std::ostream& os) const
{
	os << num_rows << ' ' << num_cols << std::endl;
	for(size_t i = 0; i != num_rows; ++i)
	{
		for(size_t j = 0; j != num_cols; ++j)
		{
			os << At(i,j);
			if( j != num_cols-1)
				os << ' ';
		}
		if(i != num_rows - 1)
			os << std::endl;
	}
	
}

std::ostream& operator << (std::ostream& os, const Matrix& matrix)
{
	matrix.Dump(os);
	return os;
}

//-------------------OVERLOADED-OPERATOR->>----------------------

void Matrix::Input(std::istream& is)
{
	is >> num_rows;
	is >> num_cols;
	matrixInit();
	for( size_t row = 0; row != num_rows; ++row )
	{
		for( size_t col = 0; col != num_cols; ++col )
		{
			int val{};
			is >> val;
			At(row,col) = val;
		}
	}
}


std::istream& operator >> (std::istream& is, Matrix& matrix)
{
	matrix.Input(is);
	return is;
}

//---------------------TESTS-----------------------------

void testDefaultConstruct_RowsZero()
{
	LOGF;
	Matrix matrix;
	assert(0 == matrix.GetNumRows());
}

void testDefaultConstruct_ColumnsZero()
{
	LOGF;
	Matrix matrix;
	assert(0 == matrix.GetNumColumns());
}

void testConstruct_RowsThree()
{
	LOGF;
	Matrix matrix(3,2);
	assert(3 == matrix.GetNumRows());
}

void testConstruct_ColumnsTwo()
{
	LOGF;
	Matrix matrix(3,2);
	assert(2 == matrix.GetNumColumns());
}

void testConstructMatrix_AtReturnsZero()
{
	LOGF;
	Matrix matrix(2,3);
	assert(0 == matrix.At(1,1));
}


void testResetMatrix_RowsFour()
{
	LOGF;
	Matrix matrix(3,2);
	matrix.Reset(4,5);
	assert(4 == matrix.GetNumRows());
}

void testResetMatrix_ColumnsFive()
{
	LOGF;
	Matrix matrix(3,2);
	matrix.Reset(4,5);
	assert(5 == matrix.GetNumColumns());
}

void testResetMatrix_AtReturnsZero()
{
	LOGF;
	Matrix matrix(3,2);
	matrix.Reset(4,5);
	assert(0 == matrix.At(2,3));
}

void testResetMatrix_AtThrowsExceptionOutOfRange()
{
	LOGF;
	bool bIsExceptionCatched {false};
	Matrix matrix(3,2);
	try
	{
		matrix.Reset(-6,-7);
	}
	catch(std::out_of_range&)
	{
		bIsExceptionCatched = true;
	}
	assert(true == bIsExceptionCatched);
}

void testOperatorEqual_TwoMatrixAreNotEqual()
{
	LOGF;
	Matrix first(1,2);
	Matrix second(2,1);
	assert(false == (first == second));
}

void testOperatorEqual_TwoNonZeroMatrixAreEqual()
{
	LOGF;
	Matrix first(1,2);
	Matrix second(1,2);
	assert(first == second);
}

void testOperatorMatrixOutput()
{
	LOGF;
	Matrix m(2,2);
	const std::string result {"2 2\n0 0\n0 0"};
	std::stringstream os;
	os << m;
	assert(result == os.str());
}

void testSumOfTwoMatrix()
{
	LOGF;
	Matrix first(2,2);
	Matrix second(2,2);
	first.MatrixInitialization(1);
	second.MatrixInitialization(2);
	Matrix result = first + second;
	assert(3 == result.At(0,0)); 
}

void testOutputOperator_MatrixWithDifferentDimensions()
{
	LOGF;
	Matrix matrix(3,2);
	matrix.At(0,0) = 1;
	matrix.At(0,1) = 2;
	matrix.At(1,0) = 3;
	matrix.At(1,1) = 4;
	matrix.At(2,0) = 5;
	matrix.At(2,1) = 6;
	const std::string result {"3 2\n1 2\n3 4\n5 6"};
	std::stringstream os;
	os << matrix;
	assert(result == os.str());
}

void testMatrixInputOperator()
{
	LOGF;
	std::string input {"2 2\n1 2\n3 4"};
	Matrix matrix;
	std::stringstream is;
	is.str(input);
	is >> matrix;
	

	Matrix result(2,2);
	result.At(0,0) = 1;
	result.At(0,1) = 2;
	result.At(1,0) = 3;
	result.At(1,1) = 4;

	assert(2 == matrix.GetNumRows());
	assert(2 == matrix.GetNumColumns());
	assert(result == matrix);
}

void testAtWithNegativeArgsThrowOutOfRange_Exception()
{
	LOGF;
	Matrix matrix(3,3);
	bool isExceptionCatched {false};
	try
	{
		matrix.At(-1,2);
	}
	catch(std::out_of_range&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);
	isExceptionCatched = false;
	try
	{
		matrix.At(2,-1);
	}
	catch(std::out_of_range&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);
	try
	{
		matrix.At(-1,-1);
	}
	catch(std::out_of_range&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);
}


void testMatrixConcatenationOperatorThrowsExceptionIfBothMatrixHaveDifferentDimensions()
{
	LOGF;
	Matrix first(1,2);
	Matrix second(3,2);
	bool isExceptionCatched {false};
	try
	{
		Matrix result =	first + second;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);
	
	first.Reset(1,2);
	second.Reset(1,1);
	isExceptionCatched = false;
	try
	{
		Matrix result =	first + second;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);

	first.Reset(1,2);
	second.Reset(3,4);
	isExceptionCatched = false;
	try
	{
		Matrix result =	first + second;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(true == isExceptionCatched);
}

void testMatrixConcatenationOperatorDoesNotThrowExceptionIfMatrixEmpty()
{
	Matrix first(0,0);
	Matrix second(0,1);
	Matrix third(1,0);
	bool isExceptionCatched {false};
	try
	{
		Matrix result = first + second;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(false == isExceptionCatched);

	isExceptionCatched = false;
	try
	{
		Matrix result = first + third;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(false == isExceptionCatched);

	isExceptionCatched = false;
	try
	{
		Matrix result = second + third;
	}
	catch(std::invalid_argument&)
	{
		isExceptionCatched = true;
	}
	assert(false == isExceptionCatched);

}

void testMatrixComparisonOperatorOfEmptyMatrixReturnsTrue()
{
	Matrix first(0,0);
	Matrix second(0,1);
	Matrix third(1,0);
	bool result = (first == second);
	assert(true == result);

	result = true;
	result = (first == third);
	assert(true == result);

	result = true;
	result = (second == third);
	assert(true == result);
}


//--------------------MAIN-------------------------------

int main() 
{
/*	Matrix one;
	Matrix two;
	std::cin >> one >> two;
	std::cout << one + two << std::endl;
*/

	//TESTS
/*	testDefaultConstruct_RowsZero();
	testDefaultConstruct_ColumnsZero();
	testConstruct_RowsThree();
	testConstruct_ColumnsTwo();
	testConstructMatrix_AtReturnsZero();
	testResetMatrix_RowsFour();
	testResetMatrix_ColumnsFive();
	testResetMatrix_AtReturnsZero();
	testResetMatrix_AtThrowsExceptionOutOfRange();
	testOperatorEqual_TwoMatrixAreNotEqual();
	testOperatorEqual_TwoNonZeroMatrixAreEqual();
	testOperatorMatrixOutput();
	testSumOfTwoMatrix();
	testOutputOperator_MatrixWithDifferentDimensions();
	testMatrixInputOperator();
	testAtWithNegativeArgsThrowOutOfRange_Exception();
	testMatrixConcatenationOperatorThrowsExceptionIfBothMatrixHaveDifferentDimensions();
	testMatrixConcatenationOperatorDoesNotThrowExceptionIfMatrixEmpty();
	testMatrixComparisonOperatorOfEmptyMatrixReturnsTrue();
*/
	//MAIN
		
	return 0;
}
