#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

char* makePwd(char* str, char(*pwd)[100], int col);
void checkDir(char* argv);
int main(int argc, char* argv[]) {
	if (argc != 2)
		printf("Invalid input data: enter the name of only one file");
	else
		checkDir(argv[1]);
	return 0;
}

void checkDir(char* argv)
{
	char pwd[3][100];
	char str[100];
	strcpy(pwd[0], argv);
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(argv)))
	{
		while ((ent = readdir(dir)))
		{
			struct stat st1;
			stat(ent->d_name, &st1);
			strcpy(pwd[1], ent->d_name);
			if (S_ISDIR(st1.st_mode) && (ent->d_name)[0] != '.')
			{
				DIR* dir1;
				struct dirent* ent1;
				if ((dir1 = opendir(makePwd(str, pwd, 2))))
				{
					struct stat st2;
					while ((ent1 = readdir(dir1)) != NULL)
					{
						strcpy(pwd[2], ent1->d_name);
						stat(makePwd(str, pwd, 3), &st2);
						if (S_ISDIR(st2.st_mode) && (ent1->d_name)[0] != '.')
						{
							printf("%s\n", ent->d_name);
							break;
						}

						closedir(dir1);
					}
				else
				{
					printf("%s - no such directory or not enough rights\n", ent->d_name);
				}
				}

			}
			closedir(dir);
		}
	else
	{
		printf("%s - no such directory or not enough rights\n", argv);
	}
	}
	char* makePwd(char* str, char(*pwd)[100], int col)
	{
		strcpy(str, ".");
		for (int i = 0; i < col; i++)
		{
			strcat(str, "/");
			strcat(str, pwd[i]);
		}
		return str;
	}
}
