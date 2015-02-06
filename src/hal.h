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

#include <stdint.h>
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

/*!
 * \brief hal_crypto_init
 * Initializes crypto operation at TEE
 * \param hSession
 * \param pMechanism
 * \param hKey
 * \return
 */
CK_RV hal_crypto_init(uint32_t command_id,
		      CK_SESSION_HANDLE hSession,
		      CK_MECHANISM_PTR pMechanism,
		      CK_OBJECT_HANDLE hKey);

/*!
 * \brief hal_crypto
 * One stage crypto operation
 * \param command_id invoked command from TEE
 * \param hSession see PKCS11
 * \param src is operation target buffer
 * \param src_len is src buffer lenghtn in bytes
 * \param dst operation output is placed into dst buffer
 * \param dst_len is dst buffer length in bytes
 * \return
 */
CK_RV hal_crypto(uint32_t command_id,
		 CK_SESSION_HANDLE hSession,
		 CK_BYTE_PTR src,
		 CK_ULONG src_len,
		 CK_BYTE_PTR dst,
		 CK_ULONG_PTR dst_len);

/*!
 * \brief hal_crypto_update
 * Update one going crypto operation
 * \param command_id invoked command from TEE
 * \param hSession see PKCS11
 * \param src is operation target buffer
 * \param src_len is src buffer lenghtn in bytes
 * \param dst operation output is placed into dst buffer
 * \param dst_len is dst buffer length in bytes
 * \return
 */
CK_RV hal_crypto_update(uint32_t command_id,
			CK_SESSION_HANDLE hSession,
			CK_BYTE_PTR src,
			CK_ULONG src_len,
			CK_BYTE_PTR dst,
			CK_ULONG_PTR dst_len);

/*!
 * \brief hal_crypto_final
 * Finalizes crypto operation
 * \param command_id invoked command from TEE
 * \param hSession see PKCS11
 * \param dst operation output is placed into dst buffer
 * \param dst_len is dst buffer length in bytes
 * \return
 */
CK_RV hal_crypto_final(uint32_t command_id,
			CK_SESSION_HANDLE hSession,
			CK_BYTE_PTR dst,
			CK_ULONG_PTR dst_len);

#endif // HAL_H
