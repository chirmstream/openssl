/* crypto/evp/c_all.c */
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

#include <stdio.h>
#include "cryptlib.h"
#include "evp.h"
#include "objects.h"

void SSLeay_add_all_algorithms()
	{
	SSLeay_add_all_ciphers();
	SSLeay_add_all_digests();
	}

void SSLeay_add_all_ciphers()
	{
#ifndef NO_DES
	EVP_add_cipher(EVP_des_cfb());
	EVP_add_cipher(EVP_des_ede_cfb());
	EVP_add_cipher(EVP_des_ede3_cfb());

	EVP_add_cipher(EVP_des_ofb());
	EVP_add_cipher(EVP_des_ede_ofb());
	EVP_add_cipher(EVP_des_ede3_ofb());

	EVP_add_cipher(EVP_desx_cbc());
	EVP_add_alias(SN_desx_cbc,"DESX");
	EVP_add_alias(SN_desx_cbc,"desx");

	EVP_add_cipher(EVP_des_cbc());
	EVP_add_alias(SN_des_cbc,"DES");
	EVP_add_alias(SN_des_cbc,"des");
	EVP_add_cipher(EVP_des_ede_cbc());
	EVP_add_cipher(EVP_des_ede3_cbc());
	EVP_add_alias(SN_des_ede3_cbc,"DES3");
	EVP_add_alias(SN_des_ede3_cbc,"des3");

	EVP_add_cipher(EVP_des_ecb());
	EVP_add_cipher(EVP_des_ede());
	EVP_add_cipher(EVP_des_ede3());
#endif

#ifndef NO_RC4
	EVP_add_cipher(EVP_rc4());
#endif

#ifndef NO_IDEA
	EVP_add_cipher(EVP_idea_ecb());
	EVP_add_cipher(EVP_idea_cfb());
	EVP_add_cipher(EVP_idea_ofb());
	EVP_add_cipher(EVP_idea_cbc());
	EVP_add_alias(SN_idea_cbc,"IDEA");
	EVP_add_alias(SN_idea_cbc,"idea");
#endif

#ifndef NO_RC2
	EVP_add_cipher(EVP_rc2_ecb());
	EVP_add_cipher(EVP_rc2_cfb());
	EVP_add_cipher(EVP_rc2_ofb());
	EVP_add_cipher(EVP_rc2_cbc());
	EVP_add_alias(SN_rc2_cbc,"RC2");
	EVP_add_alias(SN_rc2_cbc,"rc2");
#endif

#ifndef NO_BLOWFISH
	EVP_add_cipher(EVP_bf_ecb());
	EVP_add_cipher(EVP_bf_cfb());
	EVP_add_cipher(EVP_bf_ofb());
	EVP_add_cipher(EVP_bf_cbc());
	EVP_add_alias(SN_bf_cbc,"BF");
	EVP_add_alias(SN_bf_cbc,"bf");
	EVP_add_alias(SN_bf_cbc,"blowfish");
#endif
	}


void SSLeay_add_all_digests()
	{
#ifndef NO_MD2
	EVP_add_digest(EVP_md2());
#endif
#ifndef NO_MD2
	EVP_add_digest(EVP_md5());
#endif
#ifndef NO_SHA
	EVP_add_digest(EVP_sha());
#ifndef NO_DSA
	EVP_add_digest(EVP_dss());
#endif
#endif
#ifndef NO_SHA1
	EVP_add_digest(EVP_sha1());
#ifndef NO_DSA
	EVP_add_digest(EVP_dss1());
#endif
#endif
#if !defined(NO_MDC2) && !defined(NO_DES)
	EVP_add_digest(EVP_mdc2());
#endif
	}
