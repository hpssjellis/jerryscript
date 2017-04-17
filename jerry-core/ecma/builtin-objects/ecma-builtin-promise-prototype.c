/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ecma-exceptions.h"
#include "ecma-globals.h"
#include "ecma-helpers.h"
#include "ecma-promise-object.h"

#ifndef CONFIG_DISABLE_ES2015_PROMISE_BUILTIN

#define ECMA_BUILTINS_INTERNAL
#include "ecma-builtins-internal.h"

#define BUILTIN_INC_HEADER_NAME "ecma-builtin-promise-prototype.inc.h"
#define BUILTIN_UNDERSCORED_ID promise_prototype
#include "ecma-builtin-internal-routines-template.inc.h"

/** \addtogroup ecma ECMA
 * @{
 *
 * \addtogroup ecmabuiltins
 * @{
 *
 * \addtogroup promiseprototype ECMA Promise.prototype object built-in
 * @{
 */

/**
 * Promise routine: then.
 *
 * See also: 25.4.5.3
 *
 * @return ecma value of a new promise object
 *         Returned value must be freed with ecma_free_value
 */
static ecma_value_t
ecma_builtin_promise_prototype_then (ecma_value_t this_arg, /**< this argument */
                                     ecma_value_t on_fulfilled, /**< on_fulfilled function */
                                     ecma_value_t on_rejected) /**< on_rejected function */
{
  ecma_object_t *obj = ecma_get_object_from_value (this_arg);

  if (!ecma_is_promise (obj))
  {
    return ecma_raise_type_error (ECMA_ERR_MSG ("'this' is not a Promise."));
  }

  ecma_value_t result_capability = ecma_promise_new_capability ();

  if (ECMA_IS_VALUE_ERROR (result_capability))
  {
    return result_capability;
  }

  ecma_value_t ret = ecma_promise_then (this_arg, on_fulfilled, on_rejected, result_capability);
  ecma_free_value (result_capability);

  return ret;
} /* ecma_builtin_promise_prototype_then */

/**
 * @}
 * @}
 * @}
 */

#endif /* !CONFIG_DISABLE_ES2015_PROMISE_BUILTIN */