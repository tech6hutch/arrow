#pragma once

#include "Statement.hpp"
#include "lexer/Token.hpp"
#include "expressions/Expression.hpp"
#include <memory>
#include <utility>

namespace jasl {
    
    /// Note, an ElseStatement can only be part
    /// of an IfStatement or ElseIfStatement
    class ElseStatement : public Statement
    {
      public:
        ElseStatement() : Statement() {}
        ElseStatement & withToken(Token token)
        {
            m_keywordToken = std::move(token);
            return *this;
        }
        void addBodyStatement(std::shared_ptr<Statement> bodyStatement)
        {
            m_bodyStatements.emplace_back(std::move(bodyStatement));
        }

        std::string toString() const override
        {
            std::string str("\nKeyword: ");
            str.append(m_keywordToken.raw);
            str.append("\nBegin body statements:\n");
            for(auto const & statement : m_bodyStatements) {
                str.append(statement->toString());
            }
            str.append("\nEnd body statements.");
            return str;
        }
        Token m_keywordToken; // the else keyword
        std::vector<std::shared_ptr<Statement>> m_bodyStatements;
    };

}