import Turing.Base (Tape(..))
import Turing.MConfig
import Turing.StdForm
import Turing.Machine
import qualified Turing.Machine.U as U

import qualified Machines.TATp81 as TATp81
import qualified Machines.TATp81f as TATp81f
import qualified Machines.TATp83 as TATp83
import qualified Machines.TATp84 as TATp84
import qualified Machines.TATp87 as TATp87
import qualified Machines.TATp150 as TATp150
import qualified Machines.DaviesT as DaviesT


tapeAfter :: Int -> Machine -> Tape
tapeAfter n m = (\(Machine tape _) -> tape) . last . take n . moves $ m

squares :: Tape -> [Symbol]
squares (Tape ls h rs) = ls ++ [h] ++ rs

main = do
    putStr "TATp81 m-config table: " >> (print . asTable $ TATp81.b)
    putStr "TATp81 standard form: " >> (print . toStandardForm . asTable $ TATp81.b)
    putStr "TATp81 standard desciption: " >> (print . toStandardDesc . asTable $ TATp81.b)
    putStr "TATp81 description number: " >> (print . toDescNumber . asTable $ TATp81.b)
    putStr "TATp81 run:      " >> runTM       20 TATp81.m
    putStr "TATp81f run:     " >> runTM       20 TATp81f.m
    putStr "TATp83 run:      " >> runTM       20 TATp83.m
    putStr "TATp84 run:      " >> runTM       20 TATp84.m
    putStr "TATp87 run:      " >> runTM      200 TATp87.m
    putStr "DaviesT run:     " >> runTM       50 DaviesT.m
    putStr "TATp150 run:     " >> runTM       10 TATp150.m
    let t = tapeAfter 180000 $ U.m TATp150.m
    let sym = filter (\s -> s == "0" || s == "1") . squares $ t
    let t' = Tape sym " " []
    putStr "U loaded with a tape containing the standard description of TATp150:\n" 
    putStr "U(TATp150) run:  " >> print t'
    let dn = toDescNumber . asTable $ U.b 
    putStr "Description number of U has " >> (putStr . show $ length dn) >> putStrLn " digits."
