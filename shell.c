#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * main - a program that executes the command ls -l /tmp
 * in 5 different child processes
 * Each child should be created by the same process (the father)
 * Wait for a child to exit before creating a new child
 *
 * Steps
 * 1. Print a promt
 * 2. Take input
 * 3. Run the input
 * 4. Repeat steps 1 to 3
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[2], *buf;
	size_t n;
	ssize_t i;
	pid_t fr;
	int status;

	argv[1] = NULL;
	n = 10;
	buf = NULL;
	printf("#cisfun$ ");
	i = getline(&buf, &n, stdin);
	while (*buf != EOF)
	{
		if (i == -1)
		{
			perror("Error");
			break;
		}
		if (buf[i - 1] == '\n')
			buf[i - 1] = '\0';
		argv[0] = buf;
		fr = fork();
		if (fr == -1)
		{
			perror("Error");
			break;
		}
		else if (fr == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error");
				break;
			}
		}
		else
		{
			wait(&status);
			printf("#cisfun$ ");
			i = getline(&buf, &n, stdin);
		}
	}
	free(buf);
	return (0);
}
