#pragma once

#include "../SourceGenerator.h"
#include <string>
#include <string_view>

class IRSourceGenerator : public SourceGenerator 
{
private:
	std::string SEPARATOR = " ";
	std::string ARG_SEP = ", ";
	std::string INSTR_SEPARATOR = "\n";
	std::string INDENT = "   ";
public:
	// values
	
	// Idea : (T3 %a1, T3 %a2, T3 %a3, ..., TN aN)
	// Example : i64 %x, i32 %y, str %z
	std::string generate(fgvm::FArgValue* value) override;

	// Idea : %var_name = out_type [$]fname arg1 arg2 ... arg3
	// Example 1 : %x = i32 add %z %y
	// Example 2 : %x = str $custom_fmt %my_str %my_val
	std::string generate(fgvm::FunctionCallValue* value) override;

	// Idea : ret type %var
	// Example : ret i32 %x
	std::string generate(fgvm::RetValue* value) override;

	// Idea : %var = type ref %var
	// Example : %x_ref = i32 ref %var 
	std::string generate(fgvm::SARRefValue* value) override;

	// Idea : %var = literal value
	// Example 1 : %x = i32 4
	// Example 2 : %x = str<5> "Hello"
	std::string generate(fgvm::SARValue* value) override;

	// bloc statements
	// Idea : \@bloc bloc_name : { statements }
	std::string generate(fgvm::Bloc* stmt) override;

	// Idea : \@if %cond bloc_name_if_true bloc_name_if_false
	// Example
	// if %x ok not_ok
	// \@bloc ok : { ret i32 %x }
	// \@bloc not_ok : { ret i32 %y }
	std::string generate(fgvm::ConditionalBr* stmt) override;

	// Idea : \@defun type func_name (T3 %a1, T3 %a2, ..., TN aN) target_bloc_name
	// Example :
	// \@defun i32 custom_add(i32 %x, i64 %y) cadd_bloc
	// \@bloc cadd_bloc { ... ... }
	std::string generate(fgvm::FunctionDef* stmt) override;

	// Idea : \@loop %cond bl_name_if_true
	// Example : 
	// \@loop %test my_bloc
	// \@bloc my_bloc { ... ... }
	std::string generate(fgvm::Loop* stmt) override;
};