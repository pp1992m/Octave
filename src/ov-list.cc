/*

Copyright (C) 1996, 1997 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <strstream.h>

#include "lo-utils.h"

#include "defun.h"
#include "error.h"
#include "ov-list.h"
#include "unwind-prot.h"

DEFINE_OCTAVE_ALLOCATOR (octave_list);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_list, "list");

octave_value
octave_list::do_index_op (const octave_value_list& idx)
{
  octave_value retval;

  if (idx.length () == 1)
    {
      idx_vector i = idx (0).index_vector ();

      retval = octave_value_list (lst.index (i));
    }
  else
    error ("lists may only be indexed by a single scalar");

  return retval;
}

void
octave_list::assign (const octave_value_list& idx, const octave_value& rhs)
{
  if (idx.length () == 1)
    {
      int i = idx(0).int_value (true);

      if (! error_state)
	{
	  int n = lst.length ();

	  if (i > 0 && (Vresize_on_range_error || i <= n))
	    lst(i-1) = rhs;
	  else
	    error ("list index = %d out of range", i);
	}
      else
	error ("list index must be an integer");
    }
  else
    error ("lists may only be indexed by a single scalar");
}

void
octave_list::print (ostream& os, bool) const
{
  print_raw (os);
}

void
octave_list::print_raw (ostream& os, bool) const
{
  unwind_protect::begin_frame ("octave_list_print");

  int n = lst.length ();

  if (n > 0)
    {
      indent (os);
      os << "(";
      newline (os);

      increment_indent_level ();

      for (int i = 0; i < n; i++)
	{
	  ostrstream buf;
	  buf << "[" << i+1 << "]" << ends;
	  const char *nm = buf.str ();

	  octave_value val = lst(i);

	  val.print_with_name (os, nm);

	  delete [] nm;
	}

      decrement_indent_level ();

      indent (os);
      os << ")";
    }
  else
    os << "()";

  newline (os);

  unwind_protect::run_frame ("octave_list_print");
}

bool
octave_list::print_name_tag (ostream& os, const string& name) const
{
  indent (os);
  if (lst.length () == 0)
    os << name << " = ";
  else
    {
      os << name << " =";
      newline (os);
    }
  return false;
}

DEFUN (list, args, ,
  "list (ARGS)\n\
\n\
Create a new list from ARGS.")
{
  return octave_value (args);
}

DEFUN (nth, args, ,
  "nth (LIST, N)\n\
\n\
Return the N-th element of LIST.")
{
  octave_value retval;

  if (args.length () == 2)
    {
      octave_value_list lst = args(0).list_value ();

      if (! error_state)
	{
	  int n = args(1).int_value (true);

	  if (! error_state)
	    {
	      if (n > 0 && n <= lst.length ())
		retval = lst(n-1);
	      else
		error ("nth: index = %d out of range", n);
	    }
	  else
	    error ("nth: second argument must be an integer");
	}
      else
	error ("nth: first argument must be a list");
    }
  else
    print_usage ("nth");

  return retval;
}

DEFUN (append, args, ,
  "append (LIST, ARG, ...)\n\
\n\
Return a new list created by appending each ARG to LIST.  If any of\n\
the arguments to be appended is a list, its elements are appended\n\
individually.  For example,\n\
\n\
  x = list (1, 2);\n\
  y = list (3, 4);\n\
  append (x, y);\n\
\n\
results in the list containing the four elements (1 2 3 4), not a list\n\
containing the three elements (1 2 (3 4))")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      octave_value_list tmp = args(0).list_value ();

      if (! error_state)
	{
	  for (int i = 1; i < nargin; i++)
	    {
	      octave_value ov = args(i);

	      if (ov.is_list ())
		tmp.append (ov.list_value ());
	      else
		tmp.append (ov);
	    }

	  retval = tmp;
	}
    }
  else
    print_usage ("append");

  return retval;
}

DEFUN (reverse, args, ,
  "reverse (LIST)\n\
\n\
Return a new list created by reversing the elements of LIST")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1)
    {
      octave_value_list tmp = args(0).list_value ();

      if (! error_state)
	  retval = tmp.reverse ();
    }
  else
    print_usage ("reverse");

  return retval;
}

DEFUN (splice, args, ,
  "splice (LIST_1, OFFSET, LENGTH, LIST_2)\n\
splice (LIST_1, OFFSET, LENGTH, LIST_2)\n\
splice (LIST_1, OFFSET, LENGTH)\n\
splice (LIST_1, OFFSET)\n\
\n\
Replace LENGTH elements of LIST_1 beginning at OFFSET with the\n\
contents of LIST_2 (if any).  If LENGTH is omitted, all elements\n\
from OFFSET to the end of LIST_1 are replaced.  As a special case, if\n\
OFFSET is one greater than the length of LIST_1 and LENGTH is 0,\n\
splice is equivalent to append (LIST_1, LIST_2)")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1 && nargin < 5)
    {
      octave_value_list list_1 = args(0).list_value ();

      if (! error_state)
	{
	  int offset = args(1).int_value (true);

	  if (! error_state)
	    {
	      offset--;

	      int length = 0;

	      octave_value_list list_2;

	      if (nargin < 3)
		length = list_1.length () - offset;
	      else
		{
		  length = args(2).int_value (true);

		  if (! error_state)
		    {
		      if (nargin == 4)
			{
			  list_2 = args(3).list_value ();

			  if (error_state)
			    error ("splice: fourth argument must be a list");
			}
		    }
		  else
		    error ("splice: LENGTH must be an integer");
		}

	      if (! error_state)
		retval = list_1.splice (offset, length, list_2);
	    }
	  else
	    error ("splice: OFFSET must be an integer");
	}
      else
	error ("splice: first argument must be a list");      
    }
  else
    print_usage ("splice");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
