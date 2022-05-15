#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cassert>

namespace cm
{

	using namespace std;

	template <class T>
	class Matrix
	{
	public:
		using Container = vector<vector<T>>;
		using iterator = typename Container::iterator;
		using const_iterator = typename Container::const_iterator;

	private:
		// Инициализаторы матрицы
		void init(const Container& matr, const size_t& sizeRow, const size_t& sizeColumn);
		void init(const T* const* const& matr, const size_t& sizeRow, const size_t& sizeColumn);
		void init(const size_t& sizeRow, const size_t& sizeColumn, const T& value);

		// Данные о матрице
		Container data;
		size_t _sizeRow;
		size_t _sizeColumn;

		// Константные значения
		const static size_t defaultSizeRow = 0;
		const static size_t defaultSizeColumn = 0;

	public:
		// Конструкторы
		explicit Matrix(const size_t& sizeRow = defaultSizeRow, const size_t& sizeColumn = defaultSizeColumn);
		Matrix(const T* const* const& matr, const size_t& sizeRow, const size_t& sizeColumn);
		Matrix(const size_t& sizeRow, const size_t& sizeColumn, const T& value);
		Matrix(const Container& matr);
		Matrix(const Matrix<T>& matr);
		Matrix(const initializer_list<initializer_list<T>>& matr);

		// Деструктор
		~Matrix();

		// Возвращает число строк
		size_t sizeRow() const;

		// Возвращает число столбцов
		size_t sizeColumn() const;

		// Обменивает строки indexRow1 и indexRow2
		void swapRow(const size_t& indexRow1, const size_t& indexRow2);

		// Обменивает столбцы indexColumn1 и indexColumn2
		void swapColumn(const size_t& indexColumn1, const size_t& indexColumn2);

		// Добавление строки на позицию indexRow со значениями vecValueRow
		void insertRow(const size_t& indexRow, const vector<T>& vecValueRow = {});

		// Добавление столбца на позицию Indexcolumn со значениями vecValueColumn
		void insertColumn(const size_t& indexColumn, const vector<T>& vecValueColumn = {});

		// Добавление строки на позицию indexRow со значениями vecValueRow
		void insertRow(const size_t& indexRow, const size_t cntElColumn);

		// Добавление столбца на позицию Indexcolumn со значениями vecValueColumn
		void insertColumn(const size_t& indexColumn, const size_t cntElRow);


		// Удаление строки на позиции indexRow
		void eraseRow(const size_t& indexRow);

		// Удаление столбца на позиции indexRow
		void eraseColumn(const size_t& indexColumn);

		// Возвращает "истина", если матрица пуста, иначе - "ложь"
		bool empty() const;

		// Очистка матрицы
		void clear();

		bool operator==(const Matrix<T>& matr) const;
		bool operator!=(const Matrix<T>& matr) const;
		bool operator>(const Matrix<T>& matr) const;
		bool operator>=(const Matrix<T>& matr) const;
		bool operator<(const Matrix<T>& matr) const;
		bool operator<=(const Matrix<T>& matr) const;

		vector<T>& operator[] (const size_t& index);
		const vector<T>& operator[] (const size_t& index) const;

		Matrix<T>& operator=(const Matrix<T>& matr);
		Matrix<T>& operator=(const Container& matr);

		Matrix<T> operator+(const Matrix<T>& matr) const;
		Matrix<T> operator-(const Matrix<T>& matr) const;
		Matrix<T> operator*(const Matrix<T>& matr) const;

		Matrix<T> operator+=(const Matrix<T>& matr);
		Matrix<T> operator-=(const Matrix<T>& matr);
		Matrix<T> operator*=(const Matrix<T>& matr);
		Matrix<T> operator*=(const long long& val);

		friend Matrix<T> operator*(const long long& val, const Matrix<T>& matr2);
		friend Matrix<T> operator*(const Matrix<T>& matr1, const long long& val);
		friend Matrix<T> operator*(const Matrix<T>& matr, const vector<T>& vec);
		friend Matrix<T> operator*(const vector<T>& vec, const Matrix<T>& matr);


		iterator begin()
		{
			return this->data.begin();
		}

		iterator end()
		{
			return this->data.end();
		}

		const_iterator cbegin() const
		{
			return this->data.cbegin();
		}

		const_iterator cend() const
		{
			return this->data.cend();
		}
	};

}

namespace cm
{
	template <class T>
	Matrix<T>::Matrix(const size_t& sizeRow, const size_t& sizeColumn) : _sizeRow(sizeRow), _sizeColumn(sizeColumn)
	{
		init(vector<vector<T>>(sizeRow, vector<T>(sizeColumn)), sizeRow, sizeColumn);
	}

