#ifndef SVINCOLO_H
#define SVINCOLO_H
class svincolo {
private:
	static int count;
	int id;
	double dist;

public:
	svincolo(double);
	double getDist() const;
	int getId() const;
};
#endif
