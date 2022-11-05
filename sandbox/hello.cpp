#include <iostream>

#include "fgvm/core/fgvm.h"
#include "fgvm/core/utils/IRUtils.h"

#include <memory>

using namespace fgvm;

std::unique_ptr<Module> mod_container = std::make_unique<Module>();
std::unique_ptr<CodeBuilder> builder = std::make_unique<CodeBuilder>(mod_container.get());

void sandbox1()
{
    Value* x = builder->createValue("xxx", new I64(6));
    Value* y = builder->createValue("yyy", new I64(13));

    Value* add_res = builder->createAdd("m_res", x, y);

    FunctionCallValue* v_add = dynamic_cast<FunctionCallValue*> (add_res);

    SARValue* xx = (SARValue*)x;
    std::cout
        << "name : " << xx->name << "\n"
        << "type : " << IRUtils::enumTypeToStr(xx->content->getTypeId()) << "\n"
        << "args : " << xx->content->storedValueAsString() << "\n\n";


    SARValue* yy = (SARValue*)y;
    std::cout
        << "name : " << yy->name << "\n"
        << "type : " << IRUtils::enumTypeToStr(yy->content->getTypeId()) << "\n"
        << "args : " << yy->content->storedValueAsString() << "\n\n";

    std::cout
        << "name : " << v_add->name << "\n"
        << "args : " << v_add->arg_inputs.size() << "\n"
        << "type ret : " << IRUtils::enumTypeToStr(v_add->expectedReductionTypeID()) << "\n";

    // Test for bool
    std::cout << "\n** Test for bool **" << "\n";
    BOOL bl(false);
    std::cout
        << "Total bits " << bl.totalBits() << "\n"
        << "value " << bl.storedValueAsString() << std::endl;

    // Test char
    std::cout << "\n** Test for strings **" << "\n";
    STR my_str("hello, this is a message!");
    std::cout
        << "Total bits " << my_str.totalBits() << "\n"
        << "value " << my_str.storedValueAsString() << std::endl;

    // Test for void
    std::cout << "\n** Test for void **" << "\n";
    VOID vd;
    std::cout
        << "Total bits " << vd.totalBits() << "\n"
        << "value " << vd.storedValueAsString() << std::endl;

}


std::string codegen(fgvm::Value* value)
{
    std::string src = "";
    switch (value->valueTypeID())
    {
    case EValueType::AssignementID:
        src += "%" + ((SARValue*)value)->name + " = " + ((SARValue*)value)->content->storedValueAsString();
        break;
    case EValueType::FunctionCallID:
        src += "%" + ((FunctionCallValue*)value)->name + " = " + ((FunctionCallValue*)value)->called_func_name + " I got " + std::to_string(((FunctionCallValue*)value)->arg_inputs.size());
        break;
    default:
        FGError::ASSERT(false);
    }
    return src;
}

std::string codegen(fgvm::Bloc* bloc) 
{
    std::string src = bloc->name + ":{";

    auto qstmt = bloc->getStmt();
    while (!qstmt.empty()) 
    {
        Statement* stmt = qstmt.front();

        switch (stmt->stmtTypeId())
        {
        case EStatementType::BlocStmt:
            src += codegen(dynamic_cast<Bloc*>(stmt)) + "\n";
            break;
        case EStatementType::ValueStmt:
            src += codegen(dynamic_cast<Value*>(stmt)) + "\n";
            break;
        default:
            FGError::ASSERT(false); // unhandled
            break;
        }
        qstmt.pop();
    }
    src += "}";
    return src;
}

void sandbox2()
{
    using namespace fgvm;
    Bloc* my_scope = (Bloc*) builder->createBloc("some_bloc");
    
    Value* s1 = builder->createValue("x", new I32(2));
    Value* s2 = builder->createValue("y", new I32(4));
    Value* s_add = builder->createAdd("res", s1, s2);
 
    my_scope->addStmt(s1);
    my_scope->addStmt(s2);
    my_scope->addStmt(s_add);

    std::cout << codegen(my_scope);
}
int main() 
{
    sandbox2();
    return 0;
}