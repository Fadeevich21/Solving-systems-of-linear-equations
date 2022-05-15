#include "pch.h"
#include "Matrix/Matrix.hpp"
#include <vector>
#include "norms/norms.hpp"
#include "SolverSystemLinearEquations/SolverSystemLinearEquations.hpp"
#include "IterationMethod/IterationMethod.hpp"
#include "utility/utility.hpp"
#include <cmath>

using namespace cm;

#define isEqual(el1, el2, epsilon) (fabsl(el1 - el2) <= epsilon)

TEST(CheckNorms_Variant10, NormsL1_Matrix)
{
	// Arrange
	Matrix<BaseType> matrCoefficients =
	{
		{0, -0.0535, -0.5267},
		{0.0243, 0, -0.4863},
		{-0.3168, -0.6025, 0}
	};
	Norms* norms = new NormsL1;
	const BaseType epsilon = 0.001;

	const BaseType checkResNormsL1 = 1.013;

	// Act
	const BaseType resNormsL1 = norms->getNorm(matrCoefficients);

	// Assert
	ASSERT_TRUE(isEqual(resNormsL1, checkResNormsL1, epsilon));
}

TEST(CheckNorms_Variant10, NormsLInfinity_Matrix)
{
	// Arrange
	Matrix<BaseType> matrCoefficients =
	{
		{0, -0.0535, -0.5267},
		{0.0243, 0, -0.4863},
		{-0.3168, -0.6025, 0}
	};
	Norms* norms = new NormsLInfinity;
	const BaseType epsilon = 0.001;

	const BaseType checkResNormsL1 = 0.9193;

	// Act
	const BaseType resNormsL1 = norms->getNorm(matrCoefficients);

	// Assert
	ASSERT_TRUE(isEqual(resNormsL1, checkResNormsL1, epsilon));
}

TEST(CheckNorms_Variant10, NormsL1_Vector)
{
	// Arrange
	std::vector<BaseType> vec = {3, -12, 2, 4, 5};
	Norms* norms = new NormsL1;
	const BaseType epsilon = 0.001;

	const BaseType checkResNormsL1 = 26;

	// Act
	const BaseType resNormsL1 = norms->getNorm(vec);

	// Assert
	ASSERT_TRUE(isEqual(resNormsL1, checkResNormsL1, epsilon));
}

TEST(CheckNorms_Variant10, NormsLInfinity_Vector)
{
	// Arrange
	std::vector<BaseType> vec = {3, -12, 2, 4, 5};
	Norms* norms = new NormsLInfinity;
	const BaseType epsilon = 0.001;

	const BaseType checkResNormsL1 = 12;

	// Act
	const BaseType resNormsL1 = norms->getNorm(vec);

	// Assert
	ASSERT_TRUE(isEqual(resNormsL1, checkResNormsL1, epsilon));
}

TEST(SolverSystemLinearEquations, Variant10)
{
	// Arrange
	SystemEquations::Equations equations =
	{
		{0, -0.0535, -0.5267, 0.4568},
		{0.0243, 0, -0.4863, 0.8267},
		{-0.3168, -0.6025, 0, 0.8545}
	};
	const SystemEquations* const systemEquations = new SystemEquations(equations);
	const AbstractMethodSolvingSystemLinearEquations* const method = new IterationMethod;
	const BaseType epsilon = 0.1;
	const SolverSystemLinearEquations solver(systemEquations, method);

	const std::vector<BaseType> checkSolve = {0.211, 0.636, 0.41};
	
	const uint8_t indexBeginElVec = uint8_t(0);
	const uint8_t indexEndElVec = uint8_t(checkSolve.size());

	// Act
	const std::vector<BaseType> solve = solver.solve(epsilon);

	// Assert
	for (uint8_t indexElVec = indexBeginElVec; indexElVec != indexEndElVec; indexElVec++)
	{
		ASSERT_TRUE(isEqual(solve[indexElVec], checkSolve[indexElVec], epsilon));
	}
}