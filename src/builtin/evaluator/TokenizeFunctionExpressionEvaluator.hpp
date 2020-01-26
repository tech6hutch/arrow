/// (c) Ben Jones 2020

#pragma once

#include "expressions/evaluator/ExpressionEvaluator.hpp"
#include "builtin/TokenizeFunctionExpression.hpp"
#include "representation/Cache.hpp"

namespace arrow {
    class TokenizeFunctionExpressionEvaluator : public ExpressionEvaluator
    {
      public:
        explicit TokenizeFunctionExpressionEvaluator(TokenizeFunctionExpression expression);
        Type evaluate(Cache&) const override;
      private:
        TokenizeFunctionExpression m_expression;
    };
}