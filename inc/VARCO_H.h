#ifndef VARCO_H
#define VARCO_H
class varco {
private:
	static int countVarc;
	int id;
	double dist;

public:
	varco(double);
	double getDist() const;
	int getId() const;
	~varco();
	varco(const varco&);

};
#endif
