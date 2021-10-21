﻿/* ====================================================================
 * Copyright (c) 2014 - 2017 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

#include "sm4_lcl.h"


const uint8_t SM4_S[256] = {
	0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7,
	0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05,
	0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3,
	0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
	0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a,
	0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62,
	0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95,
	0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6,
	0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba,
	0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8,
	0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b,
	0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35,
	0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2,
	0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87,
	0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52,
	0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e,
	0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5,
	0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1,
	0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55,
	0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3,
	0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60,
	0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f,
	0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f,
	0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51,
	0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f,
	0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8,
	0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd,
	0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0,
	0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e,
	0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84,
	0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20,
	0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48,
};

const uint32_t SM4_T[256] = {
	0x8ed55b5bU, 0xd0924242U, 0x4deaa7a7U, 0x06fdfbfbU,
	0xfccf3333U, 0x65e28787U, 0xc93df4f4U, 0x6bb5dedeU,
	0x4e165858U, 0x6eb4dadaU, 0x44145050U, 0xcac10b0bU,
	0x8828a0a0U, 0x17f8efefU, 0x9c2cb0b0U, 0x11051414U,
	0x872bacacU, 0xfb669d9dU, 0xf2986a6aU, 0xae77d9d9U,
	0x822aa8a8U, 0x46bcfafaU, 0x14041010U, 0xcfc00f0fU,
	0x02a8aaaaU, 0x54451111U, 0x5f134c4cU, 0xbe269898U,
	0x6d482525U, 0x9e841a1aU, 0x1e061818U, 0xfd9b6666U,
	0xec9e7272U, 0x4a430909U, 0x10514141U, 0x24f7d3d3U,
	0xd5934646U, 0x53ecbfbfU, 0xf89a6262U, 0x927be9e9U,
	0xff33ccccU, 0x04555151U, 0x270b2c2cU, 0x4f420d0dU,
	0x59eeb7b7U, 0xf3cc3f3fU, 0x1caeb2b2U, 0xea638989U,
	0x74e79393U, 0x7fb1ceceU, 0x6c1c7070U, 0x0daba6a6U,
	0xedca2727U, 0x28082020U, 0x48eba3a3U, 0xc1975656U,
	0x80820202U, 0xa3dc7f7fU, 0xc4965252U, 0x12f9ebebU,
	0xa174d5d5U, 0xb38d3e3eU, 0xc33ffcfcU, 0x3ea49a9aU,
	0x5b461d1dU, 0x1b071c1cU, 0x3ba59e9eU, 0x0cfff3f3U,
	0x3ff0cfcfU, 0xbf72cdcdU, 0x4b175c5cU, 0x52b8eaeaU,
	0x8f810e0eU, 0x3d586565U, 0xcc3cf0f0U, 0x7d196464U,
	0x7ee59b9bU, 0x91871616U, 0x734e3d3dU, 0x08aaa2a2U,
	0xc869a1a1U, 0xc76aadadU, 0x85830606U, 0x7ab0cacaU,
	0xb570c5c5U, 0xf4659191U, 0xb2d96b6bU, 0xa7892e2eU,
	0x18fbe3e3U, 0x47e8afafU, 0x330f3c3cU, 0x674a2d2dU,
	0xb071c1c1U, 0x0e575959U, 0xe99f7676U, 0xe135d4d4U,
	0x661e7878U, 0xb4249090U, 0x360e3838U, 0x265f7979U,
	0xef628d8dU, 0x38596161U, 0x95d24747U, 0x2aa08a8aU,
	0xb1259494U, 0xaa228888U, 0x8c7df1f1U, 0xd73bececU,
	0x05010404U, 0xa5218484U, 0x9879e1e1U, 0x9b851e1eU,
	0x84d75353U, 0x00000000U, 0x5e471919U, 0x0b565d5dU,
	0xe39d7e7eU, 0x9fd04f4fU, 0xbb279c9cU, 0x1a534949U,
	0x7c4d3131U, 0xee36d8d8U, 0x0a020808U, 0x7be49f9fU,
	0x20a28282U, 0xd4c71313U, 0xe8cb2323U, 0xe69c7a7aU,
	0x42e9ababU, 0x43bdfefeU, 0xa2882a2aU, 0x9ad14b4bU,
	0x40410101U, 0xdbc41f1fU, 0xd838e0e0U, 0x61b7d6d6U,
	0x2fa18e8eU, 0x2bf4dfdfU, 0x3af1cbcbU, 0xf6cd3b3bU,
	0x1dfae7e7U, 0xe5608585U, 0x41155454U, 0x25a38686U,
	0x60e38383U, 0x16acbabaU, 0x295c7575U, 0x34a69292U,
	0xf7996e6eU, 0xe434d0d0U, 0x721a6868U, 0x01545555U,
	0x19afb6b6U, 0xdf914e4eU, 0xfa32c8c8U, 0xf030c0c0U,
	0x21f6d7d7U, 0xbc8e3232U, 0x75b3c6c6U, 0x6fe08f8fU,
	0x691d7474U, 0x2ef5dbdbU, 0x6ae18b8bU, 0x962eb8b8U,
	0x8a800a0aU, 0xfe679999U, 0xe2c92b2bU, 0xe0618181U,
	0xc0c30303U, 0x8d29a4a4U, 0xaf238c8cU, 0x07a9aeaeU,
	0x390d3434U, 0x1f524d4dU, 0x764f3939U, 0xd36ebdbdU,
	0x81d65757U, 0xb7d86f6fU, 0xeb37dcdcU, 0x51441515U,
	0xa6dd7b7bU, 0x09fef7f7U, 0xb68c3a3aU, 0x932fbcbcU,
	0x0f030c0cU, 0x03fcffffU, 0xc26ba9a9U, 0xba73c9c9U,
	0xd96cb5b5U, 0xdc6db1b1U, 0x375a6d6dU, 0x15504545U,
	0xb98f3636U, 0x771b6c6cU, 0x13adbebeU, 0xda904a4aU,
	0x57b9eeeeU, 0xa9de7777U, 0x4cbef2f2U, 0x837efdfdU,
	0x55114444U, 0xbdda6767U, 0x2c5d7171U, 0x45400505U,
	0x631f7c7cU, 0x50104040U, 0x325b6969U, 0xb8db6363U,
	0x220a2828U, 0xc5c20707U, 0xf531c4c4U, 0xa88a2222U,
	0x31a79696U, 0xf9ce3737U, 0x977aededU, 0x49bff6f6U,
	0x992db4b4U, 0xa475d1d1U, 0x90d34343U, 0x5a124848U,
	0x58bae2e2U, 0x71e69797U, 0x64b6d2d2U, 0x70b2c2c2U,
	0xad8b2626U, 0xcd68a5a5U, 0xcb955e5eU, 0x624b2929U,
	0x3c0c3030U, 0xce945a5aU, 0xab76ddddU, 0x867ff9f9U,
	0xf1649595U, 0x5dbbe6e6U, 0x35f2c7c7U, 0x2d092424U,
	0xd1c61717U, 0xd66fb9b9U, 0xdec51b1bU, 0x94861212U,
	0x78186060U, 0x30f3c3c3U, 0x897cf5f5U, 0x5cefb3b3U,
	0xd23ae8e8U, 0xacdf7373U, 0x794c3535U, 0xa0208080U,
	0x9d78e5e5U, 0x56edbbbbU, 0x235e7d7dU, 0xc63ef8f8U,
	0x8bd45f5fU, 0xe7c82f2fU, 0xdd39e4e4U, 0x68492121U,
};

