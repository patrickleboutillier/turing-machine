module Machines.TATp81f where

import Turing.MConfig
import Turing.MFunction
import Turing.Machine

-- This machine implements the machine that computes the value 1/3, i.e. alternating
-- 0s and 1s, but it uses a dummy m-function for testing purposes


i x@(mC)    = "i"%x  ==> [Var           $ (\s -> j (mC, s)) ]
j x@(mC, a) = "j"%x  ==> [Sym a   []    $ c ]

b = "b" ==> [None    [P "0", R]      $ i c]
c = "c" ==> [None    [R]             e]
e = "e" ==> [None    [P "1", R]      f]
f = "f" ==> [None    [R]             b]

m = newTM b
