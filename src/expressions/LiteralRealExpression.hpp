#pragma once

#include "Expression.hpp"
#include "lexer/Token.hpp"
#include <memory>
#include <string>

namespace jasl {
    
    class LiteralRealExpression : public Expression
    {
      public:
        LiteralRealExpression();

        Type evaluate() const override;

        DecayType decayType() const override;

        LiteralRealExpression & withRealToken(Token realToken);

        Token getRealToken() const;

        std::string toString() const override;

      private:
        Token m_realToken;
    };

}