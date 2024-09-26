#ifndef ABSTRACT_WINDOW
#define ABSTRACT_WINDOW


class AWindow
{
public:
    AWindow() = default;
    virtual ~AWindow() = default;

    virtual void draw() {};
};


#endif // ABSTRACT_WINDOW
