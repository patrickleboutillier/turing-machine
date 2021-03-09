module TAT81p1 where


import Turing.Base
import Turing.MConfig


-- This machine 
b = mC "b" [(None,    [P "0", R], c)]
c = mC "c" [(None,    [R],        e)]
e = mC "e" [(None,    [P "1", R], f)]
f = mC "f" [(None,    [R],        b)]