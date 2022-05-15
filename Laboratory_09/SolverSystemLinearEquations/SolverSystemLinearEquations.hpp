#pragma once

#include "..\SystemEquations\SystemEquations.hpp"
#include "..\AbstractMethodSolvingSystemLinearEquations\AbstractMethodSolvingSystemLinearEquations.hpp"
#include "..\utility\utility.hpp"
#include <vector>

namespace cm
{

	class SolverSystemLinearEquations
	{
	private:
		const SystemEquations* systemEquations_;
		const AbstractMethodSolvingSystemLinearEquations* method_;

	public:
		SolverSystemLinearEquations(const SystemEquations* const systemEquations,
			const AbstractMethodSolvingSystemLinearEquations* const method);
		~SolverSystemLinearEquations();

		void setSystemEquations(const SystemEquations* const systemEquations);
		void setMethod(const AbstractMethodSolvingSystemLinearEquations* const method);

		std::vector<BaseType> solve(const BaseType epsilon) const;
	};

}