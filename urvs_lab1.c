#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

char *makePwd(char *str, char (*pwd)[100], int amt);
void checkDir(char *argv);

int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("Invalid input data: enter the name of only one file");
    else
        checkDir(argv[1]);

    return 0;
}
//----------------------------------------------------------------------
/** 
 * Функция, которая определяет имена тех каталогов в каталоге,
 * в которых есть каталоги
 * @param argv имя целевого каталога, в котором будет происходить поиск 
**/
void checkDir(char *argv)
{
    char pwd[3][100];
    char str[100];
    strcpy(pwd[0], argv);
    DIR *dir;             // внутренняя структура для работы с типом dirent
    struct dirent *entry; //структура записей, содержащих информацию о каталоге

    // открываем поток целевого каталога
    if (dir = opendir(argv)) 
    {
        // считываем файлы в каталоге по очереди
        while (entry = readdir(dir)) 
        { 
            struct stat st1; // структура для сохранения информации
            stat(entry->d_name, &st1);
            strcpy(pwd[1], entry->d_name); // Копируем имя каталога в массив pwd

            // Проверяем, является ли файл каталогом и не каталогом "."
            if (S_ISDIR(st1.st_mode) && (entry->d_name)[0] != '.')
            { 
                // Если файл является каталогом, открываем для него поток
                // и начинаем считывать файлы в нем
                DIR *dir1;
                struct dirent *ent1;

                if (dir1 = opendir(makePwd(str, pwd, 2)))
                {
                    struct stat st2;

                    while ((ent1 = readdir(dir1)) != NULL)
                    {
                        strcpy(pwd[2], ent1->d_name);
                        stat(makePwd(str, pwd, 3), &st2);

                        if (S_ISDIR(st2.st_mode) && (ent1->d_name)[0] != '.')
                        {
                            // Если файл является каталогом, то
                            // выводим его имя в консоль
                            printf("%s\n", entry->d_name);
                            break;
                        }
                    }

                    closedir(dir1);
                }
                else
                    printf("%s - no such directory or not enough rights\n", entry->d_name);
            }
        }

        closedir(dir);
    }
    else
        printf("%s - no such directory or not enough rights\n", argv);
}
//------------------------------------------------------------------------------------------
/**
 * Составляет относительный путь дочерних каталогов по отношению к целевому
 * 
 * @param str строка, в которой будет собираться путь
 * @param pwd составная часть итогового пути
 * @param amt количество частей
 * @return Строка, содержащая путь
**/
char *makePwd(char *str, char (*pwd)[100], int amt)
{
    strcpy(str, ".");

    for (int i = 0; i < amt; i++)
    {
        strcat(str, "/");
        strcat(str, pwd[i]);
    }

    return str;
}