/*******************************************************************************
 *  cpp2csrc.c                                                                 *
 *  Author: Ariel                                                              *
 *  Reviewer:                                                                  *
 * ****************************************************************************/
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */

/*
template<class T>
inline T maxFunc(const T &t1, const T &t2)
{
	return ((t1 > t2)? t1: t2);
}*/

#define maxFunc(t1, t2) ((t1 > t2) ? t1 : t2)

typedef void (*vfunc)(void*);

/******************** Public Transport ****************************************/

/*
class Public_Transport
{
public:
	Public_Transport() : m_license_plate(++s_count) 
	{ 
		cout << "Public_Transport::Ctor()" << m_license_plate << endl; 
	}

	virtual ~Public_Transport() //dest
	{ 
		--s_count; 
		cout << "Public_Transport::Dtor()" << m_license_plate  << endl; 
	}

	Public_Transport(const Public_Transport &other) : m_license_plate(++s_count) 
	{ 
		cout << "Public_Transport::CCtor() " << m_license_plate << endl; 
	}

	virtual void Display() //virtual 
	{ 
		cout << "Public_Transport::Display(): " << m_license_plate << endl; 
	}

	static void PrintCount() { cout << "s_count: " << s_count << endl;} 
protected:
	int GetID() { return m_license_plate; }

private:
	static int s_count;
	int m_license_plate;
	Public_Transport &operator=(const Public_Transport &); 
};
*/

typedef struct 
{
    vfunc* vtable;
    int m_licencse_plate;
}Public_Transport;

int public_transport_s_count;

/* Method Declarations */

void PublicTransportCtor(Public_Transport* const this);
void PublicTransportDtor(Public_Transport* const this);
void PublicTransportCctor(Public_Transport* const this, 
                                                 Public_Transport* const other);
void PublicTransportDisplay(Public_Transport* const this);
void PrintCount(int pt_s_count);
int PublicTransportGetID(Public_Transport* const this);

vfunc pt_vtable[3] = {(vfunc)PublicTransportCtor, (vfunc)PublicTransportDtor, 
                      (vfunc)PublicTransportDisplay};

/* Method Definitions */

void PublicTransportCtor(Public_Transport* const this)
{
    ++public_transport_s_count;
    this->m_licencse_plate = public_transport_s_count;

    this->vtable = pt_vtable;

    printf("Public_Transport::Ctor()%d\n", this->m_licencse_plate);
}

void PublicTransportDtor(Public_Transport* const this)
{
    --public_transport_s_count;
    printf("Public_Transport::Dtor()%d\n", this->m_licencse_plate);
    this->m_licencse_plate = public_transport_s_count;
}

void PublicTransportCctor(Public_Transport* const this, Public_Transport* const other)
{
    this->vtable = pt_vtable;
    this->m_licencse_plate = other->m_licencse_plate;
    this->m_licencse_plate = ++public_transport_s_count;

    printf("Public_Transport::CCtor() %d\n", this->m_licencse_plate);
}

void PublicTransportDisplay(Public_Transport* const this)
{
    printf("Public_Transport::Display(): %d\n", this->m_licencse_plate);
}

void PrintCount(int pt_s_count)
{
    printf("s_count: %d\n", pt_s_count);
}

int PublicTransportGetID(Public_Transport* const this)
{
    return this->m_licencse_plate;
}

/************* End Public Transport *******************************************/

/************* Minibus ********************************************************/

/*
class Minibus: public Public_Transport
{
public:
	Minibus()
	: m_numSeats(20)
	{ 
		cout << "Minibus::Ctor()" << endl; 
	}
	Minibus(const Minibus &other )
	: Public_Transport(other),
	  m_numSeats(other.m_numSeats)
	{ 
		cout << "Minibus::CCtor()" << endl; 
	}
   ~Minibus() { cout << "Minibus::dtor()" << endl; }
	void Display() 
	{ 
		cout << "Minibus::Display() ID:"<<GetID();
		cout << " num seats:" << m_numSeats << endl; 
	}
	virtual void Wash() { cout << "Minibus::Wash() ID:"<<GetID() << endl; }

private:
	int m_numSeats;
};
*/

typedef struct
{
    Public_Transport public_transport;
    int m_mb_numseats;
}Minibus;

/* Method declarations */

void MinibusCtor(Minibus* const this);
void MinibusDtor(Minibus* const this);
void MinibusCctor(Minibus* const this, Minibus* const other);
void MinibusDisplay(Minibus* const this);
void MinibusWash(Minibus* const this);

vfunc mb_vtable[4] = {(vfunc)MinibusCtor, (vfunc)MinibusDtor, 
                      (vfunc)MinibusDisplay, (vfunc)MinibusWash};

