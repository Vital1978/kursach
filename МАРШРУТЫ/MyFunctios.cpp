#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct TRoute
  { 
    char Name[60]; //номер и название маршрута
    int Count;     //количество единиц транспорта на маршруте
    float Len;     //протяженность маршрута, км
  };
  
int Load(TRoute*, char*, int); //ввод из текстового файла в массив
int Add(TRoute*, int);  //добавление новых элементов в конец массива
int Show(TRoute*, int); //просмотр всех элементов массива
int Save(TRoute*, char*, int); //вывод элементов массива в текстовый файл
int Edit(TRoute*, int);  //корректировка полей выбранного элемента
int Del1(TRoute*, int);  //удаление выбранного элемента
int Del2(TRoute*, int); //удаление элементов по заданному условию
int Del3(TRoute*, int); //удаление элементов, начиная от выбранного
int Sort(TRoute*, int); //сортировка массива по числовому полю
int Menu(); //вывод меню на экран
void Line(); //вывод горизонтальной линии
void Data(TRoute, int); //вывод строки таблицы с данными
void Head(); //вывод заголовков столбцов таблицы
int IsEmpty(int); //список пуст
char * GetFileName(); //выбор имени файла с данными

//отображение главного меню

int Menu()
{
  int v;
  system("cls");
  cout<<"************ МАРШРУТЫ ГОРОДСКОГО ТРАНСПОРТА ************"<<endl;
  for(int i=0;i<80;i++)cout<<"=";
  cout<<endl;
  cout<<"1-Открыть 2-Добавить 3-Просмотр 4-Сохранить 5-Исправить 6-Удалить"<<endl;
  cout<<"7-Удалить по условию 8-Сортировка 9-Удалить от выбранного 0-Выход"<<endl;
  for(int i=0;i<80;i++)cout<<"=";
  cout<<"\nВведите номер команды -> ";
  cin>>v;
  cout<<endl;
  if(v<0 || v>10)v=3;
  return v;
}

//загрузка элементов из текстового файла в массив

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
  cout<<"Загружено записей: "<<size<<endl;
  return size;
}

//сохранение элементов массива в текстовый файл

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
  cout<<"Сохранено записей: "<<size<<endl;
  return size;
}

//добавление нового элемента в конец массива

int Add(TRoute *aRoute, int size)  
{
  system("cls");
  cout<<"Добавление нового элемента в конец списка"<<endl;
  char c[60]; 
  TRoute Route;
  cout<<"Введите значения полей:"<<endl;
  
  cout<<"Номер и название маршрута: ";
  fflush(stdin);
  gets(c);
  strcpy(aRoute[size].Name,c);
  
  cout<<"Количество единиц транспорта: ";
  fflush(stdin);
  cin>>aRoute[size].Count;
  
  cout<<"Протяженность маршрута (км): ";
  fflush(stdin);
  cin>>aRoute[size].Count;
  
  return size+1;
}

//корректировка полей выбранного элемента

int Edit(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"Введите номер записи для редактирования: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"Редактирование полей выбранного элемента"<<endl;
  Line();
  Data(aRoute[k],k);
  Line();
  char c[60];
  TRoute Route;
  cout<<"Введите новые значения полей:"<<endl;
  
  cout<<"Номер и название маршрута: ";
  fflush(stdin);
  gets(c);
  strcpy(aRoute[k].Name,c);
  
  cout<<"Количество единиц транспорта: ";
  fflush(stdin);
  cin>>aRoute[k].Count;
  
  cout<<"Протяженность маршрута (км): ";
  fflush(stdin);
  cin>>aRoute[k].Len;
  
  //aRoute[k]=Route;
  
  return size;
}

//удаление выбранного элемента

int Del1(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"Введите номер записи для удаления: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"Удаление выбранного элемента"<<endl;
  Line();
  Data(aRoute[k],k);
  Line();
  int yes;
  cout<<"Для подтверждения удаления элемента введите 1: ";
  cin>>yes;
  if(yes==1) for(int i=k;i<size-1;i++) aRoute[i]=aRoute[i+1];
  return size-1;
}

