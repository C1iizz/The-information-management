#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stu
{
  char sz_ID[16];    // 学生学号
  char sz_Name[16];  // 学生姓名
  char sz_Class[16]; // 学生班级
  char sz_Room[16];  // 学生宿舍
  char sz_Phone[16]; // 学生电话
  char sz_Emain[16]; // 学生邮箱
} student;

#define STU_MAXSIZE 6666
int i_stuSize;
int add_stuSize;
student stu[STU_MAXSIZE];

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

//======显示主菜单======//
void Main_Menu(void)
{
  printf("\n");
  printf("╔════════════════════════════════╗\n");
  printf("║       " MAGENTA "学生通讯录管理系统" RESET "       ║\n");
  printf("╠════════════════════════════════╣\n");
  printf("║    1.导入全部学生通讯信息" RESET "      ║\n");
  printf("║    2.添加新学生通讯信息" RESET "        ║\n");
  printf("║    3.修改学生通讯信息" RESET "          ║\n");
  printf("║    4.查询学生通讯信息" RESET "          ║\n");
  printf("║    5.显示全部学生通讯信息" RESET "      ║\n");
  printf("║    6.按班级显示学生通讯信息" RESET "    ║\n");
  printf("║    7.按宿舍显示学生通讯信息" RESET "    ║\n");
  printf("║    8.删除学生通讯信息" RESET "          ║\n");
  printf("║    0." RED "退出系统" RESET "                  ║\n");
  printf("╚════════════════════════════════╝\n");
  printf("\n");
}

