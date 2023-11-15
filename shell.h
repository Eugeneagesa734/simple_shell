#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>


/*Read and write buffers*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*cmd chaining*/
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/*converting numbers*/
#define CONVERT_LOWERCASE
#define CONVERT_UNSIGNED

/*for system using GETLINE()*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: string
 * @next: next node pointer
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}list_t;

typedef int (*builtin_func_t)(void *);

/* struct info - contains information for the shell */

/*
 * @arg: an argument-containing string produced by getline
 * @argv: a string of arrays generated from arg
 * @path: currect command string command
 * @user_input: gets the command the user inputs
 * @argc: argument count
 * @line_count: counts the error
 * @fname: programs file name
 * @fd: 
 * @histcount: history line number count
 * @cmd_buf: pointer address to the cmd_buf on if chaining
 * @cmd_buf_type: CMD_type ||, &&,
 * @history: History node
 * @status: status of the last exec'd command is returned
 * @liststr *env: environment in interactive mode
 * @liststr *alias: List alias node
 * @liststr *environ: environment in non_interactive mode
 * @readfd: The fd from which the line input is read
 * @str: string of character user inputs
 * @liststr *next: next string
 * */
typedef struct info {
  char *arg;
  char **argv;
  char *path;
  char* user_input;
  int argc;
  unsigned int line_count;
  int err_num;
  int linecount_flag;
 char *fname;
  int fd;
  int histcount;
  char **cmd_buf;
  int cmd_buf_type;
  list_t *history;
  int status;
  struct liststr *env;
  struct liststr *alias;
  struct liststr *environ;
  int readfd;
  char *str;
  struct liststr *next;
}info_t;


#define INFO_INIT {NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL, 0, 0, NULL, 0, NULL, 0, NULL, NULL, NULL, 0, NULL, NULL}


typedef struct {
    const char *type;
    int (*func)(info_t *info);
} builtin_table;



int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myenv(info_t *info);
int _myhistory(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int _myalias(info_t *info);

char **get_environ(info_t *info);

void free_list(list_t **head);


void _eputs(const char *str);
void _eputchar(char c);
void populate_env_list(info_t *info);
int _strlen(const char *s);
int _erratoi(const char *str);
void print_error(struct info *info, const char *message);
int _strcmp(const char *s1, const char *s2);


void clear_info(info_t *info);
int interactive(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int status);
int is_delim(char c, const char *delim);

char** strtow(const char *str, const char *delimiters);
char* _strdup(const char *s);
void replace_alias(struct info *info);
void replace_vars(struct info *info);

void free_argv(char **argv);
struct liststr *convert_to_liststr(char **argv);
void ffree(struct liststr *ptr);

void free_list(struct liststr **head);

/* function prototypes */
int hsh(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* char input*/
ssize_t get_input(info_t *info);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(int);

/*additional prototypes for functions with implict declaration issues*/
ssize_t remove_comments(char *buf);
void _putchar(char c);
void check_chain(info_t *info, char *buf, size_t *j, size_t i, size_t len);
int is_chain(info_t *info, char *buf, size_t *j);
void _puts(const char *str);

/*exit.c prototypes */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_getenv(info_t *info, const char *name);
void _putsfd(const char *str, int fd);
void _putfd(char c, int fd);
void delete_node_at_index(list_t **head, unsigned int index);
void add_node_end(list_t **head, const char *str, int num);

/*history.c prototypes*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

/*builtin.c prototypes*/
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);


/*memory.c prototypes*/
int bfree(void **);

/*parse.c prototypes*/
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/*loops.c prototypes*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*get_info.c prototypes*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

#endif
