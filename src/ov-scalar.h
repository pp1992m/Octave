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

#if !defined (octave_scalar_h)
#define octave_scalar_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <cstdlib>

#include <string>

class ostream;

#include "lo-mappers.h"
#include "lo-utils.h"
#include "mx-base.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "ov-base.h"
#include "ov-typeinfo.h"

class Octave_map;
class octave_value_list;

class tree_walker;

// Real scalar values.

class
octave_scalar : public octave_base_value
{
public:

  octave_scalar (void)
    : octave_base_value (), scalar (0.0) { }

  octave_scalar (double d)
    : octave_base_value (), scalar (d) { }

  octave_scalar (const octave_scalar& s)
    : octave_base_value (), scalar (s.scalar) { }

  ~octave_scalar (void) { }

  octave_value *clone (void) { return new octave_scalar (*this); }

  octave_value do_index_op (const octave_value_list& idx);

  idx_vector index_vector (void) const { return idx_vector (scalar); }

  int rows (void) const { return 1; }
  int columns (void) const { return 1; }

  int length (void) const { return 1; }

  bool is_constant (void) const { return true; }

  bool is_defined (void) const { return true; }

  bool is_real_scalar (void) const { return true; }

  octave_value all (void) const { return (scalar != 0.0); }
  octave_value any (void) const { return (scalar != 0.0); }

  bool is_real_type (void) const { return true; }
  bool is_scalar_type (void) const { return true; }
  bool is_numeric_type (void) const { return true; }

  bool valid_as_scalar_index (void) const
    { return (! xisnan (scalar) && NINT (scalar) == 1); }

  bool valid_as_zero_index (void) const
    { return (! xisnan (scalar) && NINT (scalar) == 0); }

  bool is_true (void) const { return (scalar != 0.0); }

  double double_value (bool = false) const { return scalar; }

  double scalar_value (bool = false) const { return scalar; }

  Matrix matrix_value (bool = false) const
    { return Matrix (1, 1, scalar); }

  Complex complex_value (bool = false) const { return scalar; }

  ComplexMatrix complex_matrix_value (bool = false) const
    { return  ComplexMatrix (1, 1, Complex (scalar)); }

  void increment (void) { ++scalar; }

  void decrement (void) { --scalar; }

  octave_value convert_to_str (void) const;

  void print (ostream& os, bool pr_as_read_syntax = false) const;

  void print_raw (ostream& os, bool pr_as_read_syntax = false) const;

  bool print_name_tag (ostream& os, const string& name) const;

private:

  // The value of this scalar.
  double scalar;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA

  DECLARE_OCTAVE_ALLOCATOR
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
