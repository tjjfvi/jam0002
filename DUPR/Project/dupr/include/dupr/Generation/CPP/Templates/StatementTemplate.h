#ifndef DUPR_GENERATION_CPP_TEMPLATES_STATEMENTTEMPLATE_h
#define DUPR_GENERATION_CPP_TEMPLATES_STATEMENTTEMPLATE_h

#include <variant>
#include <vector>
#include <string>

namespace dupr::generation::cpp::templates
{

	/*!	\class StatementTemplate
	 *
	 *	\brief Generates code for "StatementTemplate"
	 *
	 *	\details This is generated by DST.
	 *	For more information visit: https://github.com/Deruago/DeamerStringTemplate
	 */
	class StatementTemplate
	{
	public:
		enum class Type
{
Unknown,
Scope,

// User defined types
conditional_else_,
conditional_else_if_,
conditional_if_,
expression_,
external_statement_,
file_,
left_angle_bracket_,
left_bracket_,
left_curly_bracket_,
return_statement_,
right_angle_bracket_,
right_bracket_,
right_curly_bracket_,
statement_,
var_name_,
var_type_,
variable_assignment_,
variable_declaration_,
variable_initialization_,


};


		enum class ScopeType
{
Unknown,

// Default
Default_,
Upper_,
Lower_,

Snake_,
Slash_,
BackSlash_,
Colon_,
DoubleColon_,

Variable_Field_,
Variable_Field_Separator_,
Function_Field_,
Function_Field_Separator_,


};


