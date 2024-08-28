#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <pty.h> /* for openpty and forkpty */
#include <utmp.h> /* for login_tty */
#include <time.h>

#define SLAVE_DEV_NAME_MAX_LEN       100
#define PTY_BUFF_MAX_LEN             100


/*
 * call opentty
 * print any data read from ptmx
 */
int main(int argc, char *argv[])
{
    int mpty = 0;
    int spty = 0;
    char spty_name[SLAVE_DEV_NAME_MAX_LEN] = {'\0'};
    char *pname = NULL;

    int rv = 0;
    int namelen = 0;

    int n = 0;
    char buf[PTY_BUFF_MAX_LEN] = {'\0'};

    fd_set rdfdset;

    rv = openpty(&mpty, &spty, spty_name, NULL, NULL);

    if (-1 == rv)
    {
        perror("Failed to get a pty");
        goto ERROR;
    }

    printf("Get a pty pair, FD -- master[%d] slave[%d]\n", mpty, spty);
    printf("Slave name is:%s\n", spty_name);

    /* Monitoring the pty master for reading */
    FD_ZERO(&rdfdset);
    FD_SET(mpty, &rdfdset);

    while (1)
    {
        rv = select(mpty + 1, &rdfdset, NULL, NULL, NULL);

        if (0 > rv)
        {
            perror("Failed to select");
            goto ERROR;
        }

        if (FD_ISSET(mpty, &rdfdset))
        {
            /* Now data can be read from the pty master */
            n = read(mpty, buf, PTY_BUFF_MAX_LEN);
            if (0 < n)
            {
                int ii = 0;

                memset(buf + n, 0, PTY_BUFF_MAX_LEN - n);

                printf("-----------------------------------\n");
                printf("Message from slave:\n");
                printf("%s\n", buf);
                printf("------%d bytes------\n\n", n);

            }
            else if (0 == n)
            {
                printf("No byte is read from the master\n");
            }
            else
            {
                perror("Failed to read the master");
                goto ERROR;
            }
        }
        else
        {
            printf("The master isn't readable!\n");
            goto ERROR;
        }
    }
ERROR:
    if (0 < mpty)
    {
        close(mpty);
    }
    if (0 < spty)
    {
        close(spty);
    }
    return -1;
}