//======导入全部学生通讯信息======//
void Input_stu_Information(student stu[])
{
  int i;
  printf(MAGENTA "\n请依次输入学生通讯信息(学号 姓名 班级 宿舍门牌号 电话 E-mail):\n" RESET);
  for (i = 0; i < i_stuSize; i++)
  {
    printf(MAGENTA "请输入第%d个学生的通讯信息:\n" RESET, i + 1);
    scanf("%s%s%s%s%s%s", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
    printf("\n学生通讯信息录入成功\n");
  }
  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
}

//======添加学生通讯信息======//
void Add_stu_Information(student stu[])
{
  int i;
  printf(MAGENTA "\n请依次输入学生通讯信息(学号 姓名 班级 宿舍门牌号 电话 E-mail):\n" RESET);
  for (i = i_stuSize; i <= i_stuSize + add_stuSize; i++)
  {
    printf(MAGENTA "请输入添加的第%d个学生的通讯信息:\n" RESET, i - i_stuSize + 1);
    scanf("%s%s%s%s%s%s", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
    printf("\n学生通讯信息添加成功\n");
  }
  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
}

//======将学生通讯信息存入communicationfile.dat======//
void Save_File(student stu[])
{
  FILE *fp;
  int i;
  if ((fp = fopen("communication.dat", "wb")) == NULL)
  {
    printf(RED "Save_File函数打开文件communication.dat失败，按任意键退出!\n" RESET);
    exit(1);
  }
  for (i = 0; i < i_stuSize; i++)
  {
    if (fwrite(&stu[i], sizeof(student), 1, fp) != 1)
    {
      printf(RED "Write file error!\n" RESET);
      exit(1);
    }
  }
  fclose(fp);
}

//======主菜单第一选项：导入学生通讯信息======//
int Input_Date()
{
  printf(MAGENTA "\n请输入需导入通讯信息的学生人数：" RESET);
  scanf("%d", &i_stuSize);
  Input_stu_Information(stu);
  Save_File(stu);
  return (i_stuSize);
}

//======主菜单第二选项：添加新的学生通讯信息======//
int Add_Date()
{
  int add_stuSize;
  printf(MAGENTA "\n请输入要添加的学生人数：" RESET);
  scanf("%d", &add_stuSize);
  Add_stu_Information(stu);
  i_stuSize = i_stuSize + add_stuSize;
  Save_File(stu);
  return (i_stuSize);
}

//======主菜单第三选项：修改学生通讯信息======//
void Modify_Date()
{
  int Search_ID(char sz_ID[16]);
  int i;
  char s_ID[16];
  FILE *fp;
  printf(MAGENTA "请输入要修改通讯信息的学生学号:\n" RESET);
  scanf("%s", s_ID);
  i = Search_ID(s_ID);
  if (i == -1)
  {
    printf(RED "未找到该学号的学生.\n" RESET);
    return;
  }
  printf(MAGENTA "请按[班级 宿舍 电话 邮箱]顺序输入新的通讯信息\n" RESET);
  scanf("%s%s%s%s", stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
  if ((fp = fopen("communication.dat", "wb")) == NULL)
  {
    printf("Modify_Date函数打开文件communication.dat失败，按任意键退出!");
    return;
  }
  for (int j = 0; j < i_stuSize; j++)
  {
    fwrite(&stu[j], sizeof(student), 1, fp);
  }
  printf("成功修改!\n");
  fclose(fp);
  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
}

//======主菜单第四选项：学生通讯信息查询======//
/*学生通讯信息查询菜单*/
void Search_Menu()
{
  printf("\n");
  printf("=====================================\n");
  printf("          学生通讯信息查询\n");
  printf("=====================================\n");
  printf("  1. 按学号查询\n");
  printf("  2. 按姓名查询\n");
  printf(RED "  0. 退出查询 " RESET " \n");
  printf("=====================================\n");
}

/*1.按学号查询*/
int Search_ID(char sz_ID[16])
{
  int i;
  for (i = 0; i < i_stuSize; i++)
  {
    if (!strcmp(sz_ID, stu[i].sz_ID))
    {
      printf("学号\t姓名\t班级\t宿舍\t电话\tE-mail\n");
      printf("---------------------------------------------\n");
      printf("%s\t%s\t%s\t%s\t%s\t%s\n", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
      printf("---------------------------------------------\n");
      getchar();
      printf("\n" CYAN "按Enter返回主菜单..." RESET);
      getchar();
      return i;
    }
  }
  printf(RED "未找到该学生\n" RESET);
  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
  return -1;
}
/*2.按姓名查询*/
int Search_Name(char sz_Name[16])
{
  int i;
  int found = 0; // 用于检查是否找到任何匹配的学生
  for (i = 0; i < i_stuSize; i++)
  {
    if (!strcmp(sz_Name, stu[i].sz_Name))
    {
      if (!found)
      {
        printf("学号\t姓名\t班级\t宿舍\t电话\tE-mail\n");
        printf("---------------------------------------------\n");
      }
      printf("%s\t%s\t%s\t%s\t%s\t%s\n", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
      found = 1;
    } 
  }

  if (!found)
  {
    printf(RED "未找到该学生\n" RESET);
  }
  else
  {
    printf("---------------------------------------------\n");
  }

  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
  return found ? 1 : -1; 
}

void Search_Date()
{
  int flag = 1;
  int Select;
  char s_id[16];
  char s_name[16];
  while (flag)
  {
    Search_Menu();
    printf(MAGENTA "请输入所选查询功能号:" RESET);
    scanf("%d", &Select);
    switch (Select)
    {
    case 1:
      printf(MAGENTA "请输入查询学号:" RESET);
      scanf("%s", s_id);
      Search_ID(s_id);
      if (!Search_ID)
      {
        printf(RED "未找到该学生的通讯信息!" RESET);
      }
      break;
    case 2:
      printf(MAGENTA "请输入查询姓名:" RESET);
      scanf("%s", s_name);
      Search_Name(s_name);
      if (!Search_Name)
      {
        printf(RED "未找到该学生的通讯信息!" RESET);
      }
      break;
    case 0:
      printf("成功退出查询!\n");
      flag = 0;
      break;
    default:
      printf(RED "请输入正确的功能号!\n" RESET);
      getchar();
      printf("\n" CYAN "按Enter返回主菜单..." RESET);
      getchar();
      break;
    }
  }
}

//======主菜单第五选项：显示全部学生的通讯信息======//
void All_Date()
{
  int i;
  printf("\n\t       全体学生通讯录\n");
  printf("\t     =================\n");
  printf("学号\t姓名\t班级\t宿舍\t电话\t邮箱\n");
  printf("--------------------------------------------\n");
  for (i = 0; i < i_stuSize; i++)
  {
    printf("%s\t%s\t%s\t%s\t%s\t%s\n", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
  }
  printf("--------------------------------------------\n");
  getchar();
  printf("\n" CYAN "按Enter返回主菜单..." RESET);
  getchar();
}
//======主菜单第六选项：显示班级各学生通讯信息======//
void Class_Date()
{
  int i = 0;
  int j = 0;
  int right = 0;
  char sz_Class[16];
  printf(MAGENTA "请输入要查询的班级:" RESET);
  scanf("%s", sz_Class);
  for (; j < i_stuSize; j++)
  {
    if (!strcmp(sz_Class, stu[j].sz_Class))
      right = 1;
    break;
  }
  if (right)
  {
    printf("\n\t      %s班各学生通讯录\n", sz_Class);
    printf("\t     =================\n");
    printf("学号\t姓名\t班级\t宿舍\t电话\t邮箱\n");
    printf("--------------------------------------------\n");
    for (; i < i_stuSize; i++)
    {
      if (!strcmp(sz_Class, stu[i].sz_Class))
      {
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
      }
    }
    printf("--------------------------------------------\n");
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
  else
  {
    printf(RED "该班级不存在\n" RESET);
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
}

//======主菜单第七选项：显示宿舍各学生通讯信息======//
void Room_Date()
{
  int i = 0;
  int j = 0;
  char sz_Room[16];
  int right = 0;
  printf(MAGENTA "请输入要查询的宿舍:" RESET);
  scanf("%s", sz_Room);
  for (; j < i_stuSize; j++)
  {
    if (!strcmp(sz_Room, stu[j].sz_Room))
      right = 1;
    break;
  }
  if (right)
  {
    printf("\n\t      %s宿舍各学生通讯录\n", sz_Room);
    printf("\t     ====================\n");
    printf("学号\t姓名\t班级\t宿舍\t电话\t邮箱\n");
    printf("--------------------------------------------\n");
    for (; i < i_stuSize; i++)
    {
      if (!strcmp(sz_Room, stu[i].sz_Room))
      {
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", stu[i].sz_ID, stu[i].sz_Name, stu[i].sz_Class, stu[i].sz_Room, stu[i].sz_Phone, stu[i].sz_Emain);
      }
    }
    printf("--------------------------------------------\n");
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
  else
  {
    printf(RED "该宿舍不存在\n" RESET);
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
}
//======主菜单第八选项：删除学生通讯信息======//
/*删除学生通讯信息菜单*/
void Delete_Menu()
{
  printf("\n");
  printf("=====================================\n");
  printf("        学生通讯信息删除\n");
  printf("=====================================\n");
  printf("  1. 按学号删除\n");
  printf("  2. 按姓名删除\n");
  printf("  0. 取消删除\n");
  printf("=====================================\n");
}

void Delete_Id(char id[])
{
  int i;
  int found = 0;
  for (i = 0; i < i_stuSize; i++)
  {
    if (strcmp(stu[i].sz_ID, id) == 0)
    {
      for (int j = i; j < i_stuSize - 1; j++)
      {
        stu[j] = stu[j + 1];
      }
      i_stuSize--;
      Save_File(stu);
      printf("成功删除学生信息!");
      getchar();
      printf("\n" CYAN "按Enter返回主菜单..." RESET);
      getchar();
      found = 1;
      break;
    }
  }
  if (!found)
  {
    printf(RED "未找到学号为%s的学生。\n" RESET, id);
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
}

void Delete_Name(char name[])
{
  int i;
  int found = 0;
  for (i = 0; i < i_stuSize; i++)
  {
    if (strcmp(stu[i].sz_Name, name) == 0)
    {
      for (int j = i; j < i_stuSize - 1; j++)
      {
        stu[j] = stu[j + 1];
      }
      i_stuSize--;
      Save_File(stu);
      printf("成功删除学生信息!");
      found = 1;
      getchar();
      printf("\n" CYAN "按Enter返回主菜单..." RESET);
      getchar();
      break;
    }
  }
  if (!found)
  {
    printf(RED "未找到姓名为%s的学生。\n" RESET, name);
    getchar();
    printf("\n" CYAN "按Enter返回主菜单..." RESET);
    getchar();
  }
}

void Delete_Date()
{
  int Select;
  int great = 1;
  char s_id[16];
  char s_name[16];
  Delete_Menu();
  while (great)
  {
    printf(MAGENTA "请输入所选删除功能号:" RESET);
    scanf("%d", &Select);
    switch (Select)
    {
    case 1:
      printf(MAGENTA "请输入学号:" RESET);
      scanf("%s", s_id);
      Delete_Id(s_id);
      great = 0;
      break;
    case 2:
      printf(MAGENTA "请输入姓名:" RESET);
      scanf("%s", s_name);
      Delete_Name(s_name);
      great = 0;
      break;
    case 0:
      printf(RED "成功退出程序!" RESET "\n");
      break;
      great = 0;
    default:
      printf(RED "请输入正确的功能号!\n\n" RESET);
    }
  }
}

//======初始化数组函数======//
int Init_Arr()
{
  FILE *fp;
  int i = 0;
  if ((fp = fopen("communication.dat", "rb")) == NULL)
  {
    printf(RED "Init_Arr函数打开文件communication.dat失败，按任意键退出！" RESET);
    return 0;
  }
  while (fread(&stu[i], sizeof(student), 1, fp) == 1)
  {
    i++;
  }
  i_stuSize = i;
  fclose(fp);
  return 1;
}
//======主程序======//
void main()
{
  int SelectNum, flag = 1;
  while (flag)
  {
    Main_Menu();
    printf(MAGENTA "请输入所选功能号:" RESET);
    scanf("%d", &SelectNum);
    switch (SelectNum)
    {
    case 1:
      Input_Date();
      break;
    case 2:
      if (Init_Arr())
        Add_Date();
      break;
    case 3:
      if (Init_Arr())
        Modify_Date();
      break;
    case 4:
      if (Init_Arr())
        Search_Date();
      break;
    case 5:
      if (Init_Arr())
        All_Date();
      break;
    case 6:
      if (Init_Arr())
        Class_Date();
      break;
    case 7:
      if (Init_Arr())
        Room_Date();
      break;
    case 8:
      if (Init_Arr())
        Delete_Date();
      break;
    case 0:
      printf(RED "成功退出程序!" RESET "\n");
      flag = 0;
      break;
    default:
      printf(RED "输入错误，重新选择功能号!\n" RESET);
      getchar();
      printf("\n" CYAN "按Enter返回主菜单..." RESET);
      getchar();
      break;
    }
  }
}