		static constexpr const char* ConvertEnumToName(::dupr::generation::cpp::templates::StatementTemplate::Type enumerationValue)
{
	switch(enumerationValue)
	{
	case ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_:
{
	return "conditional_else";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_if_:
{
	return "conditional_else_if";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_if_:
{
	return "conditional_if";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::expression_:
{
	return "expression";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::external_statement_:
{
	return "external_statement";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::file_:
{
	return "file";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::left_angle_bracket_:
{
	return "left_angle_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::left_bracket_:
{
	return "left_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::left_curly_bracket_:
{
	return "left_curly_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::return_statement_:
{
	return "return_statement";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::right_angle_bracket_:
{
	return "right_angle_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::right_bracket_:
{
	return "right_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::right_curly_bracket_:
{
	return "right_curly_bracket";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::statement_:
{
	return "statement";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::var_name_:
{
	return "var_name";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::var_type_:
{
	return "var_type";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_assignment_:
{
	return "variable_assignment";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_declaration_:
{
	return "variable_declaration";
}

case ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_initialization_:
{
	return "variable_initialization";
}


	}

	return "";
}


		
	public:
		struct VariableBase
		{
			// The value is either a string
			// or a vector of variables.
			std::variant<std::string, std::vector<VariableBase*>> value;
			bool isString = true;

			::dupr::generation::cpp::templates::StatementTemplate::Type type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Unknown;

			VariableBase() : VariableBase(std::vector<VariableBase*>())
			{
			}

			virtual ~VariableBase() = default;

			VariableBase(const char* text)
			{
				isString = true;
				value = text;
			}

			VariableBase(const std::string& text)
			{
				isString = true;
				value = text;
			}

			VariableBase(std::vector<VariableBase*> variables)
			{
				isString = false;
				value = variables;
			}

			VariableBase* This()
			{
				return this;
			}

			virtual std::string GetValue()
			{
				if (isString)
				{
					return std::get<std::string>(value);
				}
				else
				{
					std::string output;
					auto& variables = std::get<std::vector<VariableBase*>>(value);
					for (auto* variable : variables)
					{
						output += variable->GetValue();
					}
					return output;
				}
			}

			std::string GetName()
			{
				return ConvertEnumToName(type);
			}

			VariableBase& operator=(const std::string& variable)
			{
				return Set(variable);
			}

			VariableBase& operator=(VariableBase* variable)
			{
				return Set(variable);
			}

			VariableBase& operator+=(VariableBase* variable)
			{
				return Add(variable);
			}

			VariableBase& operator+=(const std::string& variable)
			{
				return Add(variable);
			}

			VariableBase& Set(const std::string& variable)
			{
				value = variable;
				isString = true;

				return *this;
			}

			VariableBase& Set(VariableBase* variable)
			{
				if (variable == this)
				{
					return *this;
				}

				value = variable->value;
				isString = variable->isString;

				return *this;
			}

			VariableBase& Add(const std::string& variable)
			{
				if (isString)
				{
					auto& text = std::get<std::string>(value);
					text += variable;
					value = text;
				}
				else
				{
					auto& vector = std::get<std::vector<VariableBase*>>(value);
					vector.push_back(new VariableBase(variable));
					value = vector;
				}

				return *this;
			}

			VariableBase& Add(VariableBase* variable)
			{
				if (variable == this)
				{
					return *this;
				}

				if (isString)
				{
					// convert current -> variablebase
					// then create a vector.
					auto& currentValue = std::get<std::string>(value);
					auto* currentValueAsVariableBase = new VariableBase(currentValue);
					value = std::vector<VariableBase*>({ currentValueAsVariableBase, variable });

					isString = false;
				}
				else
				{
					auto& vector = std::get<std::vector<VariableBase*>>(value);
					vector.push_back(variable);
					value = vector;
				}

				return *this;
			}

			void Clear()
			{
				if (isString)
				{
					value = "";
				}
				else
				{
					value = std::vector<VariableBase*>();
				}
			}

			void* operator new(size_t size)
			{
				void* newVariable = ::operator new(size);
				variables_to_delete.emplace_back(static_cast<VariableBase*>(newVariable));

				return newVariable;
			}
		};

		static VariableBase* GenerateVariable(VariableBase* variable)
		{
			return variable;
		}

		
		static VariableBase* GenerateVariable(const std::string& variable)
		{
			return new VariableBase(variable);
		}

		struct VariableScope : public VariableBase
		{
			::dupr::generation::cpp::templates::StatementTemplate::ScopeType scope_type = ::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Unknown;
			bool isReserved = false;

			VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType scope_type_, bool isReserved_ = false) : VariableBase(), scope_type(scope_type_), isReserved(isReserved_)
			{
				type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;
			}

			VariableScope(const char* text, ::dupr::generation::cpp::templates::StatementTemplate::ScopeType scope_type_, bool isReserved_ = false) : VariableBase(text), scope_type(scope_type_), isReserved(isReserved_)
			{
				type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;
			}

			VariableScope(std::vector<VariableBase*> variable, ::dupr::generation::cpp::templates::StatementTemplate::ScopeType scope_type_, bool isReserved_ = false) : VariableBase(variable), scope_type(scope_type_), isReserved(isReserved_)
			{
				type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;
			}
		};
		
		struct Variable_ReservedScope_Upper : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Upper(VariableBase* base_)
			: VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Upper_, true),
			  base(base_)
			{
			}
			
			virtual std::string GetValue() override
			{
				std::string upperVariant;
				std::string currentValue = base->GetValue();

				for (const auto character : currentValue)
				{
					upperVariant += std::toupper(character);
				}

				return upperVariant;
			}
		};
		
		struct Variable_ReservedScope_Lower : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Lower(VariableBase* base_)
			: VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Lower_, true),
			  base(base_)
			{
			}
			
			virtual std::string GetValue() override
			{
				std::string lowerVariant;
				std::string currentValue = base->GetValue();

				for (const auto character : currentValue)
				{
					lowerVariant += std::tolower(character);
				}

				return lowerVariant;
			}
		};
		
		struct Variable_ReservedScope_Snake : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Snake(VariableBase* base_)
			: VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Snake_, true),
			  base(base_)
			{
			}
			
			virtual std::string GetValue() override
			{
				std::string snakeVariant;
				std::string currentValue = base->GetValue();
				
				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						snakeVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}
						
						snakeVariant += '_';
						lastWasNonAlpha = true;
					}
				}
				
				// If it contains text
				// remove the tail
				if (!snakeVariant.empty() && lastWasNonAlpha)
				{
					snakeVariant.pop_back();
				}

				return snakeVariant;
			}
		};
		
		struct Variable_ReservedScope_Slash : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_Slash(VariableBase* base_)
			: VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Slash_, true),
			  base(base_)
			{
			}
			
			virtual std::string GetValue() override
			{
				std::string slashVariant;
				std::string currentValue = base->GetValue();
				
				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						slashVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}
						
						slashVariant += '/';
						lastWasNonAlpha = true;
					}
				}
				
				// If it contains text
				// remove the tail
				if (!slashVariant.empty() && lastWasNonAlpha)
				{
					slashVariant.pop_back();
				}

				return slashVariant;
			}
		};
		
		struct Variable_ReservedScope_DoubleColon : public VariableScope
		{
			VariableBase* base;
			Variable_ReservedScope_DoubleColon(VariableBase* base_)
			: VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::DoubleColon_, true),
			  base(base_)
			{
			}
			
			virtual std::string GetValue() override
			{
				std::string doubleColonVariant;
				std::string currentValue = base->GetValue();
				
				bool lastWasNonAlpha = true;
				for (const auto character : currentValue)
				{
					if (std::isalpha(character))
					{
						doubleColonVariant += character;
						lastWasNonAlpha = false;
					}
					else
					{
						if (lastWasNonAlpha)
						{
							continue;
						}
						
						doubleColonVariant += "::";
						lastWasNonAlpha = true;
					}
				}
				
				// If it contains text
				// remove the tail
				if (!doubleColonVariant.empty() && lastWasNonAlpha)
				{
					doubleColonVariant.pop_back();
					doubleColonVariant.pop_back();
				}

				return doubleColonVariant;
			}
		};

		struct VariableScopes : public VariableBase
		{
			// Default scopes
			VariableBase* default_ = new VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Default_, true);
			VariableBase* upper_ = new Variable_ReservedScope_Upper(this);
			VariableBase* lower_ = new Variable_ReservedScope_Lower(this);
			
			VariableBase* snake_ = new Variable_ReservedScope_Snake(this);
			VariableBase* slash_ = new Variable_ReservedScope_Slash(this);
			VariableBase* double_colon_ = new Variable_ReservedScope_DoubleColon(this);
			
			VariableBase* variable_field_ = new VariableScope(::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Variable_Field_, true);
			VariableBase* variable_field_separator_ = new VariableScope("\n", ::dupr::generation::cpp::templates::StatementTemplate::ScopeType::Variable_Field_Separator_, true);

			// Ctor
			VariableScopes() : VariableBase() {}

			VariableScopes(const char* text) : VariableBase(text) {}

			VariableScopes(const std::string& text) : VariableBase(text) {}

			VariableScopes(std::vector<VariableBase*> variables) : VariableBase(variables) {}

			// Dtor
			virtual ~VariableScopes() override = default;

			// Calls
			VariableBase* Default()
			{
				return default_;
			}
			VariableBase* Upper()
			{
				return upper_;
			}

			VariableBase* Lower()
			{
				return lower_;
			}

			VariableBase* Underscore()
			{
				return snake_;
			}

			VariableBase* Snake()
			{
				return snake_;
			}

			VariableBase* Slash()
			{
				return slash_;
			}

			VariableBase* DoubleColon()
			{
				return double_colon_;
			}

			VariableBase* Variable_Field()
			{
				return variable_field_;
			}

			VariableBase* Variable_Field_Separator()
			{
				return variable_field_separator_;
			}

			void ExpandVariableField()
			{
				// currentvalue + separator
				const auto currentValue = GetValue() + Variable_Field_Separator()->GetValue();
				*Variable_Field() += currentValue;
			}
		};

