#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include "func.h"

int writeinfile(DB_item Newitem,const char * path)
{
	FILE* fAdd = fopen(path,"ab");
	if (fAdd == NULL) return 1;
	fwrite(&Newitem,sizeof(DB_item),1,fAdd);
	fclose(fAdd);
	return 0;

}
int rmfromfile(int rm_id,const char * path)
{
	DB_item Rmitem;
	FILE* fRm = fopen(path,"rb+");
	if (fRm == NULL) return 1;
	if (fseek(fRm, (rm_id) * sizeof(DB_item), SEEK_SET)==0) {
		while (fread(&Rmitem, sizeof(DB_item), 1, fRm)){
			fseek(fRm, (rm_id-1) * sizeof(DB_item), SEEK_SET);
			fwrite(&Rmitem, sizeof(DB_item), 1, fRm);
			rm_id++;
			fseek(fRm, (rm_id)*sizeof(DB_item), SEEK_SET);
		}
		truncate(path,(rm_id-1)*sizeof(DB_item));
	}
	
	fclose(fRm);
	return 0;
}

int chinfile(DB_item Chitem,int ch_id,const char * path)
{
	FILE* fChange = fopen(path,"rb+");
	if (fChange == NULL) return 1;
	fseek(fChange, (ch_id-1) * sizeof(DB_item), SEEK_SET);
	fwrite(&Chitem, sizeof(DB_item), 1, fChange);
	fclose(fChange);
	return 0;
}
