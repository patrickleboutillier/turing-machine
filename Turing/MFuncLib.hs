module Turing.MFuncLib (f, g, g'2, e'1, e'2, e'3, pe, pe2, l, r, f', f'', c, ce'2, ce'3, 
    re'3, re'4, cr'2, cr'3, cp, cpe'4, cpe'5, ce2, ce3, ce4, ce5) where

import Turing.MConfig
import Turing.MFunction


{--
    This file contains all the functions defined by Turing, see chapter 7 of "The Annotated Turing"
--}


-- page 115
f  x@(mC, mB, a) = "f"%x  ==> [Sym "e"    [L]     $ f1 (mC, mB, a),
                               Not "e"    [L]     $ f  (mC, mB, a),
                               None       [L]     $ f  (mC, mB, a)]
f1 x@(mC, mB, a) = "f1"%x ==> [Sym a      []      $ mC,
                               Not a      [R]     $ f1 (mC, mB, a),
                               None       [R]     $ f2 (mC, mB, a)]
f2 x@(mC, mB, a) = "f2"%x ==> [Sym a      []      $ mC,
                               Not a      [R]     $ f1 (mC, mB, a),
                               None       [R]     $ mB]


-- page 118
e'3  x@(mC, mB, a) = "e'3"%x  ==> [Blank      []      $ f (e1'3 (mC, mB, a), mB, a)]
e1'3 x@(mC, mB, a) = "e1'3"%x ==> [Blank      [E]     $ mC]

e'2  x@(mB, a)     = "e'2"%x  ==> [Blank      []      $ e'3 (e'2 (mB, a), mB, a)]


-- page 120
pe  x@(mC, b) = "pe"%x  ==> [Blank    []          $ f (pe1 (mC, b), mC, "e")]
pe1 x@(mC, b) = "pe1"%x ==> [Any      [R, R]      $ pe1 (mC, b),
                             None     [P b]       $ mC]


-- page 121
l x@(mC)            = "l"%x   ==>   [Blank          [L]         $ mC]
r x@(mC)            = "r"%x   ==>   [Blank          [R]         $ mC]

f'  x@(mC, mB, a)   = "f'"%x  ==>   [Blank          []          $ f (l mC, mB, a)] 
f'' x@(mC, mB, a)   = "f''"%x ==>   [Blank          []          $ f (r mC, mB, a)] 

c  x@(mC, mB, a)    = "c"%x   ==>   [Blank          []          $ f' (c1 mC, mB, a)]
c1 x@(mC)           = "c1"%x  ==>   [Var                        $ (\b -> pe (mC, b))]


-- page 122
ce'3 x@(mC, mB, a)       = "ce'3"%x  ==>    [Blank     []          $ c (e'3 (mC, mB, a), mB, a)] 
ce'2 x@(mB, a)           = "ce'2"%x  ==>    [Blank     []          $ ce'3 (ce'2 (mB, a), mB, a)]

re'4  x@(mC, mB, a, b)   = "re'4" %x ==>    [Blank     []          $ f (re1'4 (mC, mB, a, b), mB, a)]
re1'4 x@(mC, mB, a, b)   = "re1'4"%x ==>    [Blank     [E, P b]    $ mC]

re'3 x@(mB, a, b)        = "re'3" %x ==>    [Blank     []          $ re'4 (re'3 (mB, a, b), mB, a, b)]


-- page 123
cr'3 x@(mC, mB, a)         = "cr'3"%x ==>     [Blank      []  $ c (re'4 (mC, mB, a, a), mB, a)] 
cr'2 x@(mB, a)             = "cr'2"%x ==>     [Blank      []  $ cr'3 (cr'2 (mB, a), re'3 (mB, a, a), a)]

cp  x@(mC, mU, mE, a, b)   = "cp" %x  ==>     [Blank      []  $ f' (cp1 (mC, mU, b), f (mU, mE, b), a)]
cp1 x@(mC, mU, b)          = "cp1"%x  ==>     [Var            $ (\y -> f' (cp2 (mC, mU, y), mU, b))]
cp2 x@(mC, mU, y)          = "cp2"%x  ==>     [Sym y      []  $ mC,
                                               Not y      []  $ mU] -- None line required here?

cpe'5 x@(mC, mU, mE, a, b) = "cpe'5"%x ==>    [Blank      []  $ cp (e'3 (e'3 (mC, mC, b), mC, a), mU, mE, a, b)]
cpe'4 x@(mU, mE, a, b)     = "cpe'4"%x ==>    [Blank      []  $ cpe'5 (cpe'4 (mU, mE, a, b), mU, mE, a, b)]


-- page 124, g instead of q
g   x@(mC)        = "g"    %x ==>     [Any            [R]         $ g mC,
                                       None           [R]         $ g1 mC]
g1  x@(mC)        = "g1"   %x ==>     [Any            [R]         $ g mC,
                                       None           []          $ mC]

g'2  x@(mC, a)    = "g'2" %x  ==>     [Blank          []          $ g $ g1'2 (mC, a)]
g1'2 x@(mC, a)    = "g1'2"%x  ==>     [Sym a          []          $ mC,
                                       Not a          [L]         $ g1'2 (mC, a),
                                       None           [L]         $ g1'2 (mC, a)]

pe2 x@(mC, a, b)  = "pe2"%x   ==>     [Blank          []          $ pe (pe (mC, b), a)]


--page 125
ce2 x@(mB, a, b)          = "ce2"%x ==>   [Blank     []          $ ce'2 (ce'2 (mB, b), a)]
ce3 x@(mB, a, b, y)       = "ce3"%x ==>   [Blank     []          $ ce'2 (ce2 (mB, b, y), a)]
ce4 x@(mB, a, b, y, o)    = "ce4"%x ==>   [Blank     []          $ ce'2 (ce3 (mB, b, y, o), a)]
ce5 x@(mB, a, b, y, o, e) = "ce5"%x ==>   [Blank     []          $ ce'2 (ce4 (mB, b, y, o, e), a)]

e'1  x@(mC)               = "e'1" %x ==>  [Sym "e"   [R]         $ e1'1 mC,
                                           Not "e"   [L]         $ e'1 mC,
                                           None      [L]         $ e'1 mC]
e1'1 x@(mC)               = "e1'1"%x ==>  [Any       [R, E, R]   $ e1'1 mC,
                                           None      []          $ mC]
                        