/* crypto/bio/bio.h */
/* Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#ifndef HEADER_BIO_H
#define HEADER_BIO_H

#ifdef  __cplusplus
extern "C" {
#endif

/* These are the 'types' of BIOs */
#define BIO_TYPE_NONE		0
#define BIO_TYPE_MEM		(1|0x0400)
#define BIO_TYPE_FILE		(2|0x0400)

#define BIO_TYPE_FD		(4|0x0400|0x0100)
#define BIO_TYPE_SOCKET		(5|0x0400|0x0100)
#define BIO_TYPE_NULL		(6|0x0400)
#define BIO_TYPE_SSL		(7|0x0200)
#define BIO_TYPE_MD		(8|0x0200)		/* pasive filter */
#define BIO_TYPE_BUFFER		(9|0x0200)		/* filter */
#define BIO_TYPE_CIPHER		(10|0x0200)		/* filter */
#define BIO_TYPE_BASE64		(11|0x0200)		/* filter */
#define BIO_TYPE_CONNECT	(12|0x0400|0x0100)	/* socket - connect */
#define BIO_TYPE_ACCEPT		(13|0x0400|0x0100)	/* socket for accept */
#define BIO_TYPE_PROXY_CLIENT	(14|0x0400)		/* client proxy BIO */
#define BIO_TYPE_PROXY_SERVER	(15|0x0200)		/* server proxy BIO */
#define BIO_TYPE_NBIO_TEST	(16|0x0200)		/* server proxy BIO */
#define BIO_TYPE_NULL_FILTER	(17|0x0200)

#define BIO_TYPE_DESCRIPTOR	0x0100	/* socket, fd, connect or accept */
#define BIO_TYPE_FILTER		0x0200
#define BIO_TYPE_SOURCE_SINK	0x0400

/* BIO_FILENAME_READ|BIO_CLOSE to open or close on free.
 * BIO_set_fp(in,stdin,BIO_NOCLOSE); */
#define BIO_NOCLOSE		0x00
#define BIO_CLOSE		0x01

/* These are used in the following macros and are passed to
 * BIO_ctrl() */
#define BIO_CTRL_RESET		1  /* opt - rewind/zero etc */
#define BIO_CTRL_EOF		2  /* opt - are we at the eof */
#define BIO_CTRL_INFO		3  /* opt - extra tit-bits */
#define BIO_CTRL_SET		4  /* man - set the 'IO' type */
#define BIO_CTRL_GET		5  /* man - get the 'IO' type */
#define BIO_CTRL_PUSH		6  /* opt - internal, used to signify change */
#define BIO_CTRL_POP		7  /* opt - internal, used to signify change */
#define BIO_CTRL_GET_CLOSE	8  /* man - set the 'close' on free */
#define BIO_CTRL_SET_CLOSE	9  /* man - set the 'close' on free */
#define BIO_CTRL_PENDING	10  /* opt - is their more data buffered */
#define BIO_CTRL_FLUSH		11  /* opt - 'flush' buffered output */
#define BIO_CTRL_DUP		12  /* man - extra stuff for 'duped' BIO */
#define BIO_CTRL_WPENDING	13  /* opt - number of bytes still to write */

#define BIO_CTRL_SET_FILENAME	30	/* BIO_s_file special */

/* modifiers */
#define BIO_FP_READ		0x02
#define BIO_FP_WRITE		0x04
#define BIO_FP_APPEND		0x08
#define BIO_FP_TEXT		0x10

#define BIO_FLAGS_READ		0x01
#define BIO_FLAGS_WRITE		0x02
#define BIO_FLAGS_IO_SPECIAL	0x04
#define BIO_FLAGS_RWS (BIO_FLAGS_READ|BIO_FLAGS_WRITE|BIO_FLAGS_IO_SPECIAL)
#define BIO_FLAGS_SHOULD_RETRY	0x08

