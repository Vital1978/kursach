#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct TRoute
  { 
    char Name[60]; //����� � �������� ��������
    int Count;     //���������� ������ ���������� �� ��������
    float Len;     //������������� ��������, ��
  };
  
int Load(TRoute*, char*, int); //���� �� ���������� ����� � ������
int Add(TRoute*, int);  //���������� ����� ��������� � ����� �������
int Show(TRoute*, int); //�������� ���� ��������� �������
int Save(TRoute*, char*, int); //����� ��������� ������� � ��������� ����
int Edit(TRoute*, int);  //������������� ����� ���������� ��������
int Del1(TRoute*, int);  //�������� ���������� ��������
int Del2(TRoute*, int); //�������� ��������� �� ��������� �������
int Del3(TRoute*, int); //�������� ���������, ������� �� ����������
int Sort(TRoute*, int); //���������� ������� �� ��������� ����
int Menu(); //����� ���� �� �����
void Line(); //����� �������������� �����
void Data(TRoute, int); //����� ������ ������� � �������
void Head(); //����� ���������� �������� �������
int IsEmpty(int); //������ ����
char * GetFileName(); //����� ����� ����� � �������

//����������� �������� ����

int Menu()
{
  int v;
  system("cls");
  cout<<"************ �������� ���������� ���������� ************"<<endl;
  for(int i=0;i<80;i++)cout<<"=";
  cout<<endl;
  cout<<"1-������� 2-�������� 3-�������� 4-��������� 5-��������� 6-�������"<<endl;
  cout<<"7-������� �� ������� 8-���������� 9-������� �� ���������� 0-�����"<<endl;
  for(int i=0;i<80;i++)cout<<"=";
  cout<<"\n������� ����� ������� -> ";
  cin>>v;
  cout<<endl;
  if(v<0 || v>10)v=3;
  return v;
}

//�������� ��������� �� ���������� ����� � ������

int Load(TRoute *aRoute, char *FileName, int size) 
{
  string s;
  size=0;
  TRoute Route;
  strcpy(FileName,GetFileName());
  ifstream TextFile(FileName); //"routes.txt"
  while (!TextFile.eof())
  { 
    if(TextFile.eof())break;
    if(size==100)break;
    
    getline(TextFile,s);
    strcpy(Route.Name,s.c_str());
    
    getline(TextFile,s);
    stringstream ss(s);
    ss>>Route.Count;
    
    getline(TextFile,s);
    stringstream ss2(s);
    ss2>>Route.Len;
    
    aRoute[size]=Route;
    size++;
  }
  TextFile.close();
  Show(aRoute,size);
  cout<<"��������� �������: "<<size<<endl;
  return size;
}

//���������� ��������� ������� � ��������� ����

int Save(TRoute *aRoute, char *FileName, int size) 
{
  TRoute Route;
  ofstream TextFile(FileName); //"towns.txt"
  for(int i=0;i<size;i++)
  { 
    Route=aRoute[i];
    TextFile<<Route.Name<<endl;
    TextFile<<Route.Count<<endl;
    TextFile<<Route.Len;
    if(i<size-1)TextFile<<endl;
  }
  TextFile.close();
  Show(aRoute,size);
  cout<<"��������� �������: "<<size<<endl;
  return size;
}

//���������� ������ �������� � ����� �������

int Add(TRoute *aRoute, int size)  
{
  system("cls");
  cout<<"���������� ������ �������� � ����� ������"<<endl;
  char c[60]; 
  TRoute Route;
  cout<<"������� �������� �����:"<<endl;
  
  cout<<"����� � �������� ��������: ";
  fflush(stdin);
  gets(c);
  strcpy(aRoute[size].Name,c);
  
  cout<<"���������� ������ ����������: ";
  fflush(stdin);
  cin>>aRoute[size].Count;
  
  cout<<"������������� �������� (��): ";
  fflush(stdin);
  cin>>aRoute[size].Count;
  
  return size+1;
}

//������������� ����� ���������� ��������

int Edit(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"������� ����� ������ ��� ��������������: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"�������������� ����� ���������� ��������"<<endl;
  Line();
  Data(aRoute[k],k);
  Line();
  char c[60];
  TRoute Route;
  cout<<"������� ����� �������� �����:"<<endl;
  
  cout<<"����� � �������� ��������: ";
  fflush(stdin);
  gets(c);
  strcpy(aRoute[k].Name,c);
  
  cout<<"���������� ������ ����������: ";
  fflush(stdin);
  cin>>aRoute[k].Count;
  
  cout<<"������������� �������� (��): ";
  fflush(stdin);
  cin>>aRoute[k].Len;
  
  //aRoute[k]=Route;
  
  return size;
}

//�������� ���������� ��������

int Del1(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"������� ����� ������ ��� ��������: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"�������� ���������� ��������"<<endl;
  Line();
  Data(aRoute[k],k);
  Line();
  int yes;
  cout<<"��� ������������� �������� �������� ������� 1: ";
  cin>>yes;
  if(yes==1) for(int i=k;i<size-1;i++) aRoute[i]=aRoute[i+1];
  return size-1;
}

//���������� ������� �� ��������� ����

int SortOrder=0;

int Sort(TRoute *aRoute,int size) 
{
  if(SortOrder==0)SortOrder=-1;
  SortOrder=-SortOrder;
  TRoute Route;
  int i,j;
  for(i=0;i<size-1;i++)
  for(j=i+1;j<size;j++)
  if(SortOrder*aRoute[i].Len>SortOrder*aRoute[j].Len)
  {
    Route=aRoute[i];
    aRoute[i]=aRoute[j];
    aRoute[j]=Route;
  }
  Show(aRoute,size);
  if(SortOrder==1)
    cout<<"������ ������������ �� ����������� ����� ���������"<<endl;
  else
    cout<<"������ ������������ �� �������� ����� ���������"<<endl;  
  return size;
}

//�������� ��������� �� ������� (���� < ��� > ��������� ��������)

int Del2(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int length,k=0;
  TRoute Route;
  cout<<"�������� ��������� �� �������: ����� �������� ������ ��������"<<endl;
  cout<<"������� ����� ��������, ������ ������� ������� �������: ";
  cin>>length;
  system("cls");
  cout<<"�������� ��������� ���������"<<endl;
  Line();
  for(int i=0;i<size;i++) 
    if(aRoute[i].Len<length)
      Data(aRoute[i],i);
  Line();
  int yes;
  cout<<"��� �������� ������� 1, ����� - 0: ";
  cin>>yes;
  if(yes==1)
  {
    //�������� ��������� � ������ ������ ��������
    //����� ��������������� ���������� �� ����� ��������
    for(int i=0;i<size-1;i++) 
    for(int j=i+1;j<size;j++) 
      if(aRoute[i].Len<length && aRoute[j].Len>=length)
      {
        Route=aRoute[i];
        aRoute[i]=aRoute[j];
        aRoute[j]=Route;
      }
    for(int i=0;i<size;i++) 
      if(aRoute[i].Len<length)k++;
    return size-k;
  }
  else return size;
}

//�������� ���������, ������� �� ����������

int Del3(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"������� ����� ��������, � �������� ����� ������ ��������: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"�������� ��������� ���������"<<endl;
  Line();
  for(int i=k;i<size;i++) Data(aRoute[i],i);
  Line();
  int yes;
  cout<<"��� �������� ������� 1, ����� - 0: ";
  cin>>yes;
  if(yes==1) return k;
  else return size;
}

//����������� �������������� �����

void Line()
{
  for(int i=0;i<79;i++)cout<<"-"; cout<<endl;
}

//����������� ������ ������� � �������

void Data(TRoute Route, int index)
{
  printf("| %3d | %-50s | %6d | %6.1f |\n",
    index+1,Route.Name,Route.Count,Route.Len);
}

//����������� ���������� �������� �������

void Head()
{
  printf("| %3s | %-50s | %6s | %6s |\n",
    " �","����� � �������� ��������","���-��","�����");
  printf("| %3s | %-50s | %6s | %6s |\n",
    "�/�","���������� ����������","������","(��)");
}

//�������� ���� ��������� �������

int Show(TRoute *aRoute, int size) 
{
  cout<<"\n� � � � � �   � � � � � � � � �"<<endl;
  Line();
  Head();
  Line();
  for(int i=0;i<size;i++) Data(aRoute[i],i);
  Line();
  return size;
}

//��������, ������ �� ������

int IsEmpty(int size)
{
  if(size>0)return 0;
  else
  {
    cout<<endl<<"������ ����!"<<endl;
    return 1;
  }
}

// ����� ����� ���������� ����� �� �������� ��������

char * GetFileName()
{
  WIN32_FIND_DATA FindFile; //
  HANDLE HandleFile=FindFirstFile("*.txt", &FindFile);
  char FileName[100][MAX_PATH]; //������ ����� � ������� ������
  int i,FileIndex=0;
  if (HandleFile==INVALID_HANDLE_VALUE)
    puts("���� �� ������");
  do
  {
    strcpy(FileName[FileIndex], FindFile.cFileName);
    ++FileIndex;
    if(FileIndex==100)break;
  }
  while (FindNextFile(HandleFile,&FindFile));
  FindClose(HandleFile);
  cout<<endl<<"������ ������ � �������:"<<endl;
  for(i=0;i<FileIndex;i++)
    printf("%2d %s\n",i+1,FileName[i]);
  cout<<"������� ����� ����� ��� ��������: ";
  cin>>i;
  if(i<1 || i>FileIndex)i=1;
  system("cls");
  return FileName[i-1];
}
