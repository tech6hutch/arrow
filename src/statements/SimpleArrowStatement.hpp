/// (c) Ben Jones 2019 - present

#pragma once

#include "Statement.hpp"
#include "lexer/Token.hpp"
#include "expressions/Expression.hpp"
#include "receivers/Receiver.hpp"

#include <memory>

namespace arrow {
    
    // Describes a statement of the form
    // expression -> identifier;
    // or
    // expression -> identifier[expression];
    class SimpleArrowStatement : public Statement
    {
      public:
        SimpleArrowStatement(long const lineNumber);
        SimpleArrowStatement & withExpression(std::shared_ptr<Expression> expression);
        SimpleArrowStatement & withIdentifier(std::shared_ptr<Receiver> identifier);
        SimpleArrowStatement & withIndexExpression(std::shared_ptr<Expression> expression);

        std::shared_ptr<Receiver> getIdentifier() const;
        std::shared_ptr<Expression> getExpression() const;
        std::shared_ptr<Expression> getIndexExpression() const;

        std::string toString() const override;
        std::shared_ptr<StatementEvaluator> getEvaluator() const override;

      private:
        std::shared_ptr<Expression> m_expression;
        std::shared_ptr<Receiver> m_identifier;
        std::shared_ptr<Expression> m_indexExpression;
    };

}