	public:
		
struct Variable_conditional_else_ : public VariableScopes
{

static constexpr auto name = "conditional_else_";



Variable_conditional_else_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_;
}

virtual ~Variable_conditional_else_() override = default;

Variable_conditional_else_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_;

}



Variable_conditional_else_& operator=(const Variable_conditional_else_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_conditional_else_if_ : public VariableScopes
{

static constexpr auto name = "conditional_else_if_";



Variable_conditional_else_if_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_if_;
}

virtual ~Variable_conditional_else_if_() override = default;

Variable_conditional_else_if_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_else_if_;

}



Variable_conditional_else_if_& operator=(const Variable_conditional_else_if_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_conditional_if_ : public VariableScopes
{

static constexpr auto name = "conditional_if_";



Variable_conditional_if_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_if_;
}

virtual ~Variable_conditional_if_() override = default;

Variable_conditional_if_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::conditional_if_;

}



Variable_conditional_if_& operator=(const Variable_conditional_if_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_expression_ : public VariableScopes
{

static constexpr auto name = "expression_";



Variable_expression_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::expression_;
}

virtual ~Variable_expression_() override = default;

Variable_expression_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::expression_;

}



Variable_expression_& operator=(const Variable_expression_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_external_statement_ : public VariableScopes
{

static constexpr auto name = "external_statement_";



Variable_external_statement_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::external_statement_;
}

virtual ~Variable_external_statement_() override = default;

Variable_external_statement_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::external_statement_;

}



Variable_external_statement_& operator=(const Variable_external_statement_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_file_ : public VariableScopes
{

static constexpr auto name = "file_";

VariableBase* Content_ = GenerateVariable("");
VariableBase* Class_postfix_ = GenerateVariable("");
VariableBase* Extension_ = GenerateVariable("");
VariableBase* File_name_ = GenerateVariable("");
VariableBase* Namespace_ = GenerateVariable("");
VariableBase* Target_language_ = GenerateVariable("");


Variable_file_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::file_;
}

virtual ~Variable_file_() override = default;

Variable_file_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::file_;
*static_cast<VariableBase*>(Content_) = VariableBase(std::vector<VariableBase*>({ GenerateVariable(statementtemplate_->statement_->This()) }));
Content_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;

*static_cast<VariableBase*>(Class_postfix_) = VariableBase(std::vector<VariableBase*>({  }));
Class_postfix_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;

*static_cast<VariableBase*>(Extension_) = VariableBase(std::vector<VariableBase*>({ GenerateVariable("h") }));
Extension_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;

*static_cast<VariableBase*>(File_name_) = VariableBase(std::vector<VariableBase*>({ GenerateVariable("Statement") }));
File_name_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;

*static_cast<VariableBase*>(Namespace_) = VariableBase(std::vector<VariableBase*>({ GenerateVariable("dupr::generation::cpp::templates") }));
Namespace_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;

*static_cast<VariableBase*>(Target_language_) = VariableBase(std::vector<VariableBase*>({ GenerateVariable("C++") }));
Target_language_->type = ::dupr::generation::cpp::templates::StatementTemplate::Type::Scope;


}


VariableBase* Content() const
{
	return Content_;
}

VariableBase* Class_postfix() const
{
	return Class_postfix_;
}

VariableBase* Extension() const
{
	return Extension_;
}

VariableBase* File_name() const
{
	return File_name_;
}

VariableBase* Namespace() const
{
	return Namespace_;
}

VariableBase* Target_language() const
{
	return Target_language_;
}


Variable_file_& operator=(const Variable_file_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	*Content_ = *variable.Content_;
*Class_postfix_ = *variable.Class_postfix_;
*Extension_ = *variable.Extension_;
*File_name_ = *variable.File_name_;
*Namespace_ = *variable.Namespace_;
*Target_language_ = *variable.Target_language_;


	return *this;
}

};

