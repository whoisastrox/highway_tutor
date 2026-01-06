#ifndef VARCO_H
#define VARCO_H
class varco {
private:
	static int count;
	int id;
	double dist;

public:
	varco(double);
	double getDist() const;
	int getId() const;
};
#endif
