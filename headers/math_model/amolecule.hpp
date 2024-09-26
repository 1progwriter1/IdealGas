#ifndef ABSTRACT_MOLECULE
#define ABSTRACT_MOLECULE


class AMolecule
{
public:
    AMolecule() = default;
    virtual ~AMolecule() = default;

    virtual void draw();
    virtual void move();
};


#endif // ABSTRACT_MOLECULE
