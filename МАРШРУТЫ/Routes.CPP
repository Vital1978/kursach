#include "MyFunctios.cpp"

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251); 
  system("mode con cols=81 lines=60");
  TRoute aRoute[100]; //массив записей
  char FileName[MAX_PATH];
  int m, size=0;
  while(1)
  {
  m=Menu();
  switch(m)
    {
    case 1: //передача записей в массив из текстового файла
      size=Load(aRoute, FileName, size);
      break;
    case 2: //вставка новой записи
      size=Add(aRoute, size);
      Show(aRoute,size);
      break;
    case 3: //вывод справочника на экран
      if(!IsEmpty(size))
        Show(aRoute,size);
      break;
    case 4: //сохранение записей из массива в файл
      if(!IsEmpty(size))
        Save(aRoute, FileName, size);
      break;
    case 5: //корректировка выбранного элемента
      if(!IsEmpty(size))
        Edit(aRoute, size);
      Show(aRoute,size);
      break;
    case 6: //удаление выбранного элемента
      if(!IsEmpty(size))
        size=Del1(aRoute, size);
      Show(aRoute,size);
      break;
    case 7: //удаление элемента по условию
      if(!IsEmpty(size)) 
        size=Del2(aRoute, size);
      Show(aRoute,size);
      break;
    case 8: //сортировка массива элементов
      if(!IsEmpty(size))
        size=Sort(aRoute, size);
      break;
    case 9: //удаление элементов от выбранного
      if(!IsEmpty(size))
        size=Del3(aRoute, size);
      Show(aRoute,size);
      break;
    case 0: //выход из программы
      return 0;
    }
    system("pause");
  }
}