/* Mostly used in the SSL BIO */
#define BIO_FLAGS_PROTOCOL_DELAYED_READ 0x10
#define BIO_FLAGS_PROTOCOL_DELAYED_WRITE 0x20
#define BIO_FLAGS_PROTOCOL_STARTUP	0x40

#define BIO_set_flags(b,f) ((b)->flags|=(f))
#define BIO_set_retry_special(b) \
		((b)->flags|=(BIO_FLAGS_IO_SPECIAL|BIO_FLAGS_SHOULD_RETRY))
#define BIO_set_retry_read(b) \
		((b)->flags|=(BIO_FLAGS_READ|BIO_FLAGS_SHOULD_RETRY))
#define BIO_set_retry_write(b) \
		((b)->flags|=(BIO_FLAGS_WRITE|BIO_FLAGS_SHOULD_RETRY))

/* These are normally used internally in BIOs */
#define BIO_clear_flags(b,f) ((b)->flags&= ~(f))
#define BIO_clear_retry_flags(b) \
		((b)->flags&= ~(BIO_FLAGS_RWS|BIO_FLAGS_SHOULD_RETRY))
#define BIO_get_retry_flags(b) \
		((b)->flags&(BIO_FLAGS_RWS|BIO_FLAGS_SHOULD_RETRY))

/* These shouldbe used by the application to tell why we should retry */
#define BIO_should_read(a)		((a)->flags & BIO_FLAGS_READ)
#define BIO_should_write(a)		((a)->flags & BIO_FLAGS_WRITE)
#define BIO_should_io_special(a)	((a)->flags & BIO_FLAGS_IO_SPECIAL)
#define BIO_retry_type(a)		((a)->flags & BIO_FLAGS_RWS)
#define BIO_should_retry(a)		((a)->flags & BIO_FLAGS_SHOULD_RETRY)

/* The next two are used in conjunction with the
 * BIO_should_io_special() condition.  After this returns true,
 * BIO *BIO_get_retry_BIO(BIO *bio, int *reason); will walk the BIO 
 * stack and return the 'reason' for the special and the offending BIO.
 * Given a BIO, BIO_get_retry_reason(bio) will return the code. */
/* Returned from the SSL bio when the certificate retrieval code had an error */
#define BIO_RR_SSL_X509_LOOKUP		0x01
/* Returned from the connect BIO when a connect would have blocked */
#define BIO_RR_CONNECT			0x02

/* These are passed by the BIO callback */
#define BIO_CB_FREE	0x01
#define BIO_CB_READ	0x02
#define BIO_CB_WRITE	0x03
#define BIO_CB_PUTS	0x04
#define BIO_CB_GETS	0x05
#define BIO_CB_CTRL	0x06

/* The callback is called before and after the underling operation,
 * The BIO_CB_RETURN flag indicates if it is after the call */
#define BIO_CB_RETURN	0x80
#define BIO_CB_return(a) ((a)|BIO_CB_RETURN))
#define BIO_cb_pre(a)	(!((a)&BIO_CB_RETURN))
#define BIO_cb_post(a)	((a)&BIO_CB_RETURN)

#define BIO_set_callback(b,cb)		((b)->callback=(cb))
#define BIO_set_callback_arg(b,arg)	((b)->cb_arg=(char *)(arg))
#define BIO_get_callback_arg(b)		((b)->cb_arg)
#define BIO_get_callback(b)		((b)->callback)
#define BIO_method_name(b)		((b)->method->name)
#define BIO_method_type(b)		((b)->method->type)

#ifndef WIN16
typedef struct bio_method_st
	{
	int type;
	char *name;
	int (*bwrite)();
	int (*bread)();
	int (*bputs)();
	int (*bgets)();
	long (*ctrl)();
	int (*create)();
	int (*destroy)();
	} BIO_METHOD;
