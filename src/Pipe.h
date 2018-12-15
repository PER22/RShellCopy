#include "Base.h"
class Pipe : public Base{
    private:
    	Base* leftChild;
	Base* rightChild;
    public:
    	Pipe(Base*, Base*);
	~Pipe();
    	virtual int execute();
	virtual void del();
};
