#pragma once

namespace fgvm {
    enum EType {
        Unknown = -1,
        Uint8,
        Uint16,
        Uint64,
        Uint32,
        Int8,
        Int16,
        Int32,
        Int64,
        Float32,
        Float64,
        Bool,
        Str,
        Void
    };

    enum EValueType {
        UnknownID = -1,
        FArgumentID,
        AssignementID,
        AssignRefID,
        FunctionCallID,
        ReturnID
    };

    enum EStatementType {
        FunDefStmt,
        ValueStmt,
        BlocStmt,
        IfStmt,
        LoopStmt
    };
}