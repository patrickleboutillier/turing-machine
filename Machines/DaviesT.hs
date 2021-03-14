module Machines.DaviesT where

import Turing.MConfig
import Turing.Machine


s = "s" ==> [None           [P "0", R]      $ a] 

a = "a" ==> [None           [P "y", R]      $ b, 
             Any            [R]             $ a] 

b = "b" ==> [None           [P "x", L]      $ c, 
             Any            [R]             $ b]

c = "c" ==> [Sym "y"        [L]             $ d, 
             Not "y"        [L]             $ c,
             None           [L]             $ c]

d = "d" ==> [Sym "x"        [P "1", R]      $ b, 
             Sym "0"        [R]             $ e, 
             NotOneOf 
                ["x", "0"]  [L]             $ d,
             None           [L]             $ d]

e = "e" ==> [Sym "y"        [P "0", R]      $ a,
             Not "y"        [R]             $ e,
             None           [R]             $ e]

m = newTM s