#include "SingleEqualExpression.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include <utility>

namespace arrow {

    SingleEqualExpression::SingleEqualExpression(long const lineNumber) 
      : Expression(lineNumber)
      , m_token()
    {
    }

    std::shared_ptr<ExpressionEvaluator> SingleEqualExpression::getEvaluator() const
    {
        struct SingleEqualEvaluator : public ExpressionEvaluator
        {
            Type evaluate(Cache & cache) const override
            {
                return {TypeDescriptor::SingleEqual, std::string("=")};
            }
        };
        return std::make_shared<SingleEqualEvaluator>();
    }

    DecayType SingleEqualExpression::decayType() const
    {
        return DecayType::DECAYS_TO_STRING;
    }

    SingleEqualExpression & SingleEqualExpression::withToken(Token token)
    {
        m_token = std::move(token);
        return *this;
    }

    std::string SingleEqualExpression::toString() const
    {
        return ""; // TODO
    }
}