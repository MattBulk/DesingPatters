// 4.2 Open Close C example not close
enum ShapeType { circle, square };

struct PointC {
    int x;
    int y;
};

struct ShapeC
{
    /* data */
    ShapeType itsType;
};

struct CircleC
{
    /* data */
    ShapeType itsType;
    double itsRadius;
    PointC itsCenter;
};

struct SquareC
{
    /* data */
    ShapeType itsType;
    double itsSide;
    PointC itsTopLeft;
};

void drawSquare(struct SquareC*)
{
    
}

void drawCircle(struct CircleC*) {

}

typedef struct ShapeC *ShapePointer;

// this code isn't close because the switch needs to be updated whenever a new shape is added.
void drawAllShapesC(ShapePointer list[], int n) {  
    for (int i = 0; i < n; i++)
    {
        /* code */
        struct ShapeC *s = list[i];
        switch (s->itsType)
        {
        case square:
            drawSquare((struct SquareC*)s);
            break;
        
        default:
            drawCircle((struct CircleC*)s);
            break;
        }
    } 
}

// following a C++ example to solve it

class Shape {
public:
    virtual void draw() const = 0;
};

class Square : public Shape {
public:
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    virtual void draw() const = 0;
};

void DrawAllShape(Shape* list[], int size) {
    for (int i = 0; i < size; i++)
    {
        /* code */
        list[i]->draw();
    }
    
}
