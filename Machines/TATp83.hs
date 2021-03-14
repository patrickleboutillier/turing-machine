module Machines.TATp83 where

import Turing.MConfig
import Turing.Machine

-- This machine implements the machine that computes the value 1/4

b = "b" ==> [None   [P "0", R]  c]
c = "c" ==> [None   [R]         d]
d = "d" ==> [None   [P "1", R]  e]
e = "e" ==> [None   [R]         f]
f = "f" ==> [None   [P "0", R]  e]

m = newTM b
