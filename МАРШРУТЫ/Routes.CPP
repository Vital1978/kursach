#include "MyFunctios.cpp"

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251); 
  system("mode con cols=81 lines=60");
  TRoute aRoute[100]; //������ �������
  char FileName[MAX_PATH];
  int m, size=0;
  while(1)
  {
  m=Menu();
  switch(m)
    {
    case 1: //�������� ������� � ������ �� ���������� �����
      size=Load(aRoute, FileName, size);
      break;
    case 2: //������� ����� ������
      size=Add(aRoute, size);
      Show(aRoute,size);
      break;
    case 3: //����� ����������� �� �����
      if(!IsEmpty(size))
        Show(aRoute,size);
      break;
    case 4: //���������� ������� �� ������� � ����
      if(!IsEmpty(size))
        Save(aRoute, FileName, size);
      break;
    case 5: //������������� ���������� ��������
      if(!IsEmpty(size))
        Edit(aRoute, size);
      Show(aRoute,size);
      break;
    case 6: //�������� ���������� ��������
      if(!IsEmpty(size))
        size=Del1(aRoute, size);
      Show(aRoute,size);
      break;
    case 7: //�������� �������� �� �������
      if(!IsEmpty(size)) 
        size=Del2(aRoute, size);
      Show(aRoute,size);
      break;
    case 8: //���������� ������� ���������
      if(!IsEmpty(size))
        size=Sort(aRoute, size);
      break;
    case 9: //�������� ��������� �� ����������
      if(!IsEmpty(size))
        size=Del3(aRoute, size);
      Show(aRoute,size);
      break;
    case 0: //����� �� ���������
      return 0;
    }
    system("pause");
  }
}
