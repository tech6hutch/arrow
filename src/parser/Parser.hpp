#pragma once

#include "expressions/Expression.hpp"
#include "statements/Statement.hpp"
#include "lexer/Token.hpp"
#include <vector>
#include <memory>

namespace jasl {
    
    class Parser
    {
      public:
        Parser(std::vector<Token> tokens);

        void parse();

        std::vector<std::shared_ptr<Statement>> getStatements() const;

      private:
        std::vector<Token> m_tokens;
        std::vector<Token>::iterator m_current;
        std::vector<std::shared_ptr<Statement>> m_statements;

        std::shared_ptr<Statement> buildStatement();
        bool notAtEnd() const;
        void advanceTokenIterator();
        Token currentToken() const;
        Token nextToken() const;

        std::shared_ptr<Expression> parseIdentifierExpression();
        std::shared_ptr<Expression> parseLiteralIntExpression();
        std::shared_ptr<Expression> parseLiteralRealExpression();
        std::shared_ptr<Expression> parseLiteralStringExpression();
        std::shared_ptr<Expression> parseHatStringExpression();
        std::shared_ptr<Expression> parseHatHatStringExpression();
        std::shared_ptr<Expression> parseQStringExpression();
        std::shared_ptr<Expression> parseQQStringExpression();
        std::shared_ptr<Expression> parseOperatorExpression();
        std::shared_ptr<Expression> parseBooleanExpression();
        std::shared_ptr<Expression> parseMathExpression();
        std::shared_ptr<Expression> parseGroupedExpression();
        std::shared_ptr<Expression> parseListExpression();
        std::shared_ptr<Expression> parseListWordExpression();

        /// Parse a part of ListExpression. Note, we need to distinguish
        /// between 'plain' words and identifiers, both of which
        /// are generic strings.
        std::shared_ptr<Expression> parseListExpressionType();
        std::shared_ptr<Expression> 
        parseExpressionCollectionExpression(bool const identifierOnly = false);

        std::shared_ptr<Expression> parseExpression(bool checkOperator = true);

        /// Parses statements of the form
        /// keyword expression -> identifier;
        /// For example
        /// int 5 -> a;
        std::shared_ptr<Statement> parseArrowStatement();

        /// Parses statements of the form
        /// keyword expression;
        /// For example
        /// prn "hello";
        std::shared_ptr<Statement> parseArrowlessStatement();

        /// Parses a repeat statement of the form
        /// repeat expression times { statement* }
        /// For example
        /// repeat 5 times { prn "hello"; }
        std::shared_ptr<Statement> parseRepeatStatement();

        /// Parses a while statement of the form
        /// while (expression) { statement* }
        std::shared_ptr<Statement> parseWhileStatement();

        /// Parses a for statement of the form
        /// for identifier in identifier { statement* }
        /// For example
        /// for i in N { prn i; }
        std::shared_ptr<Statement> parseForStatement();

        /// Parses an if statement of the form
        /// if (expression) { statement * } elseif (...) {} else {}
        /// Note the elseif and final else parts are optional
        std::shared_ptr<Statement> parseIfStatement();

        /// Parses a call statement of the 'returning form':
        /// call identifier(expression1,..,expressionN) -> identifier;
        /// OR of the 'arrow-less' (non-returning) form:
        /// call identifier(expression1,..,expressionN);
        std::shared_ptr<Statement> parseCallStatement();

        /// Parses a start statement (the program entry point):
        /// start { statement * }
        std::shared_ptr<Statement> parseStartStatement();

        /// Parses a function statement of the form
        /// fn:identifier identifier(expression1,..,expressionN) -> identifier
        /// {
        /// }
        std::shared_ptr<Statement> parseFunctionStatement();
    };
}
