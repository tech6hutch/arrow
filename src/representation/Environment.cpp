/// (c) Ben Jones 2019 - present

#include "Environment.hpp"
#include "parser/LanguageException.hpp"

namespace arrow {

    namespace {
        template <typename T>
        void updateArray(VariantType & vt, Type element, int const index)
        {
            auto & casted = std::get<std::vector<T>>(vt);
            /*
            if(index >= casted.size()) {
                throw LanguageException("Index out of range", lineNumber);
            }*/
            if constexpr(std::is_same_v<T, Type>) {
                casted[index].m_variantType.swap(element.m_variantType);
            } else {
                auto const val = std::get<T>(element.m_variantType);
                casted[index] = val;
            }
        }

        template <typename T>
        std::pair<bool, std::vector<T>> tryErase(VariantType vt,
                                                 int const index)
        {
            try {
                auto casted = std::get<std::vector<T>>(vt);
                /*
                if(index >= casted.size()) {
                    throw LanguageException("Index out of range", lineNumber);
                }*/
                casted.erase(std::begin(casted) + index);
                return {true, casted};
            } catch (...) {
                return {false, std::vector<T>()};
            }
        }
    }

    std::deque<Type> Environment::m_returnStack;

    Environment::Environment(std::ostream & ostr)
      : m_ostream(ostr)
      , m_environmentStack{}
    {
        pushEnvironmentLayer();
    }

    std::ostream & Environment::getOutputStream()
    {
        return m_ostream;
    }

    Environment::EnvironmentMap::iterator
    Environment::findAndRetrieveCached(std::string identifier) const
    {
        for (auto & layer : m_environmentStack) {
            auto found = layer.find(identifier);
            if(found != std::end(layer)) {
                return found;
            }
        }
        return EnvironmentMap::iterator();
    }

    Type Environment::get(std::string identifier) const
    {
        auto found = findAndRetrieveCached(identifier);
        if(found == EnvironmentMap::iterator()) { return {TypeDescriptor::None, false}; }
        return found->second;
    }

    void Environment::add(std::string identifier, Type const type)
    {
        auto found = findAndRetrieveCached(identifier);
        if(found != EnvironmentMap::iterator()) {
            // Remove original instance of value
            found->second.m_variantType.swap(type.m_variantType);
            return;
        }
        // Add brand new instance
        m_environmentStack[0].emplace(identifier, type);
    }
    bool Environment::has(std::string identifier) const
    {
        auto found = findAndRetrieveCached(identifier);
        return found != EnvironmentMap::iterator();
    }
    void Environment::remove(std::string identifier) const
    {
        for (auto & layer : m_environmentStack) {
            auto found = layer.find(identifier);
            if(found != std::end(layer)) {
                layer.erase(found);
                return;
            }
        }
    }

    void Environment::pushBackContainerElement(std::string identifier, Type const type)
    {
        auto found = findAndRetrieveCached(identifier);
        
        if(found->second.m_descriptor == TypeDescriptor::Ints) {
            auto & casted = std::get<std::vector<int64_t>>(found->second.m_variantType);
            auto tval = std::get<int64_t>(type.m_variantType);
            casted.push_back(tval);
        } else if(found->second.m_descriptor == TypeDescriptor::Reals) {
            auto & casted = std::get<std::vector<real>>(found->second.m_variantType);
            auto tval = std::get<real>(type.m_variantType);
            casted.push_back(tval);
        } else if(found->second.m_descriptor == TypeDescriptor::Strings) {
            auto & casted = std::get<std::vector<std::string>>(found->second.m_variantType);
            auto tval = std::get<std::string>(type.m_variantType);
            casted.push_back(tval);
        } else if(found->second.m_descriptor == TypeDescriptor::Bytes) {
            auto & casted = std::get<std::vector<char>>(found->second.m_variantType);
            auto tval = std::get<char>(type.m_variantType);
            casted.push_back(tval);
        } else if(found->second.m_descriptor == TypeDescriptor::Bools) {
            auto & casted = std::get<std::vector<bool>>(found->second.m_variantType);
            auto tval = std::get<bool>(type.m_variantType);
            casted.push_back(tval);
        } else if(found->second.m_descriptor == TypeDescriptor::List) {
            auto & casted = std::get<std::vector<Type>>(found->second.m_variantType);
            casted.push_back(type);
        } 
    }

    void Environment::setElementInContainer(std::string identifier,
                                      int const index,
                                      Type const type)
    {
        auto found = findAndRetrieveCached(identifier);
        try {
            if(type.m_descriptor == TypeDescriptor::Int) {
                updateArray<int64_t>(found->second.m_variantType, type, index);
                return;
            } else if(type.m_descriptor == TypeDescriptor::Real) {
                updateArray<real>(found->second.m_variantType, type, index);
                return;
            } else if(type.m_descriptor == TypeDescriptor::String) {
                updateArray<std::string>(found->second.m_variantType, type, index);
                return;
            } else if(type.m_descriptor == TypeDescriptor::Byte) {
                updateArray<char>(found->second.m_variantType, type, index);
                return;
            } else if(type.m_descriptor == TypeDescriptor::Bool) {
                updateArray<bool>(found->second.m_variantType, type, index);
                return;
            } 
        } catch (...) {
            // if casting threw, it must be because of bad type conversion
            // meaning we can instead try Type as the list element type.
        }
        updateArray<Type>(found->second.m_variantType, type, index);
    }

    void Environment::eraseElementInContainer(std::string identifier,
                                        int const index)
    {
        auto found = findAndRetrieveCached(identifier);
        {
            auto result = tryErase<int64_t>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
        {
            auto result = tryErase<real>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
        {
            auto result = tryErase<bool>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
        {
            auto result = tryErase<char>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
        {
            auto result = tryErase<std::string>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
        {
            auto result = tryErase<Type>(found->second.m_variantType, index);
            if(result.first) {
                found->second.m_variantType = result.second;
                return;
            }
        }
    }


    void Environment::pushEnvironmentLayer()
    {
        m_environmentStack.emplace_front(EnvironmentMap());
    }
    void Environment::popEnvironmentLayer()
    {
        m_environmentStack.pop_front();
    }

    void Environment::pushReturnValue(Type t)
    {
        m_returnStack.push_front(std::move(t));
    }
    Type Environment::getAndPopReturnValue()
    {
        auto t = m_returnStack[0];
        m_returnStack.pop_front();
        return t;
    }
    void Environment::pushProgramArgument(Type arg)
    {
        m_programArguments.push_back(std::move(arg));
    }

    Type Environment::getProgramArgument(int64_t const index) const
    {
        return m_programArguments[index];
    }
}