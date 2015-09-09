
/* headers on Linux for unpv2 , vonzhou*/

#ifndef	__unpipc_h
#define	__unpipc_h

#include	<sys/types.h>	/* basic system data types */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<limits.h>		/* PIPE_BUF */
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<stdarg.h>		/* for variable arg lists */



// ftok()
#include	<sys/ipc.h>		/* System V IPC */

#include	<sys/shm.h>		/* System V shared memory */

#include 	<sys/msg.h> /* System V message queues */

# include	<mqueue.h>		/* Posix message queues */

#include	<semaphore.h>	/* Posix semaphores */

# include	<sys/mman.h>	/* Posix shared memory */


//vonzhou: error: storage size of ‘buf’ isn’t known (struct msgbuf )
struct msgbuf{
	long mtype;
	char mtext[1];
};


#ifndef	SEM_FAILED
#define	SEM_FAILED	((sem_t *)(-1))
#endif



#ifndef	MAP_FAILED
#define	MAP_FAILED	((void *)(-1))
#endif




#ifdef	HAVE_SYS_SEM_H
#ifdef	__bsdi__
#undef	HAVE_SYS_SEM_H		/* hack: BSDI's semctl() prototype is wrong */
#else
# include	<sys/sem.h>		/* System V semaphores */
#endif

#ifndef	HAVE_SEMUN_UNION
/* $$.It semun$$ */
union semun {				/* define union for semctl() */
  int              val;
  struct semid_ds *buf;
  unsigned short  *array;
};
#endif
#endif	/* HAVE_SYS_SEM_H */



#ifdef	HAVE_SYS_SELECT_H
# include	<sys/select.h>	/* for convenience */
#endif

#ifdef	HAVE_POLL_H
# include	<poll.h>		/* for convenience */
#endif

#ifdef	HAVE_STROPTS_H
# include	<stropts.h>		/* for convenience */
#endif

#ifdef	HAVE_STRINGS_H
# include	<strings.h>		/* for convenience */
#endif

/* Next three headers are normally needed for socket/file ioctl's:
 * <sys/ioctl.h>, <sys/filio.h>, and <sys/sockio.h>.
 */
#ifdef	HAVE_SYS_IOCTL_H
# include	<sys/ioctl.h>
#endif
#ifdef	HAVE_SYS_FILIO_H
# include	<sys/filio.h>
#endif

#ifdef	HAVE_PTHREAD_H
# include	<pthread.h>
#endif

#ifdef	HAVE_DOOR_H
# include	<door.h>		/* Solaris doors API */
#endif

#ifdef	HAVE_RPC_RPC_H
#ifdef _PSX4_NSPACE_H_TS	/* Digital Unix 4.0b hack, hack, hack */
#undef	SUCCESS
#endif
# include	<rpc/rpc.h>		/* Sun RPC */
#endif

/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
#endif

/* Posix.1g requires that an #include of <poll.h> DefinE INFTIM, but many
   systems still DefinE it in <sys/stropts.h>.  We don't want to include
   all the streams stuff if it's not needed, so we just DefinE INFTIM here.
   This is the standard value, but there's no guarantee it is -1. */
#ifndef INFTIM
#define INFTIM          (-1)    /* infinite poll timeout */
#ifdef	HAVE_POLL_H
#define	INFTIM_UNPH				/* tell unpxti.h we defined it */
#endif
#endif

/* Miscellaneous constants */
#ifndef	PATH_MAX			/* should be in <limits.h> */
#define	PATH_MAX	1024	/* max # of characters in a pathname */
#endif

#define	MAX_PATH	1024
/* $$.ix [MAX_PATH]~constant,~definition~of$$ */
#define	MAXLINE		4096	/* max text line length */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* default permissions for new files */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */


// vonzhou :  error: ‘MSG_R’ undeclared (first use in this function)
#define MSG_R 0400
#define MSG_W 0200 
/* default permissions for new SV message queues */
#define	SVMSG_MODE	(MSG_R | MSG_W | MSG_R>>3 | MSG_R>>6)
					
