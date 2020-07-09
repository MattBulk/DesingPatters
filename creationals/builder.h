#ifndef BUILDER_H
#define BUILDER_H


class Builder
{
private:
    int t;
public:
    Builder(int value) : t(value) { }
    ~Builder() {}

    int getTemperature() {
        return(t);
    }
};


#endif