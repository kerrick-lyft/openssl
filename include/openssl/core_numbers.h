/*
 * Copyright 2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OSSL_CORE_NUMBERS_H
# define OSSL_CORE_NUMBERS_H

# include <openssl/core.h>

# ifdef __cplusplus
extern "C" {
# endif

/*-
 * Identities
 * ----------
 *
 * All series start with 1, to allow 0 to be an array terminator.
 * For any FUNC identity, we also provide a function signature typedef
 * and a static inline function to extract a function pointer from a
 * OSSL_DISPATCH element in a type safe manner.
 *
 * Names:
 * for any function base name 'foo' (uppercase form 'FOO'), we will have
 * the following:
 * - a macro for the identity with the name OSSL_FUNC_'FOO' or derivates
 *   thereof (to be specified further down)
 * - a function signature typedef with the name OSSL_'foo'_fn
 * - a function pointer extractor function with the name OSSL_'foo'
 */

/* Helper macro to create the function signature typedef and the extractor */
#define OSSL_CORE_MAKE_FUNC(type,name,args)                             \
    typedef type (OSSL_##name##_fn)args;                                \
    static ossl_inline \
    OSSL_##name##_fn *OSSL_get_##name(const OSSL_DISPATCH *opf)         \
    {                                                                   \
        return (OSSL_##name##_fn *)opf->function;                       \
    }

/*
 * Core function identities, for the two OSSL_DISPATCH tables being passed
 * in the OSSL_provider_init call.
 *
 * 0 serves as a marker for the end of the OSSL_DISPATCH array, and must
 * therefore NEVER be used as a function identity.
 */
/* Functions provided by the Core to the provider, reserved numbers 1-1023 */
# define OSSL_FUNC_CORE_GET_PARAM_TYPES        1
OSSL_CORE_MAKE_FUNC(const OSSL_ITEM *,
                    core_get_param_types,(const OSSL_PROVIDER *prov))
# define OSSL_FUNC_CORE_GET_PARAMS             2
OSSL_CORE_MAKE_FUNC(int,core_get_params,(const OSSL_PROVIDER *prov,
                                         const OSSL_PARAM params[]))

/* Functions provided by the provider to the Core, reserved numbers 1024-1535 */
# define OSSL_FUNC_PROVIDER_TEARDOWN         1024
OSSL_CORE_MAKE_FUNC(void,provider_teardown,(void))
# define OSSL_FUNC_PROVIDER_GET_PARAM_TYPES  1025
OSSL_CORE_MAKE_FUNC(const OSSL_ITEM *,
                    provider_get_param_types,(const OSSL_PROVIDER *prov))
# define OSSL_FUNC_PROVIDER_GET_PARAMS       1026
OSSL_CORE_MAKE_FUNC(int,provider_get_params,(const OSSL_PROVIDER *prov,
                                             const OSSL_PARAM params[]))


# ifdef __cplusplus
}
# endif

#endif
