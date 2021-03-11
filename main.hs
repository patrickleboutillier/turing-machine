import Turing.MConfig
import Turing.Machine

import qualified Machines.TATp81 as TATp81
import qualified Machines.TATp83 as TATp83
import qualified Machines.TATp84 as TATp84
import qualified Machines.TATp87 as TATp87
import qualified Machines.TATp150 as TATp150


main = do
    runTM  20 TATp81.m
    runTM  20 TATp83.m
    runTM  20 TATp84.m
    runTM 200 TATp87.m
    runTM  20 TATp150.m