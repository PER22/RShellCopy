#ifndef BASE_H
#define BASE_H
class Base{
	public:
//This class will serve as the inheritable base class for the composite tree.
		virtual int execute()=0;
		virtual void del()=0;
//execute() and del() will be a passthrough in the composite, and a direct execution in the leaves.
		Base(){}
};

#endif
