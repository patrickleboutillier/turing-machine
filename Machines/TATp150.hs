module Machines.TATp150 where

import Turing.MConfig
import Turing.Machine


-- This machine implements the machine from page 150
b = "b" ==> [None    [P "0", R]    c]
c = "c" ==> [None    [P "1", R]    b]

m = newTM b