/* Method definitions */

void MinibusCtor(Minibus* const this)
{
    PublicTransportCtor(&(this->public_transport));
    this->public_transport.vtable = mb_vtable;
    this->m_mb_numseats = 20;

    printf("Minibus::Ctor()\n");
}

void MinibusDtor(Minibus* const this)
{
    printf("Minibus::dtor()\n");
    PublicTransportDtor(&(this->public_transport));    
}

void MinibusCctor(Minibus* const this, Minibus* const other)
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->public_transport.vtable = mb_vtable;
    this->m_mb_numseats = other->m_mb_numseats;
    printf("Minibus::CCtor()\n");
}

void MinibusDisplay(Minibus* const this)
{
    printf("Minibus::Display() ID:%d", 
                               PublicTransportGetID(&(this->public_transport)));
    printf(" num seats:%d\n", this->m_mb_numseats);
}

void MinibusWash(Minibus* const this)
{
    printf("Minibus::Wash() ID:%d\n", 
                               PublicTransportGetID(&(this->public_transport)));
}

/************** End Minibus ***************************************************/

/************** Taxi **********************************************************/

/*
class Taxi: public Public_Transport
{
public:
	Taxi() { cout << "Taxi::Ctor()" << endl; }
	Taxi(const Taxi &other ): Public_Transport(other) { cout << "Taxi::CCtor()" << endl; }
   ~Taxi() { cout << "Taxi::dtor()" << endl; }
	void Display() { cout << "Taxi::Display() ID:"<<GetID()<< endl; }

private:
	int m_numSeats;
};
*/

typedef struct
{
    Public_Transport public_transport;
    int m_tx_numSeats;
}Taxi;

/* Method Declarations */

void TaxiCtor(Taxi* const this);
void TaxiDtor(Taxi* const this);
void TaxiCctor(Taxi* const this, Taxi* const other);
void TaxiDisplay(Taxi* const this);

vfunc tx_vtable[3] = {(vfunc)TaxiCtor, (vfunc)TaxiDtor, (vfunc)TaxiDisplay};

/* Method definitions */

void TaxiCtor(Taxi* const this)
{
    PublicTransportCtor(&(this->public_transport));
    this->public_transport.vtable = tx_vtable;

    printf("Taxi::Ctor()\n");
}

void TaxiDtor(Taxi* const this)
{
    printf("Taxi::dtor()\n");
    PublicTransportDtor(&(this->public_transport));    
}

void TaxiCctor(Taxi* const this, Taxi* const other)
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->public_transport.vtable = tx_vtable;
    printf("Taxi::CCtor()\n");
}

void TaxiDisplay(Taxi* const this)
{
    printf("Taxi::Display() ID:%d\n", 
                               PublicTransportGetID(&(this->public_transport)));
}


/************* End Taxi *******************************************************/

/************* Special Taxi ***************************************************/

/*
class Special_Taxi : public Taxi
{
public:
	Special_Taxi() { cout << "Special_Taxi::Ctor()" << endl; }
	Special_Taxi(const Special_Taxi &other): Taxi(other) 
	{ 
		cout << "Special_Taxi::CCtor()" << endl; 
	}
   ~Special_Taxi() { cout << "Special_Taxi::dtor()" << endl; }
	void Display() { cout << "Special_Taxi::Display() ID:"<<GetID()<<endl;}
};*/

typedef struct
{
    Taxi taxi;
}Special_Taxi;

/* Method declarations */

void SpecialTaxiCtor(Special_Taxi* const this);
void SpecialTaxiDtor(Special_Taxi* const this);
void SpecialTaxiCctor(Special_Taxi* const this, Special_Taxi* const other);
void SpecialTaxiDisplay(Special_Taxi* const this);

vfunc sptx_vtable[3] = {(vfunc)SpecialTaxiCtor, (vfunc)SpecialTaxiDtor, 
                        (vfunc)SpecialTaxiDisplay};

/* Method definitions */

void SpecialTaxiCtor(Special_Taxi* const this)
{
    TaxiCtor(&(this->taxi));
    this->taxi.public_transport.vtable = sptx_vtable;
    printf("Special_Taxi::Ctor()\n");
}

void SpecialTaxiDtor(Special_Taxi* const this)
{
    printf("Special_Taxi::dtor()\n");
    TaxiDtor(&(this->taxi));
}

void SpecialTaxiCctor(Special_Taxi* const this, Special_Taxi* const other)
{
    TaxiCctor(&(this->taxi), &(other->taxi));
    printf("Special_Taxi::CCtor()\n");
}

void SpecialTaxiDisplay(Special_Taxi* const this)
{
    printf("Special_Taxi::Display() ID:%d\n", 
                          PublicTransportGetID(&(this->taxi.public_transport)));
}

