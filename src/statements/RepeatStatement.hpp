#pragma once

#include "Statement.hpp"
#include "lexer/Token.hpp"
#include "expressions/Expression.hpp"
#include <memory>
#include <vector>

namespace jasl {
    
    class RepeatStatement : public Statement
    {
      public:
        RepeatStatement();
        RepeatStatement & withToken(Token token);
        RepeatStatement & withExpression(std::shared_ptr<Expression> expression);
        void addBodyStatement(std::shared_ptr<Statement> bodyStatement);
        std::string toString() const override;
      private:
        Token m_keywordToken; // the repeat keyword
        std::shared_ptr<Expression> m_expression;
        std::vector<std::shared_ptr<Statement>> m_bodyStatements;
    };

}