/* $$.ix [SVMSG_MODE]~constant,~definition~of$$ */
#define	SVSEM_MODE	(SEM_R | SEM_A | SEM_R>>3 | SEM_R>>6)
					/* default permissions for new SV semaphores */

/* default permissions for new SV shared memory */
#define	SVSHM_MODE	(SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)
					/* default permissions for new SV shared memory */

/* for signal handlers */
typedef	void	Sigfunc(int);

/* vonzhou , error: ‘ulong_t’ undeclared (first use in this function)*/
typedef unsigned long ulong_t;

#ifdef	HAVE_SIGINFO_T_STRUCT
typedef	void	Sigfunc_rt(int, siginfo_t *, void *);
#endif

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))



/*
 * In our wrappers for open(), mq_open(), and sem_open() we handle the
 * optional arguments using the va_XXX() macros.  But one of the optional
 * arguments is of type "mode_t" and this breaks under BSD/OS because it
 * uses a 16-bit integer for this datatype.  But when our wrapper function
 * is called, the compiler expands the 16-bit short integer to a 32-bit
 * integer.  This breaks our call to va_arg().  All we can do is the
 * following hack.  Other systems in addition to BSD/OS might have this
 * problem too ...
 */

#ifdef	__bsdi__
#define	va_mode_t	int
#else
#define	va_mode_t	mode_t
#endif
/* $$.ix [va_mode_t]~datatype,~definition~of$$ */

		/* our record locking macros */
#define	read_lock(fd, offset, whence, len) \
			lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define	readw_lock(fd, offset, whence, len) \
			lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define	write_lock(fd, offset, whence, len) \
			lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
#define	writew_lock(fd, offset, whence, len) \
			lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define	un_lock(fd, offset, whence, len) \
			lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)
#define	is_read_lockable(fd, offset, whence, len) \
			lock_test(fd, F_RDLCK, offset, whence, len)
#define	is_write_lockable(fd, offset, whence, len) \
			lock_test(fd, F_WRLCK, offset, whence, len)
/* end unpipch */

#define	Read_lock(fd, offset, whence, len) \
			Lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define	Readw_lock(fd, offset, whence, len) \
			Lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define	Write_lock(fd, offset, whence, len) \
			Lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
#define	Writew_lock(fd, offset, whence, len) \
			Lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define	Un_lock(fd, offset, whence, len) \
			Lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)
#define	Is_read_lockable(fd, offset, whence, len) \
			Lock_test(fd, F_RDLCK, offset, whence, len)
#define	Is_write_lockable(fd, offset, whence, len) \
			Lock_test(fd, F_WRLCK, offset, whence, len)

			/* prototypes for our own library functions */
void	 daemon_init(const char *, int);
void	 daemon_inetd(const char *, int);
char	*gf_time(void);
int		 lock_reg(int, int, int, off_t, int, off_t);
pid_t	 lock_test(int, int, off_t, int, off_t);
void	*my_shm(size_t);
char	*px_ipc_name(const char *);
int		 readable_timeo(int, int);
ssize_t	 readline(int, void *, size_t);
ssize_t	 readn(int, void *, size_t);
int		 set_concurrency(int);
Sigfunc *signal_intr(int, Sigfunc *);
int	 	 sleep_us(unsigned int);
int		 start_time(void);
double	 stop_time(void);
int		 touch(void *, int);
void	 tv_sub(struct timeval *, struct timeval *);
int		 writable_timeo(int, int);
ssize_t	 writen(int, const void *, size_t);



#ifndef	HAVE_ISFDTYPE_PROTO
int		 isfdtype(int, int);
#endif

#ifndef	HAVE_PSELECT_PROTO
int		 pselect(int, fd_set *, fd_set *, fd_set *,
				 const struct timespec *, const sigset_t *);
#endif

#ifndef	HAVE_SNPRINTF_PROTO
int		 snprintf(char *, size_t, const char *, ...);
#endif

			/* prototypes for our own library wrapper functions */
char	*Gf_time(void);
void	 Lock_reg(int, int, int, off_t, int, off_t);
pid_t	 Lock_test(int, int, off_t, int, off_t);
void	*My_shm(size_t);
char	*Px_ipc_name(const char *);
int		 Readable_timeo(int, int);
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
void	 Set_concurrency(int);
Sigfunc *Signal(int, Sigfunc *);
Sigfunc *Signal_intr(int, Sigfunc *);

