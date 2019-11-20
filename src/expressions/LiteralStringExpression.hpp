#pragma once

#include "Expression.hpp"
#include "lexer/Token.hpp"
#include <memory>

namespace jasl {
    
    class LiteralStringExpression : public Expression
    {
      public:
        LiteralStringExpression();

        Type evaluate() const override;

        DecayType decayType() const override;

        LiteralStringExpression & withStringToken(Token stringToken);

        Token getStringToken() const;

        std::string toString() const override;

      private:
        Token m_stringToken;
    };

}