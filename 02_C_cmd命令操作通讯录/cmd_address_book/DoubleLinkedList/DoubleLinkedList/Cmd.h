#pragma once

//12:30
typedef void (*pfun)();

struct CMD_MAP
{
	char *m_szcmd;
	pfun m_pfun;
	
};

void Create();
void Add();
void Insert();
void Delete();
void Clearn();
void Modify();
void Find();
void Show();
void Help();
void Exit();

void Finally();