struct Variable_left_angle_bracket_ : public VariableScopes
{

static constexpr auto name = "left_angle_bracket_";



Variable_left_angle_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_angle_bracket_;
}

virtual ~Variable_left_angle_bracket_() override = default;

Variable_left_angle_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_angle_bracket_;

}



Variable_left_angle_bracket_& operator=(const Variable_left_angle_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_left_bracket_ : public VariableScopes
{

static constexpr auto name = "left_bracket_";



Variable_left_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_bracket_;
}

virtual ~Variable_left_bracket_() override = default;

Variable_left_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_bracket_;

}



Variable_left_bracket_& operator=(const Variable_left_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_left_curly_bracket_ : public VariableScopes
{

static constexpr auto name = "left_curly_bracket_";



Variable_left_curly_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_curly_bracket_;
}

virtual ~Variable_left_curly_bracket_() override = default;

Variable_left_curly_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::left_curly_bracket_;

}



Variable_left_curly_bracket_& operator=(const Variable_left_curly_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_return_statement_ : public VariableScopes
{

static constexpr auto name = "return_statement_";



Variable_return_statement_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::return_statement_;
}

virtual ~Variable_return_statement_() override = default;

Variable_return_statement_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::return_statement_;

}



Variable_return_statement_& operator=(const Variable_return_statement_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_right_angle_bracket_ : public VariableScopes
{

static constexpr auto name = "right_angle_bracket_";



Variable_right_angle_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_angle_bracket_;
}

virtual ~Variable_right_angle_bracket_() override = default;

Variable_right_angle_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_angle_bracket_;

}



Variable_right_angle_bracket_& operator=(const Variable_right_angle_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_right_bracket_ : public VariableScopes
{

static constexpr auto name = "right_bracket_";



Variable_right_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_bracket_;
}

virtual ~Variable_right_bracket_() override = default;

Variable_right_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_bracket_;

}



Variable_right_bracket_& operator=(const Variable_right_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_right_curly_bracket_ : public VariableScopes
{

static constexpr auto name = "right_curly_bracket_";



Variable_right_curly_bracket_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_curly_bracket_;
}

virtual ~Variable_right_curly_bracket_() override = default;

Variable_right_curly_bracket_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::right_curly_bracket_;

}



