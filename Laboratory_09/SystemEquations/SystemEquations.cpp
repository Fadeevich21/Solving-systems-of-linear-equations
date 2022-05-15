#include "SystemEquations.hpp"

namespace cm
{

	SystemEquations::SystemEquations(const Equations& equations)
		:data_(equations)
	{
	}

	SystemEquations::Equations SystemEquations::getEquations() const
	{
		return this->data_;
	}

	uint8_t SystemEquations::getCountEquations() const
	{
		return this->data_.sizeRow();
	}

	uint8_t SystemEquations::getCountVariables() const
	{
		return this->data_.sizeColumn();
	}

	void SystemEquations::setEquations(const Equations& equations)
	{
		this->data_ = equations;
	}

}