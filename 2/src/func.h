struct DateRec
{
	int day;
	int month;
	int year;
};

struct DB_item
{
	DateRec b_date;
	char name[10];
	char addres[13];
	int count_bed;
				
};
int writeinfile(DB_item Newitem,const char * path);
int rmfromfile(int rm_id,const char * path);
int chinfile(DB_item Chitem,int ch_id,const char * path);

void print_dbhead(int n);
int clr_area(int y, int x);
void Print_dbitem(DB_item x, int y);
void Print_alldb();
DB_item create_dbitem();
int Select_item(int n);
