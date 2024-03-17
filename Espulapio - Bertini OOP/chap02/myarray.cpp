#include "myarray.h"

MYArray::MYArray(int size) {
    this->size = size;
    data = new int[size];
}

MYArray::~MYArray() {
    delete data;
}

bool MYArray::operator==(const MYArray &right) const {
    if(size != right.size)
        return(false);
    for (int i = 0; i < this->size; i++)
    {
        if(data[i] != right.data[i])
            return(false);
    }
    return(true);
}

int& MYArray::operator[](int index) {
    return(data[index]);
}

MYArray& MYArray::operator=(const MYArray& rhs) {
    this->size = rhs.size; 
    for (int i = 0; i < this->size; i++)
        this->data[i] = rhs.data[i];
}