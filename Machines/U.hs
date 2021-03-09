module Machines.U where


import Turing.Base
import Turing.MConfig
import Turing.Machine
import Turing.Machine.U
import qualified Machines.TATp150 as T (m)

-- This machine implements the machine from page 150
dom = [" ", "0", "1"]

b = "b" ==> [None    [P "0", R]    c]
c = "c" ==> [None    [P "1", R]    b]

m = u T.m