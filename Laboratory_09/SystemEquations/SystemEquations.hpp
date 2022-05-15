#pragma once

#include "..\Matrix\Matrix.hpp"
#include "..\utility\utility.hpp"

namespace cm
{

	class SystemEquations
	{
	public:
		using Equations = Matrix<BaseType>;

	private:
		Equations data_;

	public:
		SystemEquations(const Equations &equations);
		
		Equations getEquations() const;
		uint8_t getCountEquations() const;
		uint8_t getCountVariables() const;

		void setEquations(const Equations& equations);
	};

}