#else
typedef struct bio_method_st
	{
	int type;
	char *name;
	int (_far *bwrite)();
	int (_far *bread)();
	int (_far *bputs)();
	int (_far *bgets)();
	long (_far *ctrl)();
	int (_far *create)();
	int (_far *destroy)();
	} BIO_METHOD;
#endif

typedef struct bio_st
	{
	BIO_METHOD *method;
#ifndef NOPROTO
	/* bio, mode, argp, argi, argl, ret */
	long (*callback)(struct bio_st *,int,char *,int, long,long);
#else
	long (*callback)();
#endif
	char *cb_arg; /* first argument for the callback */

	int init;
	int shutdown;
	int flags;	/* extra storage */
	int retry_reason;
	int num;
	char *ptr;
	struct bio_st *next_bio;	/* used by filter BIOs */
	struct bio_st *prev_bio;	/* used by filter BIOs */
	int references;
	unsigned long num_read;
	unsigned long num_write;

	char *app_data;
	} BIO;

typedef struct bio_f_buffer_ctx_struct
	{
	/* BIO *bio; */ /* this is now in the BIO struct */
	int ibuf_size;	/* how big is the input buffer */
	int obuf_size;	/* how big is the output buffer */

	char *ibuf;		/* the char array */
	int ibuf_len;		/* how many bytes are in it */
	int ibuf_off;		/* write/read offset */

	char *obuf;		/* the char array */
	int obuf_len;		/* how many bytes are in it */
	int obuf_off;		/* write/read offset */
	} BIO_F_BUFFER_CTX;

#define BIO_number_read(b)	((b)->num_read)
#define BIO_number_written(b)	((b)->num_write)

#define BIO_C_SET_CONNECT			100
#define BIO_C_DO_STATE_MACHINE			101
#define BIO_C_SET_NBIO				102
#define BIO_C_SET_PROXY_PARAM			103
#define BIO_C_SET_FD				104
#define BIO_C_GET_FD				105
#define BIO_C_SET_FILE_PTR			106
#define BIO_C_GET_FILE_PTR			107
#define BIO_C_SET_FILENAME			108
#define BIO_C_SET_SSL				109
#define BIO_C_GET_SSL				110
#define BIO_C_SET_MD				111
#define BIO_C_GET_MD				112
#define BIO_C_GET_CIPHER_STATUS			113
#define BIO_C_SET_BUF_MEM			114
#define BIO_C_GET_BUF_MEM_PTR			115
#define BIO_C_GET_BUFF_NUM_LINES		116
#define BIO_C_SET_BUFF_SIZE			117
#define BIO_C_SET_ACCEPT			118
#define BIO_C_SSL_MODE				119
#define BIO_C_GET_MD_CTX			120
#define BIO_C_GET_PROXY_PARAM			121

#define BIO_set_app_data(s,arg)		((s)->app_data=(char *)arg)
#define BIO_get_app_data(s)		((s)->app_data)

/* BIO_s_connect_socket() */
#define BIO_set_hostname(b,name) BIO_ctrl(b,BIO_C_SET_CONNECT,0,(char *)name)
#define BIO_set_port(b,port)	BIO_ctrl(b,BIO_C_SET_CONNECT,1,(char *)port)
#define BIO_set_nbio(b,n)	BIO_ctrl(b,BIO_C_SET_NBIO,(n),NULL)

/* BIO_s_accept_socket() */
#define BIO_set_accept_port(b,name) BIO_ctrl(b,BIO_C_SET_ACCEPT,0,(char *)name)
/* #define BIO_set_nbio(b,n)	BIO_ctrl(b,BIO_C_SET_NBIO,(n),NULL) */
#define BIO_set_nbio_accpet(b,n) BIO_ctrl(b,BIO_C_SET_ACCEPT,1,(n)?"a":NULL)
#define BIO_set_accept_bios(b,bio) BIO_ctrl(b,BIO_C_SET_ACCEPT,2,(char *)bio)

