#ifndef STRATEGY_h
#define STRATEGY_H

#include "../commons.h"
#include <sstream>

enum class OutputFormat
{
    markdown,
    html
};

class ListStrategy
{
private:
    /* data */
public:
    ListStrategy(/* args */) {}
    ~ListStrategy() {}

    virtual void start(std::ostringstream &oss){};

    virtual void add_list_item(std::ostringstream &oss, const std::string &item){};

    virtual void end(std::ostringstream &oss){};
};



class HtmlListStrategy : public ListStrategy
{
private:
    /* data */
public:
    HtmlListStrategy(/* args */) {}
    ~HtmlListStrategy() {}

    void start(std::ostringstream &oss) override
    {
        oss << "<ul>\n";
    }
    void end(std::ostringstream &oss) override
    {
        oss << "</ul>\n";
    }
    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << "<li>" << item << "</li>\n";
    }
};

class MarkdownListStrategy : public ListStrategy
{
private:
    /* data */
public:
    MarkdownListStrategy(/* args */) {}
    ~MarkdownListStrategy() {}

    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << " * " << item << std::endl;
    }
};


class TextProcessor
{
public:
    /* data */
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;

public:
    TextProcessor(/* args */) {}
    ~TextProcessor() {}

    void append_list(const std::vector<std::string> items)
    {
        list_strategy->start(oss);
        for (auto &item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat format)
    {
        switch (format)
        {
        case OutputFormat::markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        }
    }
    
};

void dynamicStrategyExample();

template<typename LS>
class TextProcessor2
{
private:
    /* data */
    std::ostringstream oss;
    LS list_strategy;

public:
    TextProcessor2() {
        
    }
    ~TextProcessor2() {}

    void append_list(const std::vector<std::string> items)
    {
        list_strategy.start(oss);
        for (auto &item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }

    std::string toString() const {
        return oss.str();
    }
    
};

void staticStrategyExample();

#endif