	template <class T>
	Matrix<T>::Matrix(const T* const* const& matr, const size_t& sizeRow, const size_t& sizeColumn) : _sizeRow(sizeRow), _sizeColumn(sizeColumn)
	{
		init(matr, sizeRow, sizeColumn);
	}

	template <class T>
	Matrix<T>::Matrix(const size_t& sizeRow, const size_t& sizeColumn, const T& value) : _sizeRow(sizeRow), _sizeColumn(sizeColumn)
	{
		init(sizeRow, sizeColumn, value);
	}

	template <class T>
	Matrix<T>::Matrix(const Container& matr)
	{
		init(matr, matr.size(), matr.begin()->size());
	}

	template <class T>
	Matrix<T>::Matrix(const Matrix<T>& matr)
	{
		init(matr.data, matr._sizeRow, matr._sizeColumn);
	}

	template<class T>
	inline Matrix<T>::Matrix(const initializer_list<initializer_list<T>>& list)
	{
		Container matr;
		const uint32_t sizeRow = uint32_t(list.size());
		const uint32_t sizeColumn = uint32_t(list.begin()->size());
		for (auto iter = list.begin(); iter != list.end(); iter = next(iter))
		{
			matr.push_back(*iter);
		}

		init(matr, sizeRow, sizeColumn);
	}

	template <class T>
	Matrix<T>::~Matrix()
	{
		this->clear();
	}

	template <class T>
	void Matrix<T>::init(const Container& matr, const size_t& sizeRow, const size_t& sizeColumn)
	{
		this->_sizeRow = sizeRow;
		this->_sizeColumn = sizeColumn;

		this->data.resize(_sizeRow, vector<T>(_sizeColumn));
		this->data = matr;
	}

	template <class T>
	void Matrix<T>::init(const T* const* const& matr, const size_t& sizeRow, const size_t& sizeColumn)
	{
		this->_sizeRow = sizeRow;
		this->_sizeColumn = sizeColumn;

		this->data.resize(_sizeRow, vector<T>(_sizeColumn));
		this->data = vector<vector<T>>(matr);
	}

	template <class T>
	void Matrix<T>::init(const size_t& sizeRow, const size_t& sizeColumn, const T& value)
	{
		this->_sizeRow = sizeRow;
		this->_sizeColumn = sizeColumn;

		this->data.resize(_sizeRow, vector<T>(_sizeColumn, value));
	}

	template <class T>
	size_t Matrix<T>::sizeRow() const
	{
		return this->_sizeRow;
	}

	template <class T>
	size_t Matrix<T>::sizeColumn() const
	{
		return this->_sizeColumn;
	}

	template <class T>
	void Matrix<T>::swapRow(const size_t& indexRow1, const size_t& indexRow2)
	{
		for (size_t i = 0; i < this->_sizeColumn; i++)
		{
			swap(this->data[indexRow1][i], this->data[indexRow2][i]);
		}
	}

	template <class T>
	void Matrix<T>::swapColumn(const size_t& indexColumn1, const size_t& indexColumn2)
	{
		for (size_t i = 0; i < _sizeRow; i++)
		{
			swap(data[i][this->indexColumn1], data[i][this->indexColumn2]);
		}
	}

	template <class T>
	bool Matrix<T>::empty() const
	{
		return this->_sizeRow == 0 || this->_sizeColumn == 0;
	}

	template <class T>
	void Matrix<T>::insertRow(const size_t& indexRow, const vector<T>& vecValueRow)
	{
		if (this->empty())
		{
			this->_sizeColumn = vecValueRow.size();
		}
		else
		{
			assert(this->_sizeColumn >= vecValueRow.size());
		}

		assert(indexRow <= this->_sizeRow);
		this->data.insert(this->data.begin() + indexRow, vecValueRow);
		this->_sizeRow++;
	}

	template <class T>
	void Matrix<T>::insertColumn(const size_t& indexColumn, const vector<T>& vecValueColumn)
	{
		if (this->empty())
		{
			for (size_t i = 0; i < vecValueColumn.size(); i++)
			{
				this->insertRow(i, {});
			}
		}
		else
		{
			assert(this->_sizeRow >= vecValueColumn.size());
		}
		assert(indexColumn <= this->_sizeColumn);
		for (size_t i = 0; i < this->_sizeRow; i++)
		{
			this->data[i].insert(this->data[i].begin() + indexColumn, vecValueColumn[i]);
		}

		this->_sizeColumn++;
	}