#define BIO_do_connect(b)	BIO_do_handshake(b)
#define BIO_do_accept(b)	BIO_do_handshake(b)
#define BIO_do_handshake(b)	BIO_ctrl(b,BIO_C_DO_STATE_MACHINE,0,NULL)

/* BIO_s_proxy_client() */
#define BIO_set_url(b,url)	BIO_ctrl(b,BIO_C_SET_PROXY_PARAM,0,(char *)(url))
#define BIO_set_proxies(b,p)	BIO_ctrl(b,BIO_C_SET_PROXY_PARAM,1,(char *)(p))
/* BIO_set_nbio(b,n) */
#define BIO_set_filter_bio(b,s) BIO_ctrl(b,BIO_C_SET_PROXY_PARAM,2,(char *)(s))
/* BIO *BIO_get_filter_bio(BIO *bio); */
#define BIO_set_proxy_cb(b,cb) BIO_ctrl(b,BIO_C_SET_PROXY_PARAM,3,(char *)(cb))
#define BIO_set_proxy_header(b,sk) BIO_ctrl(b,BIO_C_SET_PROXY_PARAM,4,(char *)sk)

#define BIO_get_proxy_header(b,skp) BIO_ctrl(b,BIO_C_GET_PROXY_PARAM,0,(char *)skp)
#define BIO_get_proxies(b,pxy_p) BIO_ctrl(b,BIO_C_GET_PROXY_PARAM,1,(char *)(pxy_p))
#define BIO_get_url(b,url)	BIO_ctrl(b,BIO_C_GET_PROXY_PARAM,2,(char *)(url))

#define BIO_set_fd(b,fd,c)	BIO_ctrl_int(b,BIO_C_SET_FD,c,fd)
#define BIO_get_fd(b,c)		BIO_ctrl(b,BIO_C_GET_FD,0,(char *)c)

#define BIO_set_fp(b,fp,c)	BIO_ctrl(b,BIO_C_SET_FILE_PTR,c,(char *)fp)
#define BIO_get_fp(b,fpp)	BIO_ctrl(b,BIO_C_GET_FILE_PTR,0,(char *)fpp)

#define BIO_read_filename(b,name) BIO_ctrl(b,BIO_C_SET_FILENAME, \
		BIO_CLOSE|BIO_FP_READ,name)
#define BIO_write_filename(b,name) BIO_ctrl(b,BIO_C_SET_FILENAME, \
		BIO_CLOSE|BIO_FP_WRITE,name)
#define BIO_append_filename(b,name) BIO_ctrl(b,BIO_C_SET_FILENAME, \
		BIO_CLOSE|BIO_FP_APPEND,name)

#define BIO_set_ssl(b,ssl,c)	BIO_ctrl(b,BIO_C_SET_SSL,c,(char *)ssl)
#define BIO_get_ssl(b,sslp)	BIO_ctrl(b,BIO_C_GET_SSL,0,(char *)sslp)
#define BIO_set_ssl_mode(b,client)	BIO_ctrl(b,BIO_C_SSL_MODE,client,NULL)

/* defined in evp.h */
/* #define BIO_set_md(b,md)	BIO_ctrl(b,BIO_C_SET_MD,1,(char *)md) */

#define BIO_set_mem_buf(b,bm,c)	BIO_ctrl(b,BIO_C_SET_BUF_MEM,c,(char *)bm)
#define BIO_get_mem_ptr(b,pp)	BIO_ctrl(b,BIO_C_GET_BUF_MEM_PTR,0,(char *)pp)

/* For the BIO_f_buffer() type */
#define BIO_get_buffer_num_lines(b)	BIO_ctrl(b,BIO_C_GET_BUFF_NUM_LINES,0,NULL)
#define BIO_set_buffer_size(b,size)	BIO_ctrl(b,BIO_C_SET_BUFF_SIZE,size,NULL)
#define BIO_set_read_buffer_size(b,size) BIO_ctrl_int(b,BIO_C_SET_BUFF_SIZE,size,0)
#define BIO_set_write_buffer_size(b,size) BIO_ctrl_int(b,BIO_C_SET_BUFF_SIZE,size,1)

