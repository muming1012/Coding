#include	"mesg.h"

void
client(int readfd, int writefd)
{
	size_t	len;
	ssize_t	n;
	char	*ptr;
	struct mymesg	mesg;

	/* start buffer with pid and a blank */
	snprintf(mesg.mesg_data, MAXMESGDATA, "%ld ", (long) getpid());
	len = strlen(mesg.mesg_data);
	ptr = mesg.mesg_data + len;

	/* read pathname */
	Fgets(ptr, MAXMESGDATA - len, stdin);
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len-1] == '\n')
		len--;				/* delete newline from fgets() */
	mesg.mesg_len = len;
	mesg.mesg_type = 1;

	/* write PID and pathname to IPC channel */
	Mesg_send(writefd, &mesg);

	/* read from IPC, write to standard output */
	mesg.mesg_type = getpid(); // get its own response
	while ( (n = Mesg_recv(readfd, &mesg)) > 0)
		Write(STDOUT_FILENO, mesg.mesg_data, n);
}
