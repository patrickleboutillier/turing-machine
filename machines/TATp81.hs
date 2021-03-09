module TAT81p1 where


import Turing.Base
import Turing.MConfig


-- This machine 
b = "b" ==> [None    [P "0", R]    c]
c = "c" ==> [None    [R]           e]
e = "e" ==> [None    [P "1", R]    f]
f = "f" ==> [None    [R]           b]