Variable_right_curly_bracket_& operator=(const Variable_right_curly_bracket_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_statement_ : public VariableScopes
{

static constexpr auto name = "statement_";



Variable_statement_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::statement_;
}

virtual ~Variable_statement_() override = default;

Variable_statement_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::statement_;

}



Variable_statement_& operator=(const Variable_statement_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_var_name_ : public VariableScopes
{

static constexpr auto name = "var_name_";



Variable_var_name_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::var_name_;
}

virtual ~Variable_var_name_() override = default;

Variable_var_name_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::var_name_;

}



Variable_var_name_& operator=(const Variable_var_name_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_var_type_ : public VariableScopes
{

static constexpr auto name = "var_type_";



Variable_var_type_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::var_type_;
}

virtual ~Variable_var_type_() override = default;

Variable_var_type_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::var_type_;

}



Variable_var_type_& operator=(const Variable_var_type_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_variable_assignment_ : public VariableScopes
{

static constexpr auto name = "variable_assignment_";



Variable_variable_assignment_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_assignment_;
}

virtual ~Variable_variable_assignment_() override = default;

Variable_variable_assignment_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_assignment_;

}



Variable_variable_assignment_& operator=(const Variable_variable_assignment_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_variable_declaration_ : public VariableScopes
{

static constexpr auto name = "variable_declaration_";



Variable_variable_declaration_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_declaration_;
}

virtual ~Variable_variable_declaration_() override = default;

Variable_variable_declaration_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_declaration_;

}



Variable_variable_declaration_& operator=(const Variable_variable_declaration_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};

struct Variable_variable_initialization_ : public VariableScopes
{

static constexpr auto name = "variable_initialization_";



Variable_variable_initialization_() : VariableScopes()
{
	type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_initialization_;
}

virtual ~Variable_variable_initialization_() override = default;

Variable_variable_initialization_(StatementTemplate* statementtemplate_, const std::vector<VariableBase*>& variables) : VariableScopes(variables)
{
type = ::dupr::generation::cpp::templates::StatementTemplate::Type::variable_initialization_;

}



Variable_variable_initialization_& operator=(const Variable_variable_initialization_& variable)
{
	if (&variable == this)
	{
		return *this;
	}

	value = variable.value;
	isString = variable.isString;

	

	return *this;
}

};


	public:
		inline static std::vector<VariableBase*> variables_to_delete = std::vector<VariableBase*>();

	public:
		std::vector<VariableBase*> variables_;

	public:
		// Members that one can directly access.
		// e.g. StatementTemplate.member = "auto-generated";
		Variable_conditional_else_* conditional_else_ = new Variable_conditional_else_();
