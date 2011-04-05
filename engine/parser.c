/*****************************************************************************
 * Licensed to Qualys, Inc. (QUALYS) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * QUALYS licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 * @brief IronBee - Parser
 *
 * @author Brian Rectanus <brectanus@qualys.com>
 */

#include "ironbee_config_auto.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#include <ironbee/engine.h>
#include <ironbee/util.h>
#include <ironbee/provider.h>

#include "ironbee_private.h"


/* -- Exported Parser Routines -- */

ib_provider_inst_t *ib_parser_provider_get_instance(ib_context_t *ctx)
{
    IB_FTRACE_INIT(ib_parser_provider_get_instance);
    ib_core_cfg_t *corecfg;
    ib_status_t rc;

    rc = ib_context_module_config(ctx, ib_core_module(),
                                  (void *)&corecfg);
    if (rc != IB_OK) {
        IB_FTRACE_RET_PTR(ib_provider_inst_t, NULL);
    }

    IB_FTRACE_RET_PTR(ib_provider_inst_t, corecfg->pi.parser);
}

void ib_parser_provider_set_instance(ib_context_t *ctx, ib_provider_inst_t *pi)
{
    IB_FTRACE_INIT(ib_parser_provider_set_instance);
    ib_core_cfg_t *corecfg;
    ib_status_t rc;

    rc = ib_context_module_config(ctx, ib_core_module(),
                                  (void *)&corecfg);
    if (rc != IB_OK) {
        /// @todo This func should return ib_status_t now
        IB_FTRACE_RET_VOID();
    }

    corecfg->pi.parser = pi;

    IB_FTRACE_RET_VOID();
}