	template<class T>
	void Matrix<T>::insertRow(const size_t& indexRow, const size_t cntElRow)
	{
		insertRow(indexRow, vector<T>(cntElRow));
	}

	template<class T>
	void Matrix<T>::insertColumn(const size_t& indexColumn, const size_t cntElColumn)
	{
		insertColumn(indexColumn, vector<T>(cntElColumn));
	}

	template <class T>
	void Matrix<T>::eraseRow(const size_t& indexRow)
	{
		this->data.erase(this->data.begin() + indexRow);
		this->_sizeRow--;
	}

	template <class T>
	void Matrix<T>::eraseColumn(const size_t& indexColumn)
	{
		for (auto& row : *this)
		{
			row.erase(row.begin() + indexColumn);
		}

		this->_sizeColumn--;
	}

	template <class T>
	void Matrix<T>::clear()
	{
		for (auto& row : *this)
		{
			row.clear();
		}

		this->data.clear();

		this->_sizeColumn = 0;
		this->_sizeRow = 0;
	}

	template <class T>
	void ReadMatrix(Matrix<T>& matr)
	{
		for (auto& row : matr)
		{
			for (auto& el : row)
			{
				cin >> el;
			}
		}
	}

	template <class T>
	void WriteMatrix(Matrix<T> matr)
	{
		for (auto& row : matr)
		{
			for (auto& el : row)
			{
				cout << fixed << setprecision(3) << left << setw(10) << el << ' ';
			}

			cout << "\n";
		}
	}

	template <class T>
	bool Matrix<T>::operator==(const Matrix<T>& matr) const
	{
		return this->data == matr.data;
	}

	template <class T>
	bool Matrix<T>::operator!=(const Matrix<T>& matr) const
	{
		return this->data != matr.data;
	}

	template <class T>
	bool Matrix<T>::operator>(const Matrix<T>& matr) const
	{
		return this->data > matr.data;
	}

	template <class T>
	bool Matrix<T>::operator>=(const Matrix<T>& matr) const
	{
		return this->data >= matr.data;
	}

	template <class T>
	bool Matrix<T>::operator<(const Matrix<T>& matr) const
	{
		return this->data < matr.data;
	}

	template <class T>
	bool Matrix<T>::operator<=(const Matrix<T>& matr) const
	{
		return this->data <= matr.data;
	}

