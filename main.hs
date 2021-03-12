import Turing.Base (Tape(..))
import Turing.MConfig
import Turing.Machine
import Turing.Machine.U

import qualified Machines.TATp81 as TATp81
import qualified Machines.TATp83 as TATp83
import qualified Machines.TATp84 as TATp84
import qualified Machines.TATp87 as TATp87
import qualified Machines.TATp150 as TATp150


tapeAfter :: Int -> Machine -> Tape
tapeAfter n m = (\(Machine dom tape _) -> tape) . last . take n . moves $ m

squares :: Tape -> [Symbol]
squares (Tape ls h rs) = ls ++ [h] ++ rs

main = do
    putStr "TATp81:      " >> runTM       20 TATp81.m
    putStr "TATp83:      " >> runTM       20 TATp83.m
    putStr "TATp84:      " >> runTM       20 TATp84.m
    putStr "TATp87:      " >> runTM      200 TATp87.m
    putStr "TATp8150:    " >> runTM       10 TATp150.m
    let t = tapeAfter 180000 $ u TATp150.m
    let sym = filter (\s -> s == "0" || s == "1") . squares $ t
    let t' = Tape sym " " []
    putStr "U loaded with a tape containing the standard description of TATp8150:\n" 
    putStr "U(TATp8150): " >> print t'