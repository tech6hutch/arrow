#include "ListWordExpression.hpp"
#include "evaluator/ExpressionEvaluator.hpp"
#include <utility>

namespace jasl {

    ListWordExpression::ListWordExpression()
     : Expression()
     , m_word()
    {
    }

    std::shared_ptr<ExpressionEvaluator> 
    ListWordExpression::getEvaluator() const
    {
        struct ListWordEvaluator : public ExpressionEvaluator {
            ListWordEvaluator(Token tok) : m_tok(std::move(tok))
            {
            }

            Type evaluate(Cache & cache) const override
            {
                return {TypeDescriptor::String, m_tok.raw};
            }
          private:
            Token m_tok;
        };
        return std::make_shared<ListWordEvaluator>(m_word);
    }

    DecayType ListWordExpression::decayType() const
    {
        return DecayType::DECAYS_TO_STRING;
    }

    ListWordExpression & ListWordExpression::withWordToken(Token word)
    {
        m_word = std::move(word);
        return *this;
    }

    Token ListWordExpression::getWordToken() const
    {
        return  m_word;
    }

    std::string ListWordExpression::toString() const
    {
        std::string str("\nList word expression: ");
        return str.append(m_word.raw);
    }
}