/* Don't use the next one unless you know what you are doing :-) */
#define BIO_dup_state(b,ret)	BIO_ctrl(b,BIO_CTRL_DUP,0,(char *)ret)

#define BIO_reset(b)		(int)BIO_ctrl(b,BIO_CTRL_RESET,0,NULL)
#define BIO_eof(b)		(int)BIO_ctrl(b,BIO_CTRL_EOF,0,NULL)
#define BIO_set_close(b,c)	(int)BIO_ctrl(b,BIO_CTRL_SET_CLOSE,(c),NULL)
#define BIO_get_close(b)	(int)BIO_ctrl(b,BIO_CTRL_GET_CLOSE,0,NULL)
#define BIO_pending(b)		(int)BIO_ctrl(b,BIO_CTRL_PENDING,0,NULL)
#define BIO_wpending(b)		(int)BIO_ctrl(b,BIO_CTRL_WPENDING,0,NULL)
#define BIO_flush(b)		(int)BIO_ctrl(b,BIO_CTRL_FLUSH,0,NULL)

/* For the BIO_f_buffer() type */
#define BIO_buffer_get_num_lines(b) BIO_ctrl(b,BIO_CTRL_GET,0,NULL)

#ifndef NOPROTO
BIO *	BIO_new(BIO_METHOD *type);
int	BIO_set(BIO *a,BIO_METHOD *type);
int	BIO_free(BIO *a);
int	BIO_read(BIO *b, char *data, int len);
int	BIO_gets(BIO *bp,char *buf, int size);
int	BIO_write(BIO *b, char *data, int len);
int	BIO_puts(BIO *bp,char *buf);
long	BIO_ctrl(BIO *bp,int cmd,long larg,char *parg);
long	BIO_ctrl_int(BIO *bp,int cmd,long larg,int iarg);
BIO *	BIO_push(BIO *b,BIO *append);
BIO *	BIO_pop(BIO *b);
void	BIO_free_all(BIO *a);
BIO *	BIO_find_type(BIO *b,int bio_type);
BIO *	BIO_get_retry_BIO(BIO *bio, int *reason);
int	BIO_get_retry_reason(BIO *bio);
BIO *	BIO_dup_chain(BIO *in);

#ifndef WIN16
long BIO_debug_callback(BIO *bio,int cmd,char *argp,int argi,
	long argl,long ret);
#else
long _far _loadds BIO_debug_callback(BIO *bio,int cmd,char *argp,int argi,
	long argl,long ret);
#endif

#if !defined(WIN16) || defined(APPS_WIN16)
BIO_METHOD *BIO_s_file(void);
#else
BIO_METHOD *BIO_s_file_internal_w16(void);
#endif

BIO_METHOD *BIO_s_mem(void);
BIO_METHOD *BIO_s_socket(void);
BIO_METHOD *BIO_s_connect(void);
BIO_METHOD *BIO_s_accept(void);
BIO_METHOD *BIO_s_fd(void);
BIO_METHOD *BIO_s_null(void);
BIO_METHOD *BIO_f_null(void);
BIO_METHOD *BIO_f_nbio_test(void);
BIO_METHOD *BIO_f_buffer(void);

int BIO_sock_should_retry(int i);
int BIO_sock_non_fatal_error(int error);
int BIO_fd_should_retry(int i);
int BIO_fd_non_fatal_error(int error);
int BIO_dump(BIO *b,char *bytes,int len);

