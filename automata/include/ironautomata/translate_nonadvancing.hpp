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
 ****************************************************************************/

#ifndef _IA_TRANSLATE_NONADVANCING_HPP_
#define _IA_TRANSLATE_NONADVANCING_HPP_

/**
 * @file
 * @brief IronAutomata --- Reduce unnecessary edge transitions.
 *
 * @author Christopher Alfeld <calfeld@qualys.com>
 */

#include <ironautomata/intermediate.hpp>

namespace IronAutomata {
namespace Intermediate {

/**
 * Convert non-advancing edges to appropriate advancing edges.
 *
 * When a non-advancing edge is followed, it implies that the next input is
 * the same as the one that the edge matched.  This knowledge can be used to
 * calculate the possible next edges.  In cases, where no outputs are involved
 * (especially true if no_advance_no_output is set), the non-advancing edge
 * can be replaced with an edge directly to the next target.
 *
 * Specifically, this routine searches for non-advancing edges from @c A to
 * @c B on input @c c that are:
 *
 * - There is no output generated by @c B (automatic for no_advance_no_output
 *   automata).
 * - Determine the next edge(s) from @c B, one of:
 *   - No edge: In which case, the original edge can be removed.  This is
 *     only done if the source node has no output to avoid interfering with
 *     algorithms that check outputs of ending nodes.
 *   - Unique, possibly default, edge to @c C: In which case, the original
 *     can be replaced with an edge to @c C.
 *   - Multiple edges: If @a conservative, do nothing, otherwise, as above
 *     for eh edge.
 *
 * This search and changes is iterated until the automata stabilizes.
 *
 * @note If no_advance_no_output is set, this routine will eliminate all
 * non-advancing edges for deterministic automata (or non-deterministic if
 * not @a conservative).
 *
 * @note The resulting automata may very well be larger than the original.  It
 * will usually, but not always, be faster.
 *
 * @param[in] automata     Automata to translate.
 * @param[in] conservative If true, will not replace an edge with more than
 *                         one edge.  Has no effect for deterministic
 *                         automata.
 * @return Number of operations performed.
 */
size_t translate_nonadvancing(
    Automata& automata,
    bool      conservative = true
);

} // Intermediate
} // IronAutomata

#endif
