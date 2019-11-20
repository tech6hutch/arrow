#pragma once

#include "Expression.hpp"
#include "lexer/Token.hpp"
#include <memory>


namespace jasl {
    class HatHatStringExpression : public Expression
    {
      public:
        HatHatStringExpression();

        Type evaluate() const override;

        DecayType decayType() const override;

        HatHatStringExpression & withHatHatStringToken(Token hatHatStringToken);

        Token getHatHatStringToken() const;

        std::string toString() const override;

      private:
        Token m_hatHatStringToken;
    };
}