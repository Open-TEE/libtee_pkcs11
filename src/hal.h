/*****************************************************************************
** Copyright (C) 2015 Intel Corporation.                                    **
**                                                                          **
** Licensed under the Apache License, Version 2.0 (the "License");          **
** you may not use this file except in compliance with the License.         **
** You may obtain a copy of the License at                                  **
**                                                                          **
**      http://www.apache.org/licenses/LICENSE-2.0                          **
**                                                                          **
** Unless required by applicable law or agreed to in writing, software      **
** distributed under the License is distributed on an "AS IS" BASIS,        **
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. **
** See the License for the specific language governing permissions and      **
** limitations under the License.                                           **
*****************************************************************************/

#ifndef __HAL_H_
#define __HAL_H_

#include "cryptoki.h"

/*!
 * \brief hal_initialize_context
 * Create a context towards the TEE, this is generally achieved by opening the TEE device
 * \param tee_context [OUT] The location to store the new context
 * \return 0 on success
 */
CK_RV hal_initialize_context(void **tee_context);

/*!
 * \brief hal_finalize_context
 * Close the connection to the TEE and free the context.
 * \param tee_context [IN] The context of the connection to close
 * \return 0 on success
 */
CK_RV hal_finalize_context(void *tee_context);

#endif // HAL_H
