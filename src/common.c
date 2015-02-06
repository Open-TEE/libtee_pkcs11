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

#include "cryptoki.h"
#include "common.h"
#include "tee_client_api.h"

static CK_RV reg_shm(TEEC_SharedMemory *reg_shm_1, TEEC_SharedMemory *reg_shm_2,
		     TEEC_SharedMemory *reg_shm_3, TEEC_SharedMemory *reg_shm_4)
{
	if (reg_shm_1 && TEEC_RegisterSharedMemory(g_tee_context, reg_shm_1) != TEEC_SUCCESS)
		goto err_1;

	if (reg_shm_2 && TEEC_RegisterSharedMemory(g_tee_context, reg_shm_2) != TEEC_SUCCESS)
		goto err_2;

	if (reg_shm_3 && TEEC_RegisterSharedMemory(g_tee_context, reg_shm_3) != TEEC_SUCCESS)
		goto err_3;

	if (reg_shm_4 && TEEC_RegisterSharedMemory(g_tee_context, reg_shm_4) != TEEC_SUCCESS)
		goto err_4;

	return CKR_OK;

err_4:
	TEEC_ReleaseSharedMemory(reg_shm_3);
err_3:
	TEEC_ReleaseSharedMemory(reg_shm_2);
err_2:
	TEEC_ReleaseSharedMemory(reg_shm_1);
err_1:
	return CKR_GENERAL_ERROR;
}

static CK_RV free_shm(TEEC_SharedMemory *reg_shm_1, TEEC_SharedMemory *reg_shm_2,
		      TEEC_SharedMemory *reg_shm_3, TEEC_SharedMemory *reg_shm_4)
{
	if (reg_shm_1)
		TEEC_ReleaseSharedMemory(reg_shm_1);

	if (reg_shm_2)
		TEEC_ReleaseSharedMemory(reg_shm_2);

	if (reg_shm_3)
		TEEC_ReleaseSharedMemory(reg_shm_3);

	if (reg_shm_4)
		TEEC_ReleaseSharedMemory(reg_shm_4);

	return CKR_OK;
}

/* Following four macros are defined for function default parameter functionality. Idea is to
 * declare struct which will be containing default function parameters and have a middle function
 * which will be filling default values. See command.h file, how this should be used */
#define FN_ARGS(name, ...) typedef struct { __VA_ARGS__ } link_fn_##name;
#define FN_ARG(name, value) name = in.name ? in.name : (value)
#define LINK_FN(name, args, ...) link_fn_##name((link_fn_##args) {__VA_ARGS__})
#define SHM_FN(type, fn, args)				\
	type link_fn_##fn(link_fn_##args in) {		\
		void *FN_ARG(ptr_1, NULL_PTR);		\
		void *FN_ARG(ptr_2, NULL_PTR);		\
		void *FN_ARG(ptr_3, NULL_PTR);		\
		void *FN_ARG(ptr_4, NULL_PTR);		\
							\
	return fn(ptr_1, ptr_2, ptr_3, ptr_4);		\
}
/* Using function default parameters macros */
FN_ARGS(shm_params, void *ptr_1; void *ptr_2; void *ptr_3; void *ptr_4;)
SHM_FN(CK_RV, reg_shm, shm_params)
SHM_FN(CK_RV, free_shm, shm_params)
