/* Perform an inferior function call, for GDB, the GNU debugger.

   Copyright (C) 2003-2015 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef INFCALL_H
#define INFCALL_H

#include "dummy-frame.h"

struct value;
struct type;

extern CORE_ADDR find_function_addr (struct value *function, 
				     struct type **retval_type);

/* Perform a function call in the inferior.

   ARGS is a vector of values of arguments (NARGS of them).  FUNCTION
   is a value, the function to be called.  Returns a value
   representing what the function returned.  May fail to return, if a
   breakpoint or signal is hit during the execution of the function.

   ARGS is modified to contain coerced values.  */

extern struct value *call_function_by_hand (struct value *function, int nargs,
					    struct value **args);

/* Similar to call_function_by_hand and additional call
   register_dummy_frame_dtor with DUMMY_DTOR and DUMMY_DTOR_DATA for the
   created inferior call dummy frame.  */

extern struct value *
  call_function_by_hand_dummy (struct value *function, int nargs,
			       struct value **args,
			       dummy_frame_dtor_ftype *dummy_dtor,
			       void *dummy_dtor_data);

struct dummy_frame_context_saver;
extern void dummy_frame_context_saver_drop
  (struct dummy_frame_context_saver *data);
extern void dummy_frame_context_saver_cleanup (void *data_voidp);
extern struct regcache *dummy_frame_context_saver_get_regs
  (struct dummy_frame_context_saver *saver);
extern struct dummy_frame_context_saver *dummy_frame_context_saver_setup
  (struct frame_id dummy_id, ptid_t ptid);

#endif
