#include "norms.hpp"
#include <cmath>

namespace cm
{

	BaseType NormsL1::getNorm(const Matrix<BaseType>& matr) const
	{
		const uint8_t indexBeginRow = uint8_t(0);
		const uint8_t indexEndRow = uint8_t(matr.sizeRow());

		const uint8_t indexBeginColumn = uint8_t(0);
		const uint8_t indexEndColumn = uint8_t(matr.sizeColumn());

		BaseType maxSumAbsElRow = (-1.L);
		for (uint8_t indexColumn = indexBeginColumn; indexColumn != indexEndColumn; indexColumn++)
		{
			BaseType sumAbsElRow = BaseType();
			for (uint8_t indexRow = indexBeginRow; indexRow != indexEndRow; indexRow++)
			{
				sumAbsElRow += fabsl(matr[indexRow][indexColumn]);
			}

			maxSumAbsElRow = max(sumAbsElRow, maxSumAbsElRow);
		}

		return maxSumAbsElRow;
	}

	BaseType NormsL1::getNorm(const std::vector<BaseType>& vec) const
	{
		BaseType absSumEl = BaseType();
		for (const BaseType el : vec)
		{
			absSumEl += fabsl(el);
		}

		return absSumEl;
	}


	BaseType NormsLInfinity::getNorm(const Matrix<BaseType>& matr) const
	{
		const uint8_t indexBeginRow = uint8_t(0);
		const uint8_t indexEndRow = uint8_t(matr.sizeRow());

		const uint8_t indexBeginColumn = uint8_t(0);
		const uint8_t indexEndColumn = uint8_t(matr.sizeColumn());

		BaseType maxSumAbsElColumn = (-1.L);
		for (uint8_t indexRow = indexBeginRow; indexRow != indexEndRow; indexRow++)
		{
			BaseType sumAbsElColumn = BaseType();
			for (uint8_t indexColumn = indexBeginColumn; indexColumn != indexEndColumn; indexColumn++)
			{
				sumAbsElColumn += fabsl(matr[indexRow][indexColumn]);
			}

			maxSumAbsElColumn = max(sumAbsElColumn, maxSumAbsElColumn);
		}

		return maxSumAbsElColumn;
	}

	BaseType NormsLInfinity::getNorm(const std::vector<BaseType>& vec) const
	{
		BaseType maxAbsEl = fabsl(vec.front());
		for (const BaseType el : vec)
		{
			const BaseType absEl = fabsl(el);
			maxAbsEl = max(absEl, maxAbsEl);
		}

		return maxAbsEl;
	}

}