#ifdef	HAVE_SIGINFO_T_STRUCT
Sigfunc_rt *Signal_rt(int, Sigfunc_rt *);
Sigfunc_rt *Signal_rt_intr(int, Sigfunc_rt *);
#endif

void	 Sleep_us(unsigned int);
void	 Start_time(void);
double	 Stop_time(void);
void	 Touch(void *, int);
int		 Writable_timeo(int, int);
void	 Writen(int, void *, size_t);

			/* prototypes for our Unix wrapper functions */
void	*Calloc(size_t, size_t);
void	 Close(int);
void	 Dup2(int, int);
int		 Fcntl(int, int, void *);
pid_t	 Fork(void);
long	 Fpathconf(int, int);
void	 Fstat(int, struct stat *);
key_t	 Ftok(const char *, int);
void	 Ftruncate(int, off_t);
int		 Getopt(int, char *const *, const char *);
void	 Gettimeofday(struct timeval *, void *);
int		 Ioctl(int, int, void *);
void	 Kill(pid_t, int);
off_t	 Lseek(int, off_t, int);
void	*Malloc(size_t);
void	 Mkfifo(const char *, mode_t);
void	 Mktemp(char *);
void	*Mmap(void *, size_t, int, int, int, off_t);
void	 Munmap(void *, size_t);
int		 Open(const char *, int, ...);
long	 Pathconf(const char *, int);
void	 Pipe(int *fds);
ssize_t	 Read(int, void *, size_t);
int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Sigaddset(sigset_t *, int);
void	 Sigdelset(sigset_t *, int);
void	 Sigemptyset(sigset_t *);
void	 Sigfillset(sigset_t *);
int		 Sigismember(const sigset_t *, int);
void	 Sigpending(sigset_t *);
void	 Sigprocmask(int, const sigset_t *, sigset_t *);
#ifdef	HAVE_SIGINFO_T_STRUCT
void	 Sigqueue(pid_t, int, const union sigval);
#endif
#ifdef	HAVE_SIGWAIT
void	 Sigwait(const sigset_t *, int *);
#endif
void	 Stat(const char *, struct stat *);
char	*Strdup(const char *);
long	 Sysconf(int);
void	 Sysctl(int *, u_int, void *, size_t *, void *, size_t);
void	 Unlink(const char *);
void	*Valloc(size_t);
pid_t	 Wait(int *);
pid_t	 Waitpid(pid_t, int *, int);
void	 Write(int, void *, size_t);

#ifdef	HAVE_MQUEUE_H
			/* 4Posix message queues */
mqd_t	 Mq_open(const char *, int, ...);
void	 Mq_close(mqd_t);
void	 Mq_unlink(const char *pathname);
void	 Mq_send(mqd_t, const char *, size_t, unsigned int);
ssize_t	 Mq_receive(mqd_t, char *, size_t, unsigned int *);
void	 Mq_notify(mqd_t, const struct sigevent *);
void	 Mq_getattr(mqd_t, struct mq_attr *);
void	 Mq_setattr(mqd_t, const struct mq_attr *, struct mq_attr *);
#endif	/* HAVE_MQUEUE_H */

#ifdef	HAVE_SEMAPHORE_H
			/* 4Posix semaphores */
sem_t	*Sem_open(const char *, int, ...);
void	 Sem_close(sem_t *);
void	 Sem_unlink(const char *);
void	 Sem_init(sem_t *, int, unsigned int);
void	 Sem_destroy(sem_t *);
void	 Sem_wait(sem_t *);
int		 Sem_trywait(sem_t *);
void	 Sem_post(sem_t *);
void	 Sem_getvalue(sem_t *, int *);
#endif	/* HAVE_SEMAPHORE_H */

/* Note that <sys/mman.h> is defined on some systems that do not support
 * Posix shared memory (e.g., 4.4BSD), because this header predates Posix
 * and appears on any system that supports mmap().  Therefore we cannot
 * use this to determine whether the implementation supports Posix shared
 * memory or not.  We use our own HAVE_SHM_OPEN_PROTO symbol.
 */

