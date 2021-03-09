module TAT81p1 where

import Turing.Base
import Turing.MConfig
import Turing.Machine

-- This machine implements the machine that computes the value 1/3, i.e. alternating
-- 0s and 1s.

b = "b" ==> [None    [P "0", R]    c]
c = "c" ==> [None    [R]           e]
e = "e" ==> [None    [P "1", R]    f]
f = "f" ==> [None    [R]           b]

m = newTM b