/************* End Special Taxi ***********************************************/

/************* Public_Convoy **************************************************/
/*
class Public_Convoy: public Public_Transport
{
public:
	Public_Convoy() 
	: m_pt1(new Minibus()), m_pt2(new Taxi())
	{  }

	~Public_Convoy() 
	{ 
		delete m_pt1; 
		delete m_pt2;
	}

	Public_Convoy(const Public_Convoy& _other) : 
	                    Public_Transport(_other),
						m_pt1(new Minibus(*static_cast<Minibus*>(_other.m_pt1))),
						m_pt2(new Taxi(*static_cast<Taxi*>(_other.m_pt2))),
						m_m(_other.m_m),
						m_t(_other.m_t)
	{}	

	void Display()
	{
		m_pt1->Display();
		m_pt2->Display();
		m_m.Display();
		m_t.Display();
	}

private:
  Public_Transport *m_pt1;
  Public_Transport *m_pt2;
  Minibus m_m;
  Taxi m_t;
};*/

typedef struct 
{
    Public_Transport public_transport;
    Public_Transport* m_pt1;
    Public_Transport* m_pt2;
    Minibus m_m;
    Taxi m_t;    
}Public_Convoy;

/* Method declarations */

void PublicConvoyCtor(Public_Convoy* const this);
void PublicConvoyCctor(Public_Convoy* const this, Public_Convoy* const other);
void PublicConvoyDisplay(Public_Convoy* const this);
void PublicConvoyDtor(Public_Convoy* const this);

vfunc pc_vtable[3] = {(vfunc)PublicConvoyCtor, (vfunc)PublicConvoyDtor, 
                      (vfunc)PublicConvoyDisplay};

/* Method definitions */

void PublicConvoyCtor(Public_Convoy* const this)
{
    PublicTransportCtor(&(this->public_transport));
    this->public_transport.vtable = pc_vtable;

    this->m_pt1 = (Minibus*)malloc(sizeof(Minibus));
    MinibusCtor(this->m_pt1);

    this->m_pt2 = (Taxi*)malloc(sizeof(Taxi));
    TaxiCtor(this->m_pt2);

    MinibusCtor(&(this->m_m));
    TaxiCtor(&(this->m_t));
}

void PublicConvoyDtor(Public_Convoy* const this)
{
    this->m_pt1->vtable[1](this->m_pt1);
    free(this->m_pt1);

    this->m_pt2->vtable[1](this->m_pt2);
    free(this->m_pt2);

    TaxiDtor(&(this->m_t));
    MinibusDtor(&(this->m_m));

    PublicTransportDtor(&(this->public_transport));
}

void PublicConvoyCctor(Public_Convoy* const this, Public_Convoy* const other)
{
    PublicTransportCctor(&(this->public_transport), &(other->public_transport));
    this->public_transport.vtable = pc_vtable;
    
    Minibus* newMB = (Minibus*)malloc(sizeof(Minibus));
    this->m_pt1 = (Public_Transport*)newMB;
    MinibusCctor((Minibus*)(this->m_pt1), (Minibus*)(other->m_pt1));

    Taxi* newTX = (Taxi*)malloc(sizeof(Taxi));
    this->m_pt2 = (Public_Transport*)newTX;
    TaxiCctor((Taxi*)(this->m_pt2), (Taxi*)(other->m_pt2));

    MinibusCctor(&(this->m_m), &(other->m_m));
    TaxiCctor(&(this->m_t), &(other->m_t));
}

void PublicConvoyDisplay(Public_Convoy* const this)
{
    this->m_pt1->vtable[2](this->m_pt1);
    this->m_pt2->vtable[2](this->m_pt2);
    this->m_m.public_transport.vtable[2](&(this->m_m));
    this->m_t.public_transport.vtable[2](&(this->m_t));
}




/************* End Public Convoy **********************************************/

/************* Global functions ***********************************************/

void PrintInfo(Public_Transport* pt);
void PTPrintInfo(void);
void PT1PrintInfo(int i, Public_Transport* pt);
void GlobalTaxiDisplay(Taxi s);

/*
void PrintInfo(Public_Transport &a) { a.Display(); }
*/

void PrintInfo(Public_Transport* pt)
{
    (pt->vtable[2])(pt);
}

/*
void PrintInfo() { Public_Transport::PrintCount(); }
*/

void PTPrintInfo(void)
{
    PrintCount(public_transport_s_count);
}

/*
Public_Transport PrintInfo(int i)
{
	Minibus ret;
	cout<<"PrintInfo(int i)"<<endl;
	ret.Display();
	return ret;
}
*/

