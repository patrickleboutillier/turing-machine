# turing-machine
Simulation of Turing Machines in Haskell, based on the book by "The Annotated Turing" by Charles Petzold

# Introduction

# Contents
The code has a lot of building blocks that you can play around with to investigate Turing machines in Haskell. The file main.hs contains a good summary of what is available. Here is an example of the output:

    ghci> main
    TATp81 m-config table: m-configs over [" ","0","1"]
    b       -> ' '  -> [P "0",R]    -> c
    c       -> ' '  -> [R]  -> e
    e       -> ' '  -> [P "1",R]    -> f
    f       -> ' '  -> [R]  -> b
    TATp81 standard form: "q1S0S1Rq2;q2S0S0Rq3;q3S0S2Rq4;q4S0S0Rq1;"
    TATp81 standard desciption: "DADDCRDAA;DAADDRDAAA;DAAADDCCRDAAAA;DAAAADDRDA;"
    TATp81 description number: "31332531173113353111731113322531111731111335317"
    TATp81 run:      [0| |1| |0| |1| |0| |1| |0| |1| |0| |1| /f]
    TATp83 run:      [0| |1| |0| |0| |0| |0| |0| |0| |0| |0| /e]
    TATp84 run:      [0| |1| |0| |1| |0| |1| |0| |1| |0| |1| |0| |1| |0| |1| |0| |1| |0| |1| |0/b]
    TATp87 run:      [e|e|0| |0| |1| |0| |1| |1| |0| |1| |1| |1| |0| |1| |1| |1| |1| |0| |1| |1/q| |1| |1]
    DaviesT run:     [0|0|1|0|1|1|0|x|x|x/a]
    TATp150 run:     [0|1|0|1|0|1|0|1|0| /c]
    U loaded with a tape containing the standard description of TATp150:
    U(TATp150) run:  [0|1|0|1|0|1|0|1|0|[ ]]
    Description number of U has 56625959 digits.

I tried hard to keep the machine notation very close to the one in the book/paper. For example, see here for the definition of the machie described on page 81 of the book: [Machines/TATp81.hs](Machines/TATp81.hs)

# Note
If you are interested in building a Turing machine simulator, make sure you read "2.4 Corrections to Turing’s Universal Computing Machine
(Donald W. Davies)" in "The Essential Turing: Seminal Writings in Computing, Logic, Philosophy, Artificial Intelligence, and Artificial Life: Plus The Secrets of Enigma"
(http://www.cse.chalmers.se/~aikmitr/papers/Turing.pdf)
