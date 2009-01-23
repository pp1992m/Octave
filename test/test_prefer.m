## Copyright (C) 2006, 2007 John W. Eaton
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or (at
## your option) any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

%% Automatically generated from DejaGNU files

%% test/octave.test/prefer/prefer-1.m
%!test
%! m = [3 2];
%! assert(all (m == (3:-1:2)));

%% test/octave.test/prefer/prefer-2.m
%!test
%! m = [3,
%! 2];
%! assert(all (m == (3:-1:2)'));

%% test/octave.test/prefer/prefer-3.m
%!test
%! a = 2;
%! assert([a - 1],1);

%% test/octave.test/prefer/prefer-4.m
%!test
%! m = [3,2];
%! fail("[m ']");

%% test/octave.test/prefer/prefer-5.m
%!assert(all ([3 2] == (3:-1:2)));

%% test/octave.test/prefer/prefer-6.m
%!assert(all ([3, 2] == (3:-1:2)));

%% test/octave.test/prefer/prefer-7.m
%!test
%! m = [3,2];
%! assert(all ([m (1)] == (3:-1:1)));

%% test/octave.test/prefer/prefer-8.m
%!test
%! m = [3,2];
%! assert([m(1)],3);

%% test/octave.test/prefer/prefer-9.m
%!test
%! m = [3,2];
%! assert(all ([m (1)] == (3:-1:1)));

%% test/octave.test/prefer/prefer-10.m
%!test
%! a = 2;
%! assert([a- 1],1);

%% test/octave.test/prefer/prefer-11.m
%!test
%! a = 1;
%! assert(all ([a -1] == (1:-2:-1)));

%% test/octave.test/prefer/prefer-12.m
%!test
%! wsn = warning ("query", "Octave:str-to-num");
%! warning ("off", "Octave:str-to-num");
%! assert("d" + 0,100);
%! warning (wsn.state, "Octave:str-to-num");

%% test/octave.test/prefer/prefer-13.m
%!test
%! wsn = warning ("query", "Octave:str-to-num");
%! warning ("on", "Octave:str-to-num");
%! fail("'d' + 0","warning");
%! warning (wsn.state, "Octave:str-to-num");

%% test/octave.test/prefer/prefer-14.m
%!test
%! wir = warning ("query", "Ocave:imag-to-real");
%! warning ("off", "Ocave:imag-to-real");
%! assert(eye (1+i),1);
%! warning (wir.state, "Ocave:imag-to-real");

%% test/octave.test/prefer/prefer-15.m
%!test
%! wir = warning ("query", "Ocave:imag-to-real");
%! warning ("on", "Ocave:imag-to-real");
%! fail("eye (1+i)","warning");
%! warning (wir.state, "Ocave:imag-to-real");

%% test/octave.test/prefer/prefer-17.m
%!test
%! wrre = warning ("query", "Octave:resize-on-range-error");
%! warning ("off", "Octave:resize-on-range-error");
%! clear a; 
%! a(2) = 1; a(3) = 2; 
%! assert(all (a == [0,1,2]));
%! warning (wrre.state, "Octave:resize-on-range-error");

%% test/octave.test/prefer/prefer-18.m
%!test
%! clear a; 
%! a(1) = 1; a(2) = 2;
%! assert(all (a == [1,2]));

%% FIXME How the hell do I test this one in test/assert 
%% test/octave.test/prefer/prefer-19.m
%!#test
%! pid = print_answer_id_name ();
%! print_answer_id_name (0);
%! a = 1
%! print_answer_id_name (pid);

%% FIXME How the hell do I test this one in test/assert 
%% test/octave.test/prefer/prefer-20.m
%!#test
%! pid = print_answer_id_name ();
%! print_answer_id_name (1);
%! a = 1
%! print_answer_id_name (pid);

%% test/octave.test/prefer/prefer-21.m
%!test
%! ped = print_empty_dimensions ();
%! print_empty_dimensions (0);
%! a = cell (1, 1);
%! b = type -q a;
%! assert (!isempty (findstr (b{1}, "[]")));
%! assert (isempty (findstr (b{1} ,"[](0x0)")));
%! print_empty_dimensions (ped);

%% test/octave.test/prefer/prefer-22.m
%!test
%! ped = print_empty_dimensions ();
%! print_empty_dimensions (1);
%! a = cell (1, 1);
%! b = type -q a;
%! assert (!isempty (findstr (b{1}, "[](0x0)")));
%! print_empty_dimensions (ped);

%% test/octave.test/prefer/prefer-23.m
%!assert(all (size (inv ([])) == [0, 0]));

%% test/octave.test/prefer/prefer-24.m
%!assert(all (svd ([]) == zeros (0, 1)));

%% test/octave.test/prefer/prefer-27.m
%!test
%! sp = save_precision ();
%! save_precision (1);
%! x = pi;
%! nm = tmpnam();
%! save("-text",nm,"x");
%! clear x;
%! load(nm);
%! unlink(nm);
%! assert(x,3);
%! save_precision (sp);

%% test/octave.test/prefer/prefer-28.m
%!test
%! sp = save_precision ();
%! save_precision (5);
%! x = pi;
%! nm = tmpnam();
%! save("-text",nm,"x");
%! clear x;
%! load(nm);
%! unlink(nm);
%! assert(x,3.1416);
%! save_precision (sp);

%% FIXME Same problem as above!!!
%% test/octave.test/prefer/prefer-29.m
%!function f ()
%! 1
%!#test
%! sf = silent_functions ();
%! silent_functions (0);
%! f
%! assert(??);
%! silent_functions (sf);

%% FIXME Same problem as above!!!
%% test/octave.test/prefer/prefer-30.m
%!function f ()
%! 1
%!#test
%! sf = silent_functions ();
%! silent_functions (1);
%! f
%! assert(??);
%! silent_functions (sf);

%% test/octave.test/prefer/prefer-32.m
%!test
%! wndz = warning ("query", "Octave:neg-dim-as-zero");
%! warning ("on", "Octave:neg-dim-as-zero");
%! fail("eye (-1) == []","warning");
%! warning (wndz.state, "Octave:neg-dim-as-zero");

%% test/octave.test/prefer/prefer-33.m
%!test
%! wndz = warning ("query", "Octave:neg-dim-as-zero");
%! warning ("off", "Octave:neg-dim-as-zero");
%! assert(all (size (eye (-1)) == [0, 0]));
%! warning (wndz.state, "Octave:neg-dim-as-zero");

%% test/octave.test/prefer/prefer-34.m
%!test
%! watv = warning ("query", "Octave:assign-as-truth-value");
%! warning ("off", "Octave:assign-as-truth-value");
%! if (x = 1) 1; endif
%! warning (watv.state, "Octave:assign-as-truth-value");

%% test/octave.test/prefer/prefer-35.m
%!test
%! watv = warning ("query", "Octave:assign-as-truth-value");
%! warning ("on", "Octave:assign-as-truth-value");
%! fail("if (x = 1) 1; endif","warning");
%! warning (watv.state, "Octave:assign-as-truth-value");

%% test/octave.test/prefer/prefer-38.m
%!test
%! wdbz = warning ("query", "Octave:divide-by-zero");
%! warning ("off", "Octave:divide-by-zero");
%! assert(isinf (1/0));
%! warning (wdbz.state, "Octave:divide-by-zero");

%% test/octave.test/prefer/prefer-39.m
%!test
%! wdbz = warning ("query", "Octave:divide-by-zero");
%! warning ("on", "Octave:divide-by-zero");
%! a = 1;
%! b = 0;
%! fail("isinf (a/b);","warning")
%! warning (wdbz.state, "Octave:divide-by-zero");

