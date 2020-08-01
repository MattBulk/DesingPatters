#include "strategy.h"

void dynamicStrategyExample()
{
    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list({"foo", "bar", "baz"});
    std::cout << tp.oss.str() << std::endl;
}

void staticStrategyExample()
{
}