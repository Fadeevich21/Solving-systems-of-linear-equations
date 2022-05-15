#include "IterationMethod.hpp"
#include "..\Matrix\Matrix.hpp"
#include <vector>
#include "..\norms\norms.hpp"

namespace cm
{

	uint8_t getIndexFreeTerm(const Matrix<BaseType>& matr)
	{
		return uint8_t(matr.sizeColumn() - 1);
	}

	void deleteFreeTermsInMatrix(Matrix<BaseType>& matr)
	{
		const uint8_t indexFreeTermMatrix = getIndexFreeTerm(matr);
		matr.eraseColumn(indexFreeTermMatrix);
	}

	Matrix<BaseType> getMatrixCoefficients(const SystemEquations& systemEquations)
	{
		Matrix<BaseType> matrCoefficients = systemEquations.getEquations();
		deleteFreeTermsInMatrix(matrCoefficients);

		return matrCoefficients;
	}

	std::vector<BaseType> getVecElColumn(const Matrix<BaseType>& matr,
		const uint8_t indexColumn)
	{
		const uint8_t countElColumn = uint8_t(matr.sizeRow());
		std::vector<BaseType> vecElColumn(countElColumn);

		const uint8_t indexBeginRow = uint8_t(0);
		const uint8_t indexEndRow = uint8_t(matr.sizeRow());

		uint8_t indexVec = uint8_t(0);
		for (uint8_t indexRow = indexBeginRow; indexRow != indexEndRow; indexRow++)
		{
			vecElColumn[indexVec++] = matr[indexRow][indexColumn];
		}

		return vecElColumn;
	}

	std::vector<BaseType> getVectorFreeTerms(const SystemEquations& systemEquations)
	{
		const SystemEquations::Equations equations = systemEquations.getEquations();
		const uint8_t indexFreeTermMatrix = getIndexFreeTerm(equations);
		const std::vector<BaseType> vecFreeTerms = getVecElColumn(equations,
			indexFreeTermMatrix);

		return vecFreeTerms;
	}

	std::vector<BaseType> getInitialApproximation(const SystemEquations& systemEquations)
	{
		return getVectorFreeTerms(systemEquations);
	}


	Norms* getNorms(const Matrix<BaseType>& matrCoefficients)
	{
		const BaseType resNormL1 = (new NormsL1)->getNorm(matrCoefficients);
		const BaseType resNormLInfinity = (new NormsLInfinity)->getNorm(matrCoefficients);
		if (resNormL1 > resNormLInfinity)
		{
			return new NormsLInfinity;
		}
		else
		{
			return new NormsL1;
		}
	}

	std::vector<BaseType> operator-(const std::vector<BaseType>& vec1,
		const std::vector<BaseType>& vec2)
	{
		if (vec1.size() != vec2.size())
		{
			return std::vector<BaseType>();
		}

		std::vector<BaseType> vecResult = vec1;

		const uint8_t indexBeginElVec = uint8_t(0);
		const uint8_t indexEndElVec = uint8_t(vec1.size());
		for (uint8_t indexElVec = indexBeginElVec; indexElVec != indexEndElVec;
			indexElVec++)
		{
			vecResult[indexElVec] -= vec2[indexElVec];
		}

		return vecResult;
	}

	std::vector<BaseType> operator+(const std::vector<BaseType>& vec1,
		const std::vector<BaseType>& vec2)
	{
		if (vec1.size() != vec2.size())
		{
			return std::vector<BaseType>();
		}

		std::vector<BaseType> vecResult = vec1;

		const uint8_t indexBeginElVec = uint8_t(0);
		const uint8_t indexEndElVec = uint8_t(vec1.size());
		for (uint8_t indexElVec = indexBeginElVec; indexElVec != indexEndElVec;
			indexElVec++)
		{
			vecResult[indexElVec] += vec2[indexElVec];
		}

		return vecResult;
	}

	bool checkStopCondition(const Norms* const norms,
		std::vector<BaseType> vecApproximate,
		std::vector<BaseType> vecApproximateSolution,
		const BaseType epsilon1)
	{
		return (norms->getNorm(vecApproximateSolution - vecApproximate) <= epsilon1);
	}

	std::vector<BaseType> getNewVecApproximate(const SystemEquations& systemEquations, std::vector<BaseType>& vecApproximatePrev)
	{
		const Matrix<BaseType> matrCoefficients = getMatrixCoefficients(systemEquations);
		const std::vector<BaseType> vecFreeTerms = getVectorFreeTerms(systemEquations);

		std::vector<BaseType> vecApproximate = getVectorFreeTerms(systemEquations);

		const uint8_t indexBeginRow = uint8_t(0);
		const uint8_t indexEndRow = uint8_t(matrCoefficients.sizeRow());

		const uint8_t indexBeginColumn = uint8_t(0);
		const uint8_t indexEndColumn = uint8_t(matrCoefficients.sizeColumn());
		for (uint8_t indexRow = indexBeginRow; indexRow != indexEndRow; indexRow++)
		{
			const uint8_t indexVecApproximate = indexRow;
			for (uint8_t indexColumn = indexBeginColumn; indexColumn != indexEndColumn; indexColumn++)
			{
				const uint8_t indexVecApproximatePrev = indexColumn;
				vecApproximate[indexVecApproximate] += matrCoefficients[indexRow][indexColumn] * vecApproximatePrev[indexVecApproximatePrev];
			}
		}

		return vecApproximate;
	}

	BaseType getEpsilon1(const Norms* const norms, const Matrix<BaseType>& matrCoefficients, const BaseType epsilon)
	{
		const BaseType normMatrCoefficients = norms->getNorm(matrCoefficients);

		return (1 - normMatrCoefficients) * epsilon / normMatrCoefficients;
	}

	std::vector<BaseType> IterationMethod::solve(const SystemEquations& systemEquations, const BaseType epsilon) const
	{
		const Matrix<BaseType> matrCoefficients = getMatrixCoefficients(systemEquations);
		const Norms* const norms = getNorms(matrCoefficients);

		const BaseType epsilon1 = getEpsilon1(norms, matrCoefficients, epsilon);

		std::vector<BaseType> vecApproximatePrev;
		std::vector<BaseType> vecApproximate = getInitialApproximation(systemEquations);
		do
		{
			vecApproximatePrev = vecApproximate;
			vecApproximate = getNewVecApproximate(systemEquations, vecApproximatePrev);
		}
		while (!checkStopCondition(norms, vecApproximate, vecApproximatePrev, epsilon1));

		return vecApproximate;
	}

}