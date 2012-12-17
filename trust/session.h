/*
 * Copyright (C) 2012 Red Hat Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the
 *       above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or
 *       other materials provided with the distribution.
 *     * The names of contributors to this software may not be
 *       used to endorse or promote products derived from this
 *       software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * Author: Stef Walter <stefw@redhat.com>
 */

#include "pkcs11.h"
#include "token.h"

#ifndef P11_SESSION_H_
#define P11_SESSION_H_

typedef void (* p11_session_cleanup) (void *data);

typedef struct {
	CK_SESSION_HANDLE handle;
	p11_dict *objects;
	p11_token *token;
	CK_BBOOL loaded;

	/* Used by various operations */
	p11_session_cleanup cleanup;
	void *operation;
} p11_session;

p11_session *     p11_session_new           (p11_token *token);

void              p11_session_free          (void *data);

CK_RV             p11_session_add_object    (p11_session *session,
                                             CK_ATTRIBUTE *attrs,
                                             CK_OBJECT_HANDLE *handle);

CK_RV             p11_session_del_object    (p11_session *session,
                                             CK_OBJECT_HANDLE handle);

CK_ATTRIBUTE *    p11_session_get_object    (p11_session *session,
                                             CK_OBJECT_HANDLE handle,
                                             CK_BBOOL *token);

CK_RV             p11_session_set_object    (p11_session *session,
                                             CK_OBJECT_HANDLE handle,
                                             CK_ATTRIBUTE *template,
                                             CK_ULONG count);

void              p11_session_set_operation (p11_session *session,
                                             p11_session_cleanup cleanup,
                                             void *operation);

#endif /* P11_SESSION_H_ */