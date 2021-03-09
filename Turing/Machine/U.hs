module Turing.Machine.U (u) where

import Turing.Base
import Turing.MConfig
import Turing.MFunctions
import Turing.Machine


-- The domain for universal Turing machines, page 151
dom = [" ", "0", "1", "D", "A", "C", "u", "v", "w", "x", "y", "z", ":", "L", "R", "N", ";", "::", "e"]

u :: Machine -> Machine
u m = newTMM dom b m


-- page 153
b  = "b" ==>      [Blank                []                                  $ f dom (b1, b1, "::")]
b1 = "b1" ==>     [Blank                [R, R, P ":", R, R, P "D", R, R, P "A"] $ anf]

anf  = "anf" ==>  [Blank                []                                  $ g'2 dom (anf1, ":")]
anf1 = "anf1"==>  [Blank                []                                  $ con dom (kom, "y")]

kom = "kom" ==>   [Sym ";"              [R, P "z", L]                       $ con dom (kmp, "x"),
                   Sym "z"              [L, L]                              $ kom,
                   NotOneOf [";", "z"]  [L]                                 $ kom,
                   None                 [L]                                 $ kom]

kmp = undefined
--}
------------------------------------

-- page 150
--b150 = mC "b" [(sNone,  [P "0", R], c150)]
--c150 = mC "c" [(sNone,  [P "1", R], b150)]
--tape150 = standardTape b150