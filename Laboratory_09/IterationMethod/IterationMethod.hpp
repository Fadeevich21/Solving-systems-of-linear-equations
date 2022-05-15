#pragma once

#include "..\AbstractMethodSolvingSystemLinearEquations\AbstractMethodSolvingSystemLinearEquations.hpp"

namespace cm
{

	class IterationMethod : public AbstractMethodSolvingSystemLinearEquations
	{
	public:
		std::vector<BaseType> solve(const SystemEquations& systemEquations, const BaseType epsilon) const;
	};

}