Variable_conditional_else_if_* conditional_else_if_ = new Variable_conditional_else_if_();
Variable_conditional_if_* conditional_if_ = new Variable_conditional_if_();
Variable_expression_* expression_ = new Variable_expression_();
Variable_external_statement_* external_statement_ = new Variable_external_statement_();
Variable_file_* file_ = new Variable_file_();
Variable_left_angle_bracket_* left_angle_bracket_ = new Variable_left_angle_bracket_();
Variable_left_bracket_* left_bracket_ = new Variable_left_bracket_();
Variable_left_curly_bracket_* left_curly_bracket_ = new Variable_left_curly_bracket_();
Variable_return_statement_* return_statement_ = new Variable_return_statement_();
Variable_right_angle_bracket_* right_angle_bracket_ = new Variable_right_angle_bracket_();
Variable_right_bracket_* right_bracket_ = new Variable_right_bracket_();
Variable_right_curly_bracket_* right_curly_bracket_ = new Variable_right_curly_bracket_();
Variable_statement_* statement_ = new Variable_statement_();
Variable_var_name_* var_name_ = new Variable_var_name_();
Variable_var_type_* var_type_ = new Variable_var_type_();
Variable_variable_assignment_* variable_assignment_ = new Variable_variable_assignment_();
Variable_variable_declaration_* variable_declaration_ = new Variable_variable_declaration_();
Variable_variable_initialization_* variable_initialization_ = new Variable_variable_initialization_();


	public:
		StatementTemplate()
		{
			*conditional_else_ = Variable_conditional_else_(this, std::vector<VariableBase*>({ GenerateVariable("else\n"), GenerateVariable("{"), GenerateVariable("\n\t"), GenerateVariable(external_statement_->Variable_Field()), GenerateVariable("\n"), GenerateVariable("}") }));
*conditional_else_if_ = Variable_conditional_else_if_(this, std::vector<VariableBase*>({ GenerateVariable("else if("), GenerateVariable(expression_->This()), GenerateVariable(")\n"), GenerateVariable("{"), GenerateVariable("\n\t"), GenerateVariable(external_statement_->Variable_Field()), GenerateVariable("\n"), GenerateVariable("}") }));
*conditional_if_ = Variable_conditional_if_(this, std::vector<VariableBase*>({ GenerateVariable("if("), GenerateVariable(expression_->This()), GenerateVariable(")\n"), GenerateVariable("{"), GenerateVariable("\n\t"), GenerateVariable(external_statement_->Variable_Field()), GenerateVariable("\n"), GenerateVariable("}") }));
*expression_ = Variable_expression_(this, std::vector<VariableBase*>({  }));
*external_statement_ = Variable_external_statement_(this, std::vector<VariableBase*>({  }));
*file_ = Variable_file_(this, std::vector<VariableBase*>({  }));
*left_angle_bracket_ = Variable_left_angle_bracket_(this, std::vector<VariableBase*>({ GenerateVariable("<") }));
*left_bracket_ = Variable_left_bracket_(this, std::vector<VariableBase*>({ GenerateVariable("{") }));
*left_curly_bracket_ = Variable_left_curly_bracket_(this, std::vector<VariableBase*>({ GenerateVariable("(") }));
*return_statement_ = Variable_return_statement_(this, std::vector<VariableBase*>({ GenerateVariable("return "), GenerateVariable(expression_->This()), GenerateVariable(";") }));
*right_angle_bracket_ = Variable_right_angle_bracket_(this, std::vector<VariableBase*>({ GenerateVariable(">") }));
*right_bracket_ = Variable_right_bracket_(this, std::vector<VariableBase*>({ GenerateVariable("}") }));
*right_curly_bracket_ = Variable_right_curly_bracket_(this, std::vector<VariableBase*>({ GenerateVariable(")") }));
*statement_ = Variable_statement_(this, std::vector<VariableBase*>({  }));
*var_name_ = Variable_var_name_(this, std::vector<VariableBase*>({  }));
*var_type_ = Variable_var_type_(this, std::vector<VariableBase*>({  }));
*variable_assignment_ = Variable_variable_assignment_(this, std::vector<VariableBase*>({ GenerateVariable(var_name_->This()), GenerateVariable(" = "), GenerateVariable(expression_->This()), GenerateVariable(";") }));
*variable_declaration_ = Variable_variable_declaration_(this, std::vector<VariableBase*>({ GenerateVariable(var_type_->This()), GenerateVariable(" "), GenerateVariable(var_name_->This()), GenerateVariable(";") }));
*variable_initialization_ = Variable_variable_initialization_(this, std::vector<VariableBase*>({ GenerateVariable(var_type_->This()), GenerateVariable(" "), GenerateVariable(var_name_->This()), GenerateVariable(" = "), GenerateVariable(expression_->This()), GenerateVariable(";") }));


			variables_.emplace_back(conditional_else_);
variables_.emplace_back(conditional_else_if_);
variables_.emplace_back(conditional_if_);
variables_.emplace_back(expression_);
variables_.emplace_back(external_statement_);
variables_.emplace_back(file_);
variables_.emplace_back(left_angle_bracket_);
variables_.emplace_back(left_bracket_);
variables_.emplace_back(left_curly_bracket_);
variables_.emplace_back(return_statement_);
variables_.emplace_back(right_angle_bracket_);
variables_.emplace_back(right_bracket_);
variables_.emplace_back(right_curly_bracket_);
variables_.emplace_back(statement_);
variables_.emplace_back(var_name_);
variables_.emplace_back(var_type_);
variables_.emplace_back(variable_assignment_);
variables_.emplace_back(variable_declaration_);
variables_.emplace_back(variable_initialization_);

		}

		virtual ~StatementTemplate()
		{
			for(auto* variable : variables_to_delete)
			{
				delete variable;
			}

			variables_to_delete.clear();
		}

	public:
		// Default DST functions

		/*!	\fn GetOutput
		 *
		 *	\brief returns the output with the given the current state.
		 */
		std::string GetOutput()
		{
			return file_->Content()->GetValue();
		}

		/*!	\fn GetVariables
		 *
		 *	\brief Returns all top level variables known in this template.
		 */
		std::vector<VariableBase*> GetVariables()
		{
			return variables_;
		}

	public:
	};
}

#endif // DUPR_GENERATION_CPP_TEMPLATES_STATEMENTTEMPLATE_h
