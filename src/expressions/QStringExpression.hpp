/// (c) Ben Jones 2019 - present

#pragma once

#include "Expression.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include "lexer/Token.hpp"
#include <memory>

namespace arrow {
    class QStringExpression : public Expression
    {
      public:
        QStringExpression(long const lineNumber);

        QStringExpression & withQStringToken(Token qStringToken);

        Token getQStringToken() const;

        std::shared_ptr<ExpressionEvaluator> getEvaluator() const override;

        std::string toString() const override;

      private:
        Token m_qStringToken;
    };
}