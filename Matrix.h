#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
public:
	Matrix(size_t rows, size_t cols, T initial)
	{
		mRows = rows;
		mCols = cols;
		mData.resize(rows);

		for (size_t i = 0; i < mData.size(); i++)
			mData[i].resize(cols, initial);
	}

	Matrix(const Matrix<T>& other)
	{
		mRows = other.Rows();
		mCols = other.Cols();
		mData.resize(mRows);

		for (size_t i = 0; i < mData.size(); i++)
			mData[i].resize(mCols);

		for (size_t i = 0; i < mRows; i++)
		{
			for (size_t j = 0; j < mCols; j++)
				this->mData[i][j] = other(i, j);
		}
	}

	~Matrix() {}


	Matrix<T> operator+(const Matrix<T>& other)
	{
		Matrix<T> sum(mCols, mRows, 0);
		size_t i, j;
		for (i = 0; i < mRows; i++)
		{
			for (j = 0; j < mCols; j++)
				sum(i, j) = this->mData[i][j] + other(i, j);
		}
		return sum;
	}

	Matrix<T> operator-(const Matrix<T>& other)
	{
		Matrix<T> diff(mCols, mRows, 0);
		size_t i, j;
		for (i = 0; i < mRows; i++)
		{
			for (j = 0; j < mCols; j++)
				diff(i, j) = this->mData[i][j] - other(i, j);
		}
		return diff;
	}

	Matrix<T> operator*(const Matrix<T>& other)
	{
		Matrix prod(mRows, other.Cols(), 0);
		assert(mCols == other.Rows());

		size_t i, j, k;
		T temp = 0;
		for (i = 0; i < mRows; i++)
		{
			for (j = 0; j < other.Cols(); j++)
			{
				temp = 0;
				for (k = 0; k < mCols; k++)
				{
					temp += mData[i][k] * other(k, j);
				}
				prod(i, j) = temp;
			}
		}
		return prod;
	}

	Matrix<T> operator*(T scalar)
	{
		Matrix result(mRows, mCols, 0);
		size_t i, j;
		for (i = 0; i < mRows; i++)
		{
			for (j = 0; j < mCols; j++)
			{
				result(i, j) = this->mData[i][j] * scalar;
			}
		}
		return result;
	}

	Matrix<T> operator/(T scalar)
	{
		Matrix result(mRows, mCols, 0);
		size_t i, j;
		for (i = 0; i < mRows; i++)
		{
			for (j = 0; j < mCols; j++)
			{
				result(i, j) = this->mData[i][j] / scalar;
			}
		}
		return result;
	}
	
	Matrix<T> transpose()
	{
		Matrix trans(mCols, mRows, 0);
		for (size_t i = 0; i < mCols; i++)
		{
			for (size_t j = 0; j < mRows; j++)
				trans(i, j) = this->mData[j][i];
		}
		return trans;
	}


	const T& operator()(const size_t& row, const size_t& col) const { return this->mData[row][col]; }

	T& operator()(const size_t& row, const size_t& col) { return this->mData[row][col]; }

	void print() const
	{
		std::cout << "Matrix: " << std::endl;
		for (size_t i = 0; i < mRows; i++)
		{
			std::cout << "[";
			for (size_t j = 0; j < mCols; j++)
			{
				std::cout << mData[i][j] << ", ";
			}
			std::cout << "]," << std::endl;
		}
	}

	size_t Rows() const { return this->mRows; }

	size_t Cols() const { return this->mCols; }


private:
	size_t mRows, mCols;
	std::vector<std::vector<T>> mData;

};
