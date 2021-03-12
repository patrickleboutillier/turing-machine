module Turing.MFuncLib (f, g, g'2, e'1, e'2, e'3, pe, pe2, l, r, f', f'', c, ce'2, ce'3, 
    re'3, re'4, cr'2, cr'3, cp, cpe'4, cpe'5, ce2, ce3, ce4, ce5, con) where


import Turing.MConfig
import Turing.MFunction


{--
    This file contains all the function defined by Turing, see chapter 7 of "The Annotated Turing"
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
e'3  d x@(mC, mB, a) = "e'3"%x  ==> [Blank      []      $ f (e1'3 d (mC, mB, a), mB, a)]
e1'3 d x@(mC, mB, a) = "e1'3"%x ==> [Blank      [E]     $ mC]

e'2  d x@(mB, a)     = "e'2"%x  ==> [Blank      []      $ e'3 d (e'2 d (mB, a), mB, a)]


-- page 120
pe  d x@(mC, b) = "pe"%x  ==> [Blank    []          $ f (pe1 d (mC, b), mC, "e")]
pe1 d x@(mC, b) = "pe1"%x ==> [Any      [R, R]      $ pe1 d (mC, b),
                               None     [P b]       $ mC]


-- page 121
l x@(mC)            = "l"%x   ==>   [Blank          [L]         $ mC]
r x@(mC)            = "r"%x   ==>   [Blank          [R]         $ mC]

f'  d x@(mC, mB, a) = "f'"%x  ==>   [Blank          []          $ f (l mC, mB, a)] 
f'' d x@(mC, mB, a) = "f''"%x ==>   [Blank          []          $ f (r mC, mB, a)] 

c  d x@(mC, mB, a)  = "c"%x   ==>   [Blank          []          $ f' d (c1 d mC, mB, a)]
c1 d x@(mC)         = "c1"%x  ==> map f d
    where f b =                      Sym b          []          $ pe d (mC, b)


-- page 122
ce'3 d x@(mC, mB, a)     = "ce'3"%x  ==>    [Blank     []          $ c d (e'3 d (mC, mB, a), mB, a)] 
ce'2 d x@(mB, a)         = "ce'2"%x  ==>    [Blank     []          $ ce'3 d (ce'2 d (mB, a), mB, a)]

re'4  d x@(mC, mB, a, b) = "re'4" %x ==>    [Blank     []          $ f (re1'4 d (mC, mB, a, b), mB, a)]
re1'4 d x@(mC, mB, a, b) = "re1'4"%x ==>    [Blank     [E, P b]    $ mC]

re'3 d x@(mB, a, b)      = "re'3" %x ==>    [Blank     []          $ re'4 d (re'3 d (mB, a, b), mB, a, b)]


-- page 123
cr'3 d x@(mC, mB, a)         = "cr'3"%x ==>     [Blank      []  $ c d (re'4 d (mC, mB, a, a), mB, a)] 
cr'2 d x@(mB, a)             = "cr'2"%x ==>     [Blank      []  $ cr'3 d (cr'2 d (mB, a), re'3 d (mB, a, a), a)]

cp  d x@(mC, mU, mE, a, b)   = "cp" %x  ==>     [Blank      []  $ f' d (cp1 d (mC, mU, b), f (mU, mE, b), a)]
cp1 d x@(mC, mU, b)          = "cp1"%x  ==> map f d 
    where f y =                                  Sym y      []  $ f' d (cp2 d (mC, mU, y), mU, b)
cp2 d x@(mC, mU, y)          = "cp2"%x  ==>     [Sym y      []  $ mC,
                                                 Not y      []  $ mU] -- None line required here?

cpe'5 d x@(mC, mU, mE, a, b) = "cpe'5"%x ==>    [Blank      []  $ cp d (e'3 d (e'3 d (mC, mC, b), mC, a), mU, mE, a, b)]
cpe'4 d x@(mU, mE, a, b)     = "cpe'4"%x ==>    [Blank      []  $ cpe'5 d (cpe'4 d (mU, mE, a, b), mU, mE, a, b)]


-- page 124, g instead of q
g   d x@(mC)        = "g"    %x ==>     [Any            [R]         $ g d mC,
                                         None           [R]         $ g1 d mC]
g1  d x@(mC)        = "g1"   %x ==>     [Any            [R]         $ g d mC,
                                         None           []          $ mC]

g'2  d x@(mC, a)    = "g'2" %x  ==>     [Blank          []          $ g d $ g1'2 d (mC, a)]
g1'2 d x@(mC, a)    = "g1'2"%x  ==>     [Sym a          []          $ mC,
                                         Not a          [L]         $ g1'2 d (mC, a),
                                         None           [L]         $ g1'2 d (mC, a)]

pe2 d x@(mC, a, b)  = "pe2"%x   ==>     [Blank          []          $ pe d (pe d (mC, b), a)]


--page 125
ce2 d x@(mB, a, b)          = "ce2"%x ==>   [Blank     []          $ ce'2 d (ce'2 d (mB, b), a)]
ce3 d x@(mB, a, b, y)       = "ce3"%x ==>   [Blank     []          $ ce'2 d (ce2 d (mB, b, y), a)]
ce4 d x@(mB, a, b, y, o)    = "ce4"%x ==>   [Blank     []          $ ce'2 d (ce3 d (mB, b, y, o), a)]
ce5 d x@(mB, a, b, y, o, e) = "ce5"%x ==>   [Blank     []          $ ce'2 d (ce4 d (mB, b, y, o, e), a)]

e'1  d x@(mC)               = "e'1" %x ==>  [Sym "e"   [R]         $ e1'1 d mC,
                                             Not "e"   [L]         $ e'1 d mC,
                                             None      [L]         $ e'1 d mC]
e1'1 d x@(mC)               = "e1'1"%x ==>  [Any       [R, E, R]   $ e1'1 d mC,
                                             None      []          $ mC]


-- page 152
con  x@(mC, a) = "con"  %x ==>    [Not "A"    [R, R]                    $ con  (mC, a),
                                   Sym "A"    [L, P a, R]               $ con1 (mC, a)]
con1 x@(mC, a) = "con1" %x ==>    [Sym "A"    [R, P a, R]               $ con1 (mC, a),
                                   Sym "D"    [R, P a, R]               $ con2 (mC, a),
                                   None       [P "D", R, P a, R, R, R]  $ mC]
con2 x@(mC, a) = "con2" %x ==>    [Sym "C"    [R, P a, R]               $ con2 (mC, a),
                                   Not "C"    [R, R]                    $ mC,
                                   None       [R, R]                    $ mC]
                        