//сортировка массива по числовому полю

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
    cout<<"Список отсортирован по возрастанию длины маршрутов"<<endl;
  else
    cout<<"Список отсортирован по убыванию длины маршрутов"<<endl;  
  return size;
}

//удаление элементов по условию (поле < или > заданного значения)

int Del2(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int length,k=0;
  TRoute Route;
  cout<<"Удаление элементов по условию: длина маршрута меньше заданной"<<endl;
  cout<<"Введите длину маршрута, меньше которой следует удалить: ";
  cin>>length;
  system("cls");
  cout<<"Удаление выбранных элементов"<<endl;
  Line();
  for(int i=0;i<size;i++) 
    if(aRoute[i].Len<length)
      Data(aRoute[i],i);
  Line();
  int yes;
  cout<<"Для удаления введите 1, иначе - 0: ";
  cin>>yes;
  if(yes==1)
  {
    //удаление маршрутов с длиной меньше заданной
    //путем предварительной сортировки по этому признаку
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

//удаление элементов, начиная от выбранного

int Del3(TRoute *aRoute,int size) 
{
  Show(aRoute,size);
  int k;
  cout<<"Введите номер элемента, с которого нужно начать удаление: ";
  cin>>k;
  system("cls");
  k--;
  cout<<"Удаление выбранных элементов"<<endl;
  Line();
  for(int i=k;i<size;i++) Data(aRoute[i],i);
  Line();
  int yes;
  cout<<"Для удаления введите 1, иначе - 0: ";
  cin>>yes;
  if(yes==1) return k;
  else return size;
}

//отображение горизонтальной линии

void Line()
{
  for(int i=0;i<79;i++)cout<<"-"; cout<<endl;
}

//отображение строки таблицы с записью

void Data(TRoute Route, int index)
{
  printf("| %3d | %-50s | %6d | %6.1f |\n",
    index+1,Route.Name,Route.Count,Route.Len);
}

//отображение заголовков столбцов таблицы

void Head()
{
  printf("| %3s | %-50s | %6s | %6s |\n",
    " №","Номер и название маршрута","Кол-во","Длина");
  printf("| %3s | %-50s | %6s | %6s |\n",
    "п/п","городского транспорта","единиц","(км)");
}

//просмотр всех элементов массива

int Show(TRoute *aRoute, int size) 
{
  cout<<"\nС П И С О К   М А Р Ш Р У Т О В"<<endl;
  Line();
  Head();
  Line();
  for(int i=0;i<size;i++) Data(aRoute[i],i);
  Line();
  return size;
}

//проверка, пустой ли список

int IsEmpty(int size)
{
  if(size>0)return 0;
  else
  {
    cout<<endl<<"Список пуст!"<<endl;
    return 1;
  }
}

// выбор имени текстового файла из текущего каталога

char * GetFileName()
{
  WIN32_FIND_DATA FindFile; //
  HANDLE HandleFile=FindFirstFile("*.txt", &FindFile);
  char FileName[100][MAX_PATH]; //массив строк с именами файлов
  int i,FileIndex=0;
  if (HandleFile==INVALID_HANDLE_VALUE)
    puts("Путь не найден");
  do
  {
    strcpy(FileName[FileIndex], FindFile.cFileName);
    ++FileIndex;
    if(FileIndex==100)break;
  }
  while (FindNextFile(HandleFile,&FindFile));
  FindClose(HandleFile);
  cout<<endl<<"Список файлов с данными:"<<endl;
  for(i=0;i<FileIndex;i++)
    printf("%2d %s\n",i+1,FileName[i]);
  cout<<"Введите номер файла для загрузки: ";
  cin>>i;
  if(i<1 || i>FileIndex)i=1;
  system("cls");
  return FileName[i-1];
}
