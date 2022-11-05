#pragma once

#include "../SourceGenerator.h"

class IRSourceGenerator : public SourceGenerator 
{
public:
	// values
	std::string generate(fgvm::FArgValue* value) override;
	std::string generate(fgvm::FunctionCallValue* value) override;
	std::string generate(fgvm::RetValue* value) override;
	std::string generate(fgvm::SARRefValue* value) override;
	std::string generate(fgvm::SARValue* value) override;

	// bloc statements
	std::string generate(fgvm::Bloc* stmt) override;
	std::string generate(fgvm::ConditionalBr* stmt) override;
	std::string generate(fgvm::FunctionDef* stmt) override;
	std::string generate(fgvm::Loop* stmt) override;
};