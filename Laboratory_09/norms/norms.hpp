#pragma once

#include "..\Matrix\Matrix.hpp"
#include <vector>

namespace cm
{
	using BaseType = long double;


	class Norms
	{
	public:
		Norms() = default;

		virtual BaseType getNorm(const Matrix<BaseType>& matr) const = 0;
		virtual BaseType getNorm(const std::vector<BaseType>& vec) const = 0;
	};

	class NormsL1 : public Norms
	{
	public:
		NormsL1() = default;

		BaseType getNorm(const Matrix<BaseType>& matr) const;
		BaseType getNorm(const std::vector<BaseType>& vec) const;
	};

	class NormsLInfinity : public Norms
	{
	public:
		NormsLInfinity() = default;

		BaseType getNorm(const Matrix<BaseType>& matr) const;
		BaseType getNorm(const std::vector<BaseType>& vec) const;
	};

}
