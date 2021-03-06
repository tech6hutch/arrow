/// (c) Ben Jones 2019 - present

//#include "StringToIntStatement.hpp"
//#include "expressions/evaluator/ExpressionEvaluator.hpp"
//#include "evaluator/StatementEvaluator.hpp"
//#include "parser/LanguageException.hpp"
//#include "utility/from_string.hpp"
//#include <utility>

namespace arrow {
    // TODO: convert to a builtin expression
    /*    
    StringToIntStatement::StringToIntStatement(long const lineNumber,
                                               ArrowStatement arrowStatement)
      : Statement(lineNumber)
      , m_arrowStatement(std::move(arrowStatement))
    {
    }

    std::string StringToIntStatement::toString() const
    {
        return m_arrowStatement.toString();
    }

    std::shared_ptr<StatementEvaluator> StringToIntStatement::getEvaluator() const
    {
        
        struct StringToIntStatementEvaluator : public StatementEvaluator
        {
            StringToIntStatementEvaluator(StringToIntStatement statement)
              : m_statement(std::move(statement))
            {
            }
            StatementResult evaluate(Environment & environment) const override
            {
                auto const expression = m_statement.getExpression();
                auto const type = expression->getEvaluator()->evaluate(environment);
                if(type.m_descriptor != TypeDescriptor::String) {
                    throw LanguageException("Not a string", m_statement.getLineNumber());
                }
                auto converted = from_string<real>(std::get<std::string>(type.m_variantType));
                auto identifier = m_statement.getIdentifier();
                environment.add(identifier.raw, {TypeDescriptor::Int, converted});
                return StatementResult::Continue;
            }
          private:
            StringToIntStatement m_statement;
        };
        return std::make_shared<StringToIntStatementEvaluator>(*this);
    }

    StringToIntStatement const & StringToIntStatement::withToken(Token token) const
    {
        m_arrowStatement.withToken(std::move(token));
        return *this;
    }

    Token StringToIntStatement::getToken() const
    {
        return m_arrowStatement.getToken();
    }

    std::shared_ptr<Expression> StringToIntStatement::getExpression() const
    {
        return m_arrowStatement.getExpression();
    }

    Token StringToIntStatement::getIdentifier() const
    {
        return m_arrowStatement.getIdentifier();
    }
    */
}