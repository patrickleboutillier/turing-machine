module Machines.U where


import Turing.MConfig
import Turing.StdForm
import Turing.Machine
import Turing.Machine.U
import qualified Machines.TATp150 as T

m@(Machine dom tape mc) = u T.m