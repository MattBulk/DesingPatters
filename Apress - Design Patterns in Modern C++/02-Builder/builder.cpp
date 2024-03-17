#include "builder.h"
#include <vector>

// Simple and Fluent Builder
class HtmlElement
{
public:
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;
public:
    HtmlElement() { }
    HtmlElement(const std::string& name, const std::string& text) : name(name), text(text) { } 
    ~HtmlElement() { }

    std::string str(int indent = 0) const {
        std::string str = name + "\n";
        for (auto &&e : elements)
        {
            str.append(e.name + " " + e.text + "\n");
        }
        return(str);
    }
};

class HtmlBuilder
{
public:
    HtmlElement root;
public:

    HtmlBuilder(std::string rootName) {
        root.name = rootName;
    }
    ~HtmlBuilder() {}

    // void addChild(std::string childName, std::string childText) {
    //     HtmlElement e{ childName, childText};
    //     root.elements.emplace_back(e);
    // }

    // fluent interface lets chaining calls by reference. A pointer can be return as well
    HtmlBuilder& addChild(std::string childName, std::string childText) {
        HtmlElement e{ childName, childText};
        root.elements.emplace_back(e);
        return(*this);
    }

    std::string str() {
        return(root.str());
    }
};

void simpleBuilder() {
    HtmlBuilder builder{"ul"};
    builder.addChild("li", "hello");
    builder.addChild("li", "world").addChild("li", "space");

    print(builder.str(), "");
}

// Communicating Intent

class HtmlBuilder2;

#include <memory>

class HtmlElement2
{
public:
    std::string name;
    std::string text;
    std::vector<HtmlElement2> elements;
    const size_t indentSize = 2;

public:
    static std::unique_ptr<HtmlBuilder2> build(const std::string& rootName) {
        return std::make_unique<HtmlBuilder2>(rootName);
    }

    std::string str(int indent = 0) const {
        std::string str = name + "\n";
        for (auto &&e : elements)
        {
            str.append(e.name + " " + e.text + "\n");
        }
        return(str);
    }
    
    HtmlElement2() { }

    ~HtmlElement2() { }

    HtmlElement2(const std::string& name, const std::string& text) : name(name), text(text) { }     
};

class HtmlBuilder2
{
public:
    HtmlElement2 root;
    
public:
    HtmlBuilder2(std::string rootName) {
        root.name = rootName;
    }
    ~HtmlBuilder2() {}

    operator HtmlElement2() const {
        return root; 
    }
    // void addChild(std::string childName, std::string childText) {
    //     HtmlElement e{ childName, childText};
    //     root.elements.emplace_back(e);
    // }

    // fluent interface lets chaining calls by reference. A pointer can be return as well
    HtmlBuilder2& addChild(std::string childName, std::string childText) {
        HtmlElement2 e{childName, childText};
        root.elements.emplace_back(e);
        return(*this);
    }

    std::string str(int indent = 0) const {
        std::string str = root.name + "\n";
        for (auto &&e : root.elements)
        {
            str.append(e.name + " " + e.text + "\n");
        }
        return(str);
    }
};

void communicatingIntent() {
    auto builder = HtmlElement2::build("ul");
    builder->addChild("li", "hello");
    builder->addChild("li", "world");
    print(builder->str(), " builder");

    HtmlElement2 e = HtmlElement2::build("ul")->addChild("li", "hello");
    print(e.str(), " element");
}

// Groovy-style builder

#include <ostream>
#include <utility>

class Tag
{
public:
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;
public:
    Tag(/* args */) {}
    ~Tag() {}

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
        // implementation
        os << tag.name << ": ";
        std::vector<Tag> chs = tag.children;
        os << "children: " << chs.size();
        
        return os;
    }
protected:
    Tag(const std::string& name, const std::string& text) : name{name}, text{text} { }

    Tag(const std::string& name, const std::vector<Tag>& children) : name{name}, children{children} { }

};

#include <initializer_list>

class P : public Tag
{
private:
    /* data */
public:
    P(const std::string& text) : Tag{"p", text} { }

    P(const std::initializer_list<Tag>& children) : Tag{"p", children} { }

    ~P() {}
};

class IMG : public Tag
{
private:
    /* data */
public:
    IMG(const std::string& url) : Tag{"img", ""} {
        std::pair<std::string, std::string> pair("src", url); 
        attributes.emplace_back(pair);
    }
    ~IMG() {}
};

void groovyExample() {
    std::cout << P {
        IMG {"http://voidexample.png"},
        IMG {"http://fillexample.png"}
    }
    << std::endl;
}

// Composite builder

PersonAddressBuilder PersonBuilderBase::lives() const {
    return(PersonAddressBuilder(person));

}

PersonJobBuilder PersonBuilderBase::works() const {
    return(PersonJobBuilder(person));

}

void compositeExample() {

    // to do

}