	template <class T>
	Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matr)
	{
		this->data = matr.data;
		this->_sizeRow = matr._sizeRow;
		this->_sizeColumn = matr._sizeColumn;

		return *this;
	}

	template<class T>
	inline Matrix<T>& Matrix<T>::operator=(const Container& matr)
	{
		return this->operator=(Matrix<T>(matr));
	}

	template <class T>
	Matrix<T> Matrix<T>::operator+(const Matrix<T>& matr) const
	{
		Matrix<T> matrResult = matr;
		try
		{
			if (this->sizeColumn() != matrResult.sizeColumn() && this->sizeRow() != matrResult.sizeRow())
			{
				throw "Размерности матриц не совпадают";
			}

			for (size_t i = 0; i < matrResult.sizeRow(); i++)
			{
				for (size_t j = 0; j < matrResult.sizeColumn(); j++)
				{
					matrResult[i][j] += this->data[i][j];
				}
			}
		}
		catch (const char* msg)
		{
			cout << msg << endl;
		}

		return matrResult;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator-(const Matrix<T>& matr) const
	{
		Matrix<T> matrResult = matr;
		try
		{
			if (this->sizeColumn() != matrResult.sizeColumn() && this->sizeRow() != matrResult.sizeRow())
			{
				throw "Размерности матриц не совпадают!";
			}
			for (size_t i = 0; i < matrResult.sizeRow(); i++)
			{
				for (size_t j = 0; j < matrResult.sizeColumn(); j++)
				{
					matrResult[i][j] = this->data[i][j] - matrResult[i][j];
				}
			}
		}
		catch (const char* msg)
		{
			cout << msg << endl;
		}

		return matrResult;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) const
	{
		Matrix<T> matrRes(this->sizeRow(), matr.sizeColumn());
		try
		{
			if (this->sizeColumn() != matr.sizeRow())
			{
				throw "Количество столбцов первой матрицы не совпадает с числом строк второй матрицы!";
			}
			for (size_t i = 0; i < matr.sizeRow(); i++)
			{
				for (size_t j = 0; j < matr.sizeColumn(); j++)
				{
					for (size_t k = 0; k < this->sizeColumn(); k++)
					{
						matrRes[i][j] += this->data[i][k] * matr[k][j];
					}
				}
			}
		}
		catch (const char* msg)
		{
			cout << msg << endl;
		}

		return matrRes;
	}

	template <class T>
	Matrix<T> operator*(const Matrix<T>& matr, const long long& val)
	{
		Matrix<T> matrRes(matr.sizeRow(), matr.sizeColumn(), 0);
		for (size_t i = 0; i < matr.sizeRow(); i++)
		{
			for (size_t j = 0; j < matr.sizeColumn(); j++)
			{
				matr[i][j] = val * matr[i][j];
			}
		}

		return matr;
	}

	template <class T>
	Matrix<T> operator*(const long long& val, const Matrix<T>& matr)
	{
		Matrix<T> matrRes(matr.sizeRow(), matr.sizeColumn(), 0);
		for (size_t i = 0; i < matr.sizeRow(); i++)
		{
			for (size_t j = 0; j < matr.sizeColumn(); j++)
			{
				matr[i][j] = val * matr[i][j];
			}
		}

		return matr;
	}

	template <class T>
	Matrix<T> operator*(const Matrix<T>& matr, const vector<T>& vec)
	{
		Matrix<T> matrResult(matr.sizeRow(), matr.sizeColumn(), 0);
		if (matrResult.sizeColumn() == vec.size())
		{
			for (size_t i = 0; i < matr.sizeRow(); i++)
			{
				for (size_t j = 0; j < matr.sizeColumn(); j++)
				{
					for (size_t k = 0; k < matr.sizeColumn(); k++)
					{
						matrResult[i][j] += matr[i][k] * vec[k];
					}
				}
			}
		}

		return matrResult;
	}

	template <class T>
	Matrix<T> operator*(const vector<T>& vec, const Matrix<T>& matr)
	{
		Matrix<T> matrResult(matr.sizeRow(), matr.sizeColumn(), 0);
		if (matr.sizeRow() == vec.size())
		{
			for (size_t i = 0; i < matr.sizeRow(); i++)
			{
				for (size_t j = 0; j < matr.sizeColumn(); j++)
				{
					for (size_t k = 0; k < matr.sizeColumn(); k++)
					{
						matrResult[i][j] += matr[k][j] * vec[k];
					}
				}
			}
		}

		return matrResult;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator+=(const Matrix<T>& matr)
	{
		return *this + matr;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator-=(const Matrix<T>& matr)
	{
		return *this - matr;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator*=(const Matrix<T>& matr)
	{
		return *this * matr;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator*=(const long long& val)
	{
		return this * val;
	}

	template <class T>
	vector<T>& Matrix<T>::operator[](const size_t& index)
	{
		return this->data[index];
	}

	template <class T>
	const vector<T>& Matrix<T>::operator[](const size_t& index) const
	{
		return this->data[index];
	}

}

namespace cm
{

	template <class T>
	Matrix<T> TransposeMatrix(Matrix<T> matr)
	{
		Matrix<T> matrRes(matr.sizeColumn(), matr.sizeRow(), 0);
		for (size_t i = 0; i < matr.sizeRow(); i++)
		{
			for (size_t j = 0; j < matr.sizeColumn(); j++)
			{
				matrRes[i][j] = matr[j][i];
			}
		}

		return matrRes;
	}

	template <class T>
	bool IsIdentityMatrix(Matrix<T> matr)
	{
		bool flag = true;
		for (size_t i = 0; flag && i < matr.sizeRow(); i++)
		{
			for (size_t j = 0; flag && j < matr.sizeColumn(); j++)
			{
				if (i == j && matr[i][j] != 1 || i != j && matr[i][j] != 0)
				{
					flag = false;
				}
			}
		}

		return flag;
	}

	template <class T>
	Matrix<T> GetIdentityMatrix(size_t sizeRow, size_t sizeColumn)
	{
		Matrix<T> matr(sizeRow, sizeColumn);
		for (size_t i = 0; i < sizeRow; i++)
		{
			matr[i][i] = 1;
		}

		return matr;
	}

	template <class T>
	vector<T> GetRowMatrix(Matrix<T> matr, size_t indexRow)
	{
		vector<T> rowMatrix(matr.sizeColumn());
		for (size_t i = 0; i < matr.sizeColumn(); i++)
		{
			rowMatrix[i] = matr[indexRow][i];
		}

		return rowMatrix;
	}

	template <class T>
	vector<T> GetColumnMatrix(Matrix<T> matr, size_t indexColumn)
	{
		vector<T> columnMatrix(matr.sizeRow());
		for (size_t i = 0; i < matr.sizeRow(); i++)
		{
			columnMatrix[i] = matr[i][indexColumn];
		}

		return columnMatrix;
	}

}