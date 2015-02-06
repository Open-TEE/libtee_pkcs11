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

#ifndef __COMMON_H_
#define __COMMON_H_

extern void *g_tee_context;

/*!
  \def register_shm(...)
  This function will register up to four shared memory region. In parameters are pointers to
  TEEC_SharedMemory structs and function will return CK_RV value. Example:
  rv = register_shm(&shm_1);
  rv = register_shm(&shm_1, &shm_2);
*/
#define register_shm(...) LINK_FN(reg_shm, shm_params, __VA_ARGS__)

/*!
  \def release_shm(...)
  See register_shm(...). This will do the same, but is releasing the registers
*/
#define release_shm(...) LINK_FN(free_shm, shm_params, __VA_ARGS__)

#endif /* __COMMON_H_ */
