#include "strategy.h"

void dynamicStrategyExample()
{
    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list({"foo", "bar", "baz"});
    print("MARK\n", tp.oss.str());
}

void staticStrategyExample()
{
    TextProcessor2<HtmlListStrategy> tp;
    
    tp.append_list({"foo", "bar", "baz"});
    print("HTML\n", tp.toString());
}