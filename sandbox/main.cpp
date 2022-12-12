#include <iostream>

#include "fgvm/core/fgvm.h"
#include "fgvm/core/utils/IRUtils.h"

#include "fgvm/core/generator/ir-generator/IRSourceGenerator.h"
#include "fgvm/core/generator/NameGenerator.h"

// #include "fgvm/core/analytic-tools/Lexer.h"

#include "fgvm/examples/fg-script/FGLexer.h"
#include "fgvm/examples/brainfuck/BrainfLexer.h"
#include "fgvm/examples/brainfuck/BrainfParser.h"

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
    auto s2 = builder->createGetAddrOf("y", s1);
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
    
    auto s1 = builder->createValue("test", new I32(8));
    auto s2 = builder->createValue("test2", new I32(9));
    auto s3 = builder->createValue("ok", new STR("All ok!"));
    auto s4 = builder->createGetAddrOf("m_ref", s3);
    auto s5 = builder->createGetValAddr("deref", s4); 
    auto res_div = builder->createDiv("res_div", args[0], args[1]);
    auto ret_val = builder->createReturn(res_div);

    // test custom call
    auto alloc_size = builder->createValue("alloc_size", new U32(6));
    auto alloc_mem = builder->createAlloc("alloc", alloc_size);
    auto set_ref = builder->createSetValAddr("same_ref", alloc_mem, s1);
    auto suppose_i_am_anything = builder->createValue("something", new I32(1234));
    auto off__ref = builder->createSetValAddr("same_ref", alloc_mem, suppose_i_am_anything);

    // test bool if and loop

    // if statement
    auto test_bool = builder->createValue("m_bool", new BOOL(false));
    auto if_bloc = builder->createBloc("if_bloc");
    if_bloc->addStmt(builder->createValue("m_bool", new BOOL(false)));
    auto if_stmt = builder->createIF(test_bool, if_bloc, nullptr);
    // loop
    auto loop_bloc = builder->createBloc("loop_bloc");
    auto to_incr = builder->createValue("temp_i", new U32(0));
    auto max_val = builder->createValue("max_val", new U32(10));
    auto compare = builder->createCompLT("less_t", to_incr, max_val);
    loop_bloc->addStmt(builder->createIncr(max_val));
    loop_bloc->addStmt(compare);
    auto loop_stmt = builder->createLoop(compare, loop_bloc);
    
    // setup the call chain
    auto bloc = builder->createBloc("func_body");
    bloc->addStmt(s1);
    bloc->addStmt(s2);
    bloc->addStmt(s3);
    bloc->addStmt(s4);
    bloc->addStmt(s5);
    bloc->addStmt(alloc_size);
    bloc->addStmt(alloc_mem);
    bloc->addStmt(suppose_i_am_anything);
    bloc->addStmt(off__ref);
    bloc->addStmt(set_ref);
    bloc->addStmt(res_div);
    bloc->addStmt(test_bool);
    bloc->addStmt(if_stmt);
    bloc->addStmt(compare);
    bloc->addStmt(loop_stmt);

    // bloc->addStmt(ret_val); // throws an error
    // bloc->setRetValue(builder->createReturn(s4)); // throws an error
    bloc->setRetValue(ret_val);

    auto fdef = builder->createFunc("someFunc", args, bloc, EType::Int32);

    IRSourceGenerator generator;
    std::cout << IRUtils::prettifyIRSourceCode(generator.generate(fdef));
}

void testVariables() {
    using namespace fgvm;


    auto seq = builder->createStmtSequence();

    auto x = builder->createValue("x", new I32(1));
    auto y = builder->createValue("y", new I32(2));
    auto x1 = builder->createValue("x", new I32(1234));


    seq->setSequence({ x, y, x1 });

    IRSourceGenerator generator;
    std::cout << IRUtils::prettifyIRSourceCode(generator.generate(seq));
}

void testLexer1() {
    class CustomLexer : public Lexer {
    public:
        CustomLexer(std::string source, std::string filepath)
            : Lexer(source, filepath) {}
    };

    std::string file = "<sandbox>";
    std::string source = "hello world does it \"work\" 123.65";

    CustomLexer lexer(source, file);
    auto res = lexer.tokenize();
    std::cout << "N tokens " << res.size() << std::endl;
    for (auto& token : res) {
        std::cout << token.to_string() << std::endl;
    }
}

void testLexer2() {
    using namespace FGScript;
    std::string file = "<sandbox>";
    std::string source = "one + two - 171.0654 = \"three!\"";

    FGLexer lexer(source, file);
    auto res = lexer.tokenize();
    std::cout << "N tokens " << res.size() << std::endl;
    for (auto& token : res) {
        std::cout << token.to_string() << std::endl;
    }
}


void testLexerBrainfuck() {
    using namespace Brainf_ck;
    std::string file = "<sandbox>";
    std::string source = "+++[>+++++[>+++++<-]<-]>>----------.+++++.+++++++.----.++.----------.";
    // std::string source = "><++-+";

    BrainfLexer lexer(source, file);
    auto tokens = lexer.tokenize();
    // std::cout << "N tokens " << tokens.size() << std::endl;
    // for (auto& token : tokens)
    //    std::cout << token.to_string() << std::endl;

    BrainfParser parser(tokens);
    std::string ir_code = parser.compileToIntermediateCode();

    std::cout << IRUtils::prettifyIRSourceCode(ir_code);
}

void testStatementSeq() {
    auto test = builder->createStmtSequence();
    test->add(builder->createValue("456", new U8(123)));
    test->add(builder->createValue("456", new U8(123)));
    test->add(builder->createValue("123", new U8(123)));

    auto bloc = builder->createBloc("hey");
    bloc->addStmt(builder->createValue("789", new U8(123)));
    bloc->addStmt(builder->createValue("245", new U8(123)));
    bloc->addStmt(builder->createValue("111", new U8(123)));
    test->add(bloc);

    auto test2 = builder->createStmtSequence();
    test2->add(builder->createValue("_test2", new U8(123)));
    auto test3 = builder->createStmtSequence();
    test3->add(builder->createValue("_test3", new U8(123)));

    test->add(test2);
    test->add(test3);

    IRSourceGenerator generator;
    std::string ir_code = generator.generate(test);
    std::cout << IRUtils::prettifyIRSourceCode(ir_code);
}

void testNameGenerator() {
    NameGenerator generator;
    std::cout << generator.get("x") << std::endl;
    std::cout << generator.get("x") << std::endl;
    std::cout << generator.get("y") << std::endl;
    std::cout << generator.get("z") << std::endl;
    std::cout << generator.get("x") << std::endl;
    std::cout << generator.get("y") << std::endl;
    std::cout << generator.get("y") << std::endl;
    std::cout << generator.get("x") << std::endl;
}

int main() 
{
    try {
        // sandbox2();
        // testFunc();
        // testLexer1();
        // testLexer2();
        testLexerBrainfuck();
        // testVariables();
        // testNameGenerator();
    }
    catch (std::logic_error& err) {
        std::cerr << "Oups !\n";
        std::cerr << "Logic error : " << err.what();
    }
    catch (std::exception& err) {
        std::cerr << "Exception : " << err.what();
    }
    return 0;
}