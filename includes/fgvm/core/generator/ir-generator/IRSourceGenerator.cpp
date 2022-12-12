#include "IRSourceGenerator.h"
#include <string>
#include <string_view>

std::string IRSourceGenerator::generate(fgvm::StatementSequence* stmt_seq)
{
	std::vector<std::string> lines;
	auto statements = stmt_seq->getSequence();
	for (auto stmt : statements)
		lines.push_back(dynamic_cast<SourceGenerator*>(this)->generate(stmt));

	return IRUtils::join(lines, INSTR_SEPARATOR);
}

std::string IRSourceGenerator::generate(fgvm::FArgValue* value)
{
	std::string type = IRUtils::enumTypeToStr(value->content->getTypeId());
	return IRUtils::format("{0} {1}", {type, sym_name->latest(value->name)});
}

std::string IRSourceGenerator::generate(fgvm::FunctionCustomCallValue* value)
{
	std::string src = "%{0} = {1} {2} {3}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	std::vector<std::string> input_chunk;
	for (auto input : value->arg_inputs)
		input_chunk.push_back("%" + sym_name->latest(input->name));

	std::string in_str = IRUtils::join(input_chunk, SEPARATOR);

	return IRUtils::format(
		src,
		{ sym_name->get(value->name), type, sym_name->latest(value->called_func_name), in_str }
	);
}

std::string IRSourceGenerator::generate(fgvm::RetValue* value)
{
	std::string src = "@ret {0} %{1}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	return IRUtils::format(
		src,
		{ type, sym_name->latest(value->content->name) }
	);
}

std::string IRSourceGenerator::generate(fgvm::SARRefValue* value)
{
	std::string src = "%{0} = {1} ref %{2}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	return IRUtils::format(
		src,
		{ sym_name->get(value->name), type, sym_name->latest(value->derefValue()->name) }
	);
}

std::string IRSourceGenerator::generate(fgvm::SARValue* value)
{
	std::string src = "%{0} = {1} {2}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());
	std::string stored_value = value->content->storedValueAsString();
	if (value->expectedReductionTypeID() == fgvm::EType::Str)
		stored_value = "\"" + stored_value + "\"";
	return IRUtils::format(
		src,
		{ sym_name->get(value->name), type, stored_value }
	);
}

std::string IRSourceGenerator::generate(fgvm::Bloc* bloc)
{
	std::string src = "@bloc {0}: {\n{1}\n}";
	std::vector<std::string> body_str;
	std::queue<fgvm::Statement*> qstmt = bloc->getStmt();
	while (!qstmt.empty()) {
		auto item = qstmt.front();
		body_str.push_back(dynamic_cast<SourceGenerator*>(this)->generate(item));
		qstmt.pop();
	}

	auto ret_value = bloc->getRetValue();
	if (ret_value)
		body_str.push_back(generate(ret_value));

	return IRUtils::format(
		src,
		{bloc->name, IRUtils::join(body_str, INSTR_SEPARATOR)}
	);
}

std::string IRSourceGenerator::generate(fgvm::ConditionalBr* if_stmt)
{
	std::string src = "@if %{0} {1} @else {2}\n{3}";

	std::string cond_var = sym_name->latest(if_stmt->condition->name);
	auto true_bloc = if_stmt->true_bloc;
	auto else_bloc = if_stmt->else_bloc;


	if (else_bloc == nullptr) {
		src = "@if %{0} {1}\n{2}";
		return IRUtils::format(
			src,
			{ cond_var, true_bloc->name, generate(true_bloc) }
		);
	}

	std::string bloc_a = generate(true_bloc) + INSTR_SEPARATOR;
	std::string bloc_b = generate(else_bloc);

	return IRUtils::format(
		src, 
		{ cond_var, true_bloc->name, else_bloc->name, bloc_a, bloc_b }
	);
}

std::string IRSourceGenerator::generate(fgvm::FunctionDef* fn_stmt)
{
	std::string src = "@defun {0} {1} ({2}) {3}\n{4}";
	std::string ret_type = IRUtils::enumTypeToStr(fn_stmt->ret_type);
	std::string f_name = sym_name->get(fn_stmt->name);

	std::vector<std::string> arg_vec;
	for (auto arg : fn_stmt->arguments)
		arg_vec.push_back(generate(arg));
	
	std::string f_args = IRUtils::join(arg_vec, ARG_SEP);
	std::string target_f_bloc = fn_stmt->bloc_def->name;
	std::string f_body = generate(fn_stmt->bloc_def) + INSTR_SEPARATOR;

	return IRUtils::format(
		src,
		{ret_type, f_name, f_args, target_f_bloc, f_body}
	);
}

std::string IRSourceGenerator::generate(fgvm::Loop* loop_stmt)
{
	std::string src = "@loop %{0} {1}\n{2}";
	std::string cond_var = sym_name->latest(loop_stmt->condition->name);
	std::string bloc_name = loop_stmt->loop_bloc->name;
	std::string l_bloc = generate(loop_stmt->loop_bloc);
	return IRUtils::format(
		src,
		{cond_var, bloc_name, l_bloc}
	);
}