#ifdef	HAVE_SHM_OPEN_PROTO
			/* 4Posix shared memory */
int		 Shm_open(const char *, int, mode_t);
void	 Shm_unlink(const char *);
#endif

/* System V message queues API*/
int		 Msgget(key_t key, int flag);
void	 Msgctl(int, int, struct msqid_ds *);
void	 Msgsnd(int, const void *, size_t, int);
ssize_t	 Msgrcv(int, void *, size_t, int, int);

#ifdef	HAVE_SYS_SEM_H
			/* 4System V semaphores */
int		 Semget(key_t, int, int);
int		 Semctl(int, int, int, ...);
void	 Semop(int, struct sembuf *, size_t);
#endif	/* HAVE_SYS_SEM_H */

/* System V shared memory */
int		 Shmget(key_t, size_t, int);
void	*Shmat(int, const void *, int);
void	 Shmdt(const void *);
void	 Shmctl(int, int, struct shmid_ds *);

/* prototypes for our stdio wrapper functions */
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);
FILE	*Popen(const char *, const char *);
int		 Pclose(FILE *);

#ifdef	HAVE_FATTACH
void	 Fattach(int, const char *);
#endif
#ifdef	HAVE_POLL
int		 Poll(struct pollfd *, unsigned long, int);
#endif

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

			/* prototypes for our pthread wrapper functions */
void	 Pthread_attr_init(pthread_attr_t *);
void	 Pthread_attr_destroy(pthread_attr_t *);
void	 Pthread_attr_setdetachstate(pthread_attr_t *, int);
void	 Pthread_attr_setscope(pthread_attr_t *, int);
void	 Pthread_create(pthread_t *, const pthread_attr_t *,
					    void * (*)(void *), void *);
void	 Pthread_join(pthread_t, void **);
void	 Pthread_detach(pthread_t);
void	 Pthread_kill(pthread_t, int);
void	 Pthread_setcancelstate(int, int *);

void	 Pthread_mutexattr_init(pthread_mutexattr_t *);
void	 Pthread_mutexattr_destroy(pthread_mutexattr_t *);
void	 Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void	 Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void	 Pthread_mutex_destroy(pthread_mutex_t *);
void	 Pthread_mutex_lock(pthread_mutex_t *);
void	 Pthread_mutex_unlock(pthread_mutex_t *);

void	 Pthread_condattr_init(pthread_condattr_t *);
void	 Pthread_condattr_destroy(pthread_condattr_t *);
void	 Pthread_condattr_setpshared(pthread_condattr_t *, int);
void	 Pthread_cond_broadcast(pthread_cond_t *);
void	 Pthread_cond_signal(pthread_cond_t *);
void	 Pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
void	 Pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *,
							    const struct timespec *);

void	 Pthread_key_create(pthread_key_t *, void (*)(void *));
void	 Pthread_setspecific(pthread_key_t, const void *);
void	 Pthread_once(pthread_once_t *, void (*)(void));
long	 pr_thread_id(pthread_t *);

#ifdef	HAVE_DOOR_H
			/* typedefs to simplify declarations */
typedef	void  Door_server_proc(void *, char *, size_t, door_desc_t *, size_t);
typedef	void  Door_create_proc(door_info_t *);

			/* prototypes for our doors wrapper functions */

void	 Door_bind(int);
void	 Door_call(int, door_arg_t *);
int		 Door_create(Door_server_proc *, void *, u_int);
void	 Door_cred(door_cred_t *);
void	 Door_info(int, door_info_t *);
void	 Door_return(char *, size_t, door_desc_t *, size_t);
void	 Door_revoke(int);
void	 Door_unbind(void);
Door_create_proc	*Door_server_create(Door_create_proc *);
#endif	/* HAVE_DOOR_H */

#ifdef	HAVE_RPC_RPC_H
CLIENT	*Clnt_create(const char *, u_long, u_long, const char *);
void	 Clnt_control(CLIENT *, u_int, char *);
#endif

#endif /* __unpipc_h */