void PT1PrintInfo(int i, Public_Transport* pt)
{
    Minibus ret;
    MinibusCtor(&ret);
    printf("PrintInfo(int i)\n");
    MinibusDisplay(&ret);
    PublicTransportCctor(pt, (Public_Transport*)&ret);
    MinibusDtor(&ret);
    (void)i;
}

/*
void TaxiDisplay(Taxi s) { s.Display(); }
*/

void GlobalTaxiDisplay(Taxi s)
{
    Taxi tmp;
    TaxiCctor(&tmp, &s);
    TaxiDisplay(&tmp);
    TaxiDtor(&tmp);
}


/************* End Global functions *******************************************/

int main(void)
{
    Minibus m;
    MinibusCtor(&m);

    PrintInfo((Public_Transport*)&m);
    PT1PrintInfo(3, (Public_Transport*)&m);
    PublicTransportDisplay((Public_Transport*)&m);
    PublicTransportDtor((Public_Transport*)&m);

    Minibus* arr_m1 = (Minibus*)malloc(sizeof(Minibus));
    MinibusCtor(arr_m1);

    Taxi* arr_t1 = (Taxi*)malloc(sizeof(Taxi));
    TaxiCtor(arr_t1);

    Minibus* arr_m2 = (Minibus*)malloc(sizeof(Minibus));
    MinibusCtor(arr_m2);

    Public_Transport* array[] = {(Public_Transport*)arr_m1, 
                                 (Public_Transport*)arr_t1, 
                                 (Public_Transport*)arr_m2};

    for(size_t i = 0; i < 3; ++i)
    {
        array[i]->vtable[2](array[i]);
    }

    for(size_t i = 0; i < 3; ++i)
    {
        array[i]->vtable[1](array[i]);
        free(array[i]);
    }

    Public_Transport arr2_p1, arr2_p2, arr2_p3;
    
    Minibus arr2_m1;
    MinibusCtor(&arr2_m1);
    PublicTransportCctor(&arr2_p1, (Public_Transport*)&arr2_m1);
    MinibusDtor(&arr2_m1);

    Taxi arr2_t1;
    TaxiCtor(&arr2_t1);
    PublicTransportCctor(&arr2_p2, (Public_Transport*)&arr2_t1);
    TaxiDtor(&arr2_t1);

    PublicTransportCtor(&arr2_p3);

    Public_Transport arr2[] = {arr2_p1, arr2_p2, arr2_p3};

    for(size_t i = 0; i < 3; ++i)
    {
        arr2[i].vtable[2](&arr2[i]);
    }

    PrintCount(public_transport_s_count);

    Minibus m2;
    MinibusCtor(&m2);

    PrintCount(public_transport_s_count);

    Minibus arr3_m1, arr3_m2, arr3_m3, arr3_m4;
    Minibus arr3[4] = {arr3_m1, arr3_m2, arr3_m3, arr3_m4};
    
    for(size_t i = 0; i < 4; ++i)
    {
        MinibusCtor(&arr3[i]);
    }

    Taxi arr4_t1, arr4_t2, arr4_t3, arr4_t4;
    Taxi tmpArr4[4] = {arr4_t1, arr4_t2, arr4_t3, arr4_t4};
    Taxi* arr4 = (Taxi*)malloc(sizeof(Taxi) * 4);

    for(size_t i = 0; i < 4; ++i)
    {
        TaxiCtor(&tmpArr4[i]);
        arr4[i] = tmpArr4[i];
    }

    for(size_t i = 0; i < 4; ++i)
    {
        TaxiDtor(&arr4[4 - i  -1]);
    }
    free(arr4);

    printf("%d\n", maxFunc(1, 2));

    Special_Taxi st;
    SpecialTaxiCtor(&st);
    GlobalTaxiDisplay(st.taxi);
    
    Public_Convoy* ts1 = (Public_Convoy*)malloc(sizeof(Public_Convoy));
    PublicConvoyCtor(ts1);

    Public_Convoy* ts2 = (Public_Convoy*)malloc(sizeof(Public_Convoy));
    PublicConvoyCctor(ts2, ts1);

    PublicConvoyDisplay(ts1);
    PublicConvoyDisplay(ts2);

    PublicConvoyDtor(ts1);

    PublicConvoyDisplay(ts2);
    PublicConvoyDtor(ts2);
    
    SpecialTaxiDtor(&st);
    for(size_t i = 0; i < 4; ++i)
    {
        MinibusDtor(&arr3[4 - i - 1]);
    }
    
    MinibusDtor(&m2);
    PublicTransportDtor(&arr2_p3);
    PublicTransportDtor(&arr2_p2);
    PublicTransportDtor(&arr2_p1);
    MinibusDtor(&m);
    return 0;
}