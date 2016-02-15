#ifndef ENTITY_H
#define ENTITY_H

enum EEntityType {
	ET_NULL,
	ET_SPACESHIP, 
	ET_ASTEROID,
	ET_MISSILE
};

class CEntity {
public:
	CEntity(EEntityType type, double x, double y, int r, int g, int b, int a);
	virtual ~CEntity();

	virtual void Run(); 
	virtual void Draw(); 

	virtual void SetX(double x);
	virtual void SetY(double y);
	virtual void SetPosition(double x, double y);
	virtual void SetRGBA(int r, int g, int b, int a);
	virtual void SetDestroy(bool state);

	virtual double GetX() const;
	virtual double GetY() const;
	virtual int GetR() const;
	virtual int GetB() const;
	virtual int GetG() const;
	virtual int GetA() const;
	virtual bool ToDestroy() const;
	EEntityType GetType() const;
private:
	EEntityType m_type;	
	bool m_destroy; 
	int m_r; 
	int m_g;
	int m_b;
	int m_a;
	double m_x;
	double m_y;
};
 
#endif
