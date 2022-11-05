#include "IRSourceGenerator.h"


std::string IRSourceGenerator::generate(fgvm::FArgValue* value)
{
	std::string type = IRUtils::enumTypeToStr(value->content->getTypeId());
	return IRUtils::format("{0} {1}", {type, value->name});
}

std::string IRSourceGenerator::generate(fgvm::FunctionCallValue* value)
{
	std::string src = "%{0} = {1} {2} {3}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	std::vector<std::string> input_chunk;
	for (auto input : value->arg_inputs)
		input_chunk.push_back("%" + input->name);

	std::string in_str = IRUtils::join(input_chunk, SEPARATOR);

	return IRUtils::format(
		src,
		{ value->name, type, value->called_func_name, in_str }
	);
}

std::string IRSourceGenerator::generate(fgvm::RetValue* value)
{
	std::string src = "ret {0} %{1}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	return IRUtils::format(
		src,
		{ type, value->content->name }
	);
}

std::string IRSourceGenerator::generate(fgvm::SARRefValue* value)
{
	std::string src = "%{0} = {1} ref %{2}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	return IRUtils::format(
		src,
		{ value->name, type, value->derefValue()->name}
	);
}

std::string IRSourceGenerator::generate(fgvm::SARValue* value)
{
	std::string src = "%{0} = {1} {2}";
	std::string type = IRUtils::enumTypeToStr(value->expectedReductionTypeID());

	return IRUtils::format(
		src,
		{ value->name, type, value->content->storedValueAsString() }
	);
}

std::string IRSourceGenerator::generate(fgvm::Bloc* stmt)
{
	return std::string();
}

std::string IRSourceGenerator::generate(fgvm::ConditionalBr* stmt)
{
	return std::string();
}

std::string IRSourceGenerator::generate(fgvm::FunctionDef* stmt)
{
	return std::string();
}

std::string IRSourceGenerator::generate(fgvm::Loop* stmt)
{
	return std::string();
}
