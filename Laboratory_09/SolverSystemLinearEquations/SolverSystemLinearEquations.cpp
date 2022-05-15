#include "SolverSystemLinearEquations.hpp"

namespace cm
{

	SolverSystemLinearEquations::SolverSystemLinearEquations(const SystemEquations* const systemEquations, const AbstractMethodSolvingSystemLinearEquations* const method)
		:systemEquations_(systemEquations), method_(method)
	{
	}

	SolverSystemLinearEquations::~SolverSystemLinearEquations()
	{
		delete this->systemEquations_;
		delete this->method_;
	}

	void SolverSystemLinearEquations::setSystemEquations(const SystemEquations* const systemEquations)
	{
		delete this->systemEquations_;
		this->systemEquations_ = systemEquations;
	}

	void SolverSystemLinearEquations::setMethod(const AbstractMethodSolvingSystemLinearEquations* const method)
	{
		delete this->method_;
		this->method_ = method;
	}

	std::vector<BaseType> SolverSystemLinearEquations::solve(const BaseType epsilon) const
	{
		const SystemEquations* const systemEquations = this->systemEquations_;
		const AbstractMethodSolvingSystemLinearEquations* const method = this->method_;

		return method->solve(*systemEquations, epsilon);
	}

}