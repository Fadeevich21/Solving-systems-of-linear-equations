#pragma once

#include "..\SystemEquations\SystemEquations.hpp"
#include "..\utility\utility.hpp"
#include <vector>

namespace cm
{

	class AbstractMethodSolvingSystemLinearEquations
	{
	public:
		AbstractMethodSolvingSystemLinearEquations() = default;

		virtual std::vector<BaseType> solve(const SystemEquations& systemEquations, const BaseType epsilon) const = 0;
	};

}