struct hostent *BIO_gethostbyname(char *name);
int BIO_sock_error(int sock);
int BIO_socket_ioctl(int fd, long type, unsigned long *arg);
int BIO_get_port(char *str, short *port_ptr);
int BIO_get_host_ip(char *str, unsigned char *ip);
int BIO_get_accept_socket(char *host_port);
int BIO_accept(int sock,char **ip_port);
int BIO_sock_init(void );
void BIO_sock_cleanup(void);
int BIO_set_tcp_ndelay(int sock,int turn_on);

void ERR_load_BIO_strings(void );

#if !defined(WIN16) || defined(APPS_WIN16)
BIO *BIO_new_file(char *filename, char *mode);
BIO *BIO_new_fp(FILE *stream, int close_flag);
#endif
BIO *BIO_new_socket(int sock, int close_flag);
BIO *BIO_new_fd(int fd, int close_flag);
BIO *BIO_new_connect(char *host_port);
BIO *BIO_new_accept(char *host_port);

void BIO_copy_next_retry(BIO *b);

#else

BIO *	BIO_new();
int	BIO_set();
int	BIO_free();
int	BIO_read();
int	BIO_gets();
int	BIO_write();
int	BIO_puts();
long	BIO_ctrl();
long	BIO_ctrl_int();
BIO *	BIO_push();
BIO *	BIO_pop();
void	BIO_free_all();
BIO *	BIO_find_type();
BIO *	BIO_get_retry_BIO();
int	BIO_get_retry_reason();
BIO *	BIO_dup_chain();

#ifndef WIN16
long BIO_debug_callback();
#else
long _far _loadds BIO_debug_callback();
#endif

#if !defined(WIN16) || defined(APPS_WIN16)
BIO_METHOD *BIO_s_file();
#else
BIO_METHOD *BIO_s_file_internal_w16();
#endif

BIO_METHOD *BIO_s_mem();
BIO_METHOD *BIO_s_socket();
BIO_METHOD *BIO_s_connect();
BIO_METHOD *BIO_s_accept();
BIO_METHOD *BIO_s_fd();
BIO_METHOD *BIO_s_null();
BIO_METHOD *BIO_f_null();
BIO_METHOD *BIO_f_buffer();
BIO_METHOD *BIO_f_nbio_test();

int BIO_sock_should_retry();
int BIO_sock_non_fatal_error();
int BIO_fd_should_retry();
int BIO_fd_non_fatal_error();
int BIO_dump();

struct hostent *BIO_gethostbyname();
int BIO_sock_error();
int BIO_socket_ioctl();
int BIO_get_port();
int BIO_get_host_ip();
int BIO_get_accept_socket();
int BIO_accept();
int BIO_sock_init();
void BIO_sock_cleanup();
int BIO_set_tcp_ndelay();

void ERR_load_BIO_strings();

#if !defined(WIN16) || defined(APPS_WIN16)
BIO *BIO_new_file();
BIO *BIO_new_fp();
#endif
BIO *BIO_new_socket();
BIO *BIO_new_fd();
BIO *BIO_new_connect();
BIO *BIO_new_accept();

void BIO_copy_next_retry();

#endif

/* Tim Hudson's portable varargs stuff */

#ifndef NOPROTO
#define VAR_ANSI	/* select ANSI version by default */
#endif

#ifdef VAR_ANSI
/* ANSI version of a "portable" macro set for variable length args */
#ifndef __STDARG_H__ /**/
#include <stdarg.h>
#endif /**/

#define VAR_PLIST(arg1type,arg1)    arg1type arg1, ...
#define VAR_PLIST2(arg1type,arg1,arg2type,arg2) arg1type arg1,arg2type arg2,...
#define VAR_ALIST
#define VAR_BDEFN(args,arg1type,arg1)   va_list args
#define VAR_BDEFN2(args,arg1type,arg1,arg2type,arg2)    va_list args
#define VAR_INIT(args,arg1type,arg1)    va_start(args,arg1);
#define VAR_INIT2(args,arg1type,arg1,arg2type,arg2) va_start(args,arg2);
#define VAR_ARG(args,type,arg)	arg=va_arg(args,type)
#define VAR_END(args)		va_end(args);

#else

/* K&R version of a "portable" macro set for variable length args */
#ifndef __VARARGS_H__
#include <varargs.h>
#endif

#define VAR_PLIST(arg1type,arg1)	va_alist
#define VAR_PLIST2(arg1type,arg1,arg2type,arg2) va_alist
#define VAR_ALIST		va_dcl
#define VAR_BDEFN(args,arg1type,arg1)	va_list args; arg1type arg1
#define VAR_BDEFN2(args,arg1type,arg1,arg2type,arg2)    va_list args; \
	arg1type arg1; arg2type arg2
#define VAR_INIT(args,arg1type,arg1)	va_start(args); \
	arg1=va_arg(args,arg1type);
#define VAR_INIT2(args,arg1type,arg1,arg2type,arg2) va_start(args); \
	arg1=va_arg(args,arg1type);	arg2=va_arg(args,arg2type);
#define VAR_ARG(args,type,arg)		arg=va_arg(args,type)
#define VAR_END(args)			va_end(args);

#endif

#ifndef NOPROTO
int BIO_printf( VAR_PLIST( BIO *, bio ) );
#else
int BIO_printf();
#endif

/* BEGIN ERROR CODES */
/* Error codes for the BIO functions. */

/* Function codes. */
#define BIO_F_ACPT_STATE				 100
#define BIO_F_BIO_ACCEPT				 101
#define BIO_F_BIO_CTRL					 102
#define BIO_F_BIO_GETS					 103
#define BIO_F_BIO_GET_ACCEPT_SOCKET			 104
#define BIO_F_BIO_GET_HOST_IP				 105
#define BIO_F_BIO_GET_PORT				 106
#define BIO_F_BIO_NEW					 107
#define BIO_F_BIO_NEW_FILE				 108
#define BIO_F_BIO_PUTS					 109
#define BIO_F_BIO_READ					 110
#define BIO_F_BIO_SOCK_INIT				 111
#define BIO_F_BIO_WRITE					 112
#define BIO_F_CONN_STATE				 113
#define BIO_F_FILE_CTRL					 114
#define BIO_F_MEM_WRITE					 115
#define BIO_F_WSASTARTUP				 116

/* Reason codes. */
#define BIO_R_ACCEPT_ERROR				 100
#define BIO_R_BAD_FOPEN_MODE				 101
#define BIO_R_BAD_HOSTNAME_LOOKUP			 102
#define BIO_R_CONNECT_ERROR				 103
#define BIO_R_ERROR_SETTING_NBIO			 104
#define BIO_R_ERROR_SETTING_NBIO_ON_ACCEPTED_SOCKET	 105
#define BIO_R_ERROR_SETTING_NBIO_ON_ACCEPT_SOCKET	 106
#define BIO_R_GETHOSTBYNAME_ADDR_IS_NOT_AF_INET		 107
#define BIO_R_INVALID_IP_ADDRESS			 108
#define BIO_R_NBIO_CONNECT_ERROR			 109
#define BIO_R_NO_ACCEPT_PORT_SPECIFIED			 110
#define BIO_R_NO_HOSTHNAME_SPECIFIED			 111
#define BIO_R_NO_PORT_DEFINED				 112
#define BIO_R_NO_PORT_SPECIFIED				 113
#define BIO_R_NULL_PARAMETER				 114
#define BIO_R_UNABLE_TO_BIND_SOCKET			 115
#define BIO_R_UNABLE_TO_CREATE_SOCKET			 116
#define BIO_R_UNABLE_TO_LISTEN_SOCKET			 117
#define BIO_R_UNINITALISED				 118
#define BIO_R_UNSUPPORTED_METHOD			 119
#define BIO_R_WSASTARTUP				 120
 
#ifdef  __cplusplus
}
#endif
#endif

