#ifndef MYAARRAY_H
#define MYARRAY_H

class MYArray {
public:
    MYArray(int size = 10);
    ~MYArray();

    bool operator ==(const MYArray &right) const;

    int& operator[](int index);

    MYArray& operator=(const MYArray &rhs);

private:
    int size;
    int* data;
};

#endif