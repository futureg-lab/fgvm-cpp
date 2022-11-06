#include <iostream>

#include "fgvm/core/fgvm.h"
#include "fgvm/core/utils/IRUtils.h"

#include "fgvm/core/generator/ir-generator/IRSourceGenerator.h"

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

void sandbox2()
{
    using namespace fgvm;
    auto generator = new IRSourceGenerator();
    auto s1 = builder->createValue("x", new I32(2));
    auto s2 = builder->createRef("y", s1);
    auto ret = builder->createReturn(s2);

    auto s_add = builder->createAdd("res", builder->createValue("a", new I32(4)), builder->createValue("b", new I32(7)));

    std::cout << ((SourceGenerator*)generator)->generate(s1) << std::endl;
    std::cout << ((SourceGenerator*)generator)->generate(s2) << std::endl;
    std::cout << ((SourceGenerator*)generator)->generate(ret) << std::endl;
    std::cout << generator->generate((FunctionCallValue*)s_add) << std::endl;
}

void testFunc() {
    using namespace fgvm;

    std::vector<FArgValue*> args = {
        builder->createArg("x", EType::Int32),
        builder->createArg("y", EType::Int32)
    };
    
    auto s1 = builder->createValue("x", new I32(8));
    auto s2 = builder->createValue("y", new I32(9));
    auto res_div = builder->createDiv("res_div", s1, s2);
    auto ret_val = builder->createReturn(res_div);

    auto bloc = builder->createBloc("func_body");
    bloc->addStmt(s1);
    bloc->addStmt(s2);
    bloc->addStmt(res_div);

    // bloc->addStmt(ret_val); // throw an error
    bloc->setRetValue(ret_val);

    auto fdef = builder->createFunc("someFunc", args, bloc, EType::Int32);

    IRSourceGenerator generator;
    std::cout << generator.generate(fdef);
}

int main() 
{
    // sandbox2();
    testFunc();
    return 0;
}