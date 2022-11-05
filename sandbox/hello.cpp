#include <iostream>

#include "fgvm/core/fgvm.h"
#include "fgvm/core/utils/IRUtils.h"


using namespace fgvm;

Module* mod_container = new Module;
CodeBuilder* builder = new CodeBuilder(mod_container);

void sandbox1()
{

    using namespace fgvm;

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
}
int main() 
{
    sandbox1();
    return 0;
}