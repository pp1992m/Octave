## Copyright (C) 2006-2012 John W. Eaton
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

%% test/octave.test/for/for-1.m
%!test
%! for i = 1
%!   __printf_assert__ ("%d", i);
%! end
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1"));

%% test/octave.test/for/for-2.m
%!test
%! for i = 1:4
%!   __printf_assert__ ("%d", i);
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1234"));

%% test/octave.test/for/for-3.m
%!test
%! for i = [1,2,3,4]
%!   __printf_assert__ ("%d", i);
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1234"));

%% test/octave.test/for/for-4.m
%!test
%! for i = [1,2;3,4]
%!   __printf_assert__ ("%d", i(1,1));
%!   __printf_assert__ ("%d", i(2,1));
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1324"));

%% test/octave.test/for/for-5.m
%!test
%! for i = I
%!   __printf_assert__ ("%d", imag (i));
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1"));

%% test/octave.test/for/for-6.m
%!test
%! for i = [1,2,3,4]*I
%!   __printf_assert__ ("%d", imag (i));
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1234"));

%% test/octave.test/for/for-7.m
%!test
%! for i = [1,2;3,4]*I
%!   __printf_assert__ ("%d", imag (i(1,1)));
%!   __printf_assert__ ("%d", imag (i(2,1)));
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("1324"));

%% test/octave.test/for/for-8.m
%!test
%! for i = [1,2,3,4]
%!   if (i > 2)
%!     break;
%!   endif
%!   __printf_assert__ ("%d", i);
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("12"));

%% test/octave.test/for/for-9.m
%!test
%! for i = [1,2,3,4]
%!   if (i < 3)
%!     continue;
%!   endif
%!   __printf_assert__ ("%d", i);
%! endfor
%! __printf_assert__ ("\n");
%! assert (__prog_output_assert__ ("34"));

%!test
%! a = [1,3;2,4];
%! j = 0;
%! for i = cat (3, a, 4 + a)
%!   assert (i, [1;2] + 2*j++)
%! endfor

%!test
%! a = {1,3;2,4};
%! j = 0;
%! for i = cat (3, a, cellfun (@(x) 4 + x, a, "UniformOutput", 0))
%!   assert (i, {1 + 2*j; 2 